//http://paginas.fe.up.pt/~apm/REDAI/

#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <math.h>

using namespace std;

struct timespec startTime, endTime;
typedef long long number;
const number BILLION = 1000000000;
const number two_pow_25 = 33554432;
const number two_pow_32 = 4294967296;
const int L1 = 256;   //L1 cache size
const int L2 = 1024;  //L2 cache size

/*Algorithms*/
//TODO Refactor - I don't use limitSqrt for nothing
  //Implement like the openmp, just divide the data in blocks then let the rest process
number sieveMPI(char* isPrime, number limitSqrt, number start, number end) {
	// Declaring array and setting all numbers to prime
	number arraySize = (end - start + 1) / 2;
	char* isPrimeBlock = (char*)malloc(arraySize*sizeof(char));
	number i, j;
	for(i = 0; i <= arraySize; i++){
		isPrimeBlock[i] = 1;
	}

	// Main loop
	number iDouble;
	for (i = 3; i*i <= end; i += 2){
		if(isPrime[i>>1]){
		// Skip numbers before block's range
			number startValue = ((start + i - 1) / i)*i;
			if (startValue < i*i) {
				startValue = i*i;
			}
		// Ensuring start value is off
			if ((startValue % 2) == 0){
				startValue += i;
			}

		//printf("Start: %lld\n", startValue);

		// Secondary Loop
			iDouble = 2 * i;
			for (j = startValue; j <= end; j += iDouble){
				number index = j - start;
				isPrimeBlock[index >> 1] = 0;
			}

		}
	}


	// Counting number of primes found
	number prime_count = 0;

	for (i = 0; i < arraySize; i++) {
		prime_count += isPrimeBlock[i];
	}

	if (start <= 2){
		prime_count++; // If it's the first block, 2 is an even prime number
	}

	// Freeing memory space
	return prime_count;
}

number sieveHybrid(char* isPrime, number limitSqrt, number start, number blockEnd) {
	omp_set_num_threads(omp_get_num_procs());
	number i, j, blockSize = L1*L2;

	number prime_count = 0;

	// Main Loop
	#pragma omp parallel for reduction (+:prime_count) shared(isPrime) schedule(dynamic)
	for (start = start; start <= blockEnd; start += blockSize){
		number end = start + blockSize;
		if (end > blockEnd){
			end = blockEnd;
		}

		prime_count += sieveMPI(isPrime, limitSqrt, start, end);
	}
	return prime_count;

}


/***************************************************/

/*Main*/
int main (int argc, char *argv[])
{
  /*Main execution*/
  int nr_threads = 1;
  number limit;
  int opt = 0;

  if(argc < 2){
    cout <<
    endl << "Usage: ./mpi <nr> <opt> <?nr_threads>" <<
    endl << "opt:" <<
    endl << "1. Distributed Memory System - Using only MPI" <<
    endl << "2. Hybrid - MPI with Shared Memory System" <<
    endl;
    return 0;
  }else{

    opt = atoi(argv[2]);

    if(strcmp(argv[1], "two_pow_25") == 0 ){
      limit = two_pow_25;
    }else if(strcmp(argv[1], "two_pow_32") == 0 ){
      limit = two_pow_32;
    }else{
      limit = atoll(argv[1]);
    }


    if(argv[3])
      nr_threads = atoi(argv[3]);
  }

  switch(opt){
    case 1:
      cout << "Executing as a Distributed Memory System" << endl;
      break;
    case 2:
      cout << "Executing as Hybrid System" << endl;
      break;
    default:
      cout << "Wrong option! opt=" << opt << ". Please use 1 or 2." << endl;
      exit(0);
      break;
  }

    /*Variables to use in MPI world*/
    int thread_id;
    number i, j;
    number prime_count;

    /*Initializing MPI world*/

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &thread_id);
    MPI_Comm_size(MPI_COMM_WORLD, &nr_threads);

    //http://www.algorithmist.com/index.php/Prime_Sieve_of_Eratosthenes
    //Trial Division Algorithm
    number limitSqrt = (number)sqrt((double)limit);
    number prime_arraySize = (limitSqrt-1)/2;
    char *isPrime = NULL;
    isPrime = (char*)malloc(prime_arraySize*sizeof(char));

    if(isPrime == NULL){
      cout << "Memory allocation failed (isPrime)\n";
      exit(0);
    }

    for(i = 0; i < prime_arraySize; i++){
      isPrime[i] = 1;
    }

    clock_gettime(CLOCK_REALTIME, &startTime);

    for(i=3; i<=limitSqrt; i+=2){
      if(isPrime[i>>1]){
        for(j=i*i; j<=limitSqrt; j+=2*i){
          isPrime[i>>1]=0;
        }
      }
    }

    if(thread_id == 0){
      //The remainder from sqrt(N) to N is divided by each thread
      number blockSize = (limit-limitSqrt)/nr_threads;
      number bounds_buff[2];             //0 as the lowerBound, 1 as the upperBound of the block
      number lowerBound = limitSqrt + blockSize;

      for(i=1; i<nr_threads; i++){
        //The last thread receives the remainder from the 2nd last until N
        if(i != nr_threads-1){
          bounds_buff[0] = lowerBound;
          bounds_buff[1] = lowerBound + blockSize;
          lowerBound +=blockSize; //Increments the lower bound for next block
        }else{
          bounds_buff[0] = lowerBound;
          bounds_buff[1] = limit;
        }

        MPI_Send(bounds_buff, 2, MPI_LONG_LONG, i, 1, MPI_COMM_WORLD);
      }

      number prime_count;

      switch(opt){
        case 1:
          prime_count = sieveMPI(isPrime, limitSqrt, limitSqrt, limitSqrt+blockSize);
          break;
        case 2:
          prime_count = sieveHybrid(isPrime, limitSqrt, limitSqrt, limitSqrt+blockSize);
          break;
        default:
          break;
      }

      number prime_count_thread;
      for(i=1; i<nr_threads; i++){
        MPI_Recv(&prime_count_thread, 1, MPI_LONG_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        prime_count += prime_count_thread;
      }
      clock_gettime(CLOCK_REALTIME, &endTime);
      double executionTime = ( endTime.tv_sec - startTime.tv_sec ) + (double)( endTime.tv_nsec - startTime.tv_nsec ) / (double)BILLION;
      cout << "\nTotal Time of execution: " << setprecision(3) << executionTime << " seconds" << endl << endl;

      cout << "Number of primes to " << limit << ": " << prime_count << endl << endl;
    }else{
      number bounds_buff[2];

      MPI_Recv(bounds_buff, 2, MPI_LONG_LONG, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      number prime_count_thread;

      switch(opt){
        case 1:
          prime_count_thread = sieveMPI(isPrime, limitSqrt, bounds_buff[0], bounds_buff[1]);
          break;
        case 2:
          prime_count_thread = sieveHybrid(isPrime, limitSqrt, bounds_buff[0], bounds_buff[1]);
          break;
        default:
          break;
      }

      MPI_Send(&prime_count_thread, 1, MPI_LONG_LONG, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
