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
const number HUNDRED_THOUSAND = 100000;
const number TEN_MILLION = 10000000;
const number BILLION = 1000000000;
const number two_pow_25 = 33554432;
const number two_pow_32 = 4294967296;
const int L1 = 128;   //256;   //L1 cache size  - 128@FEUP; 256@Home
const int L2 = 1024;  //L2 cache size
const int DEBUG = 0;

/*Algorithms*/
  //Implement like the openmp, just divide the data in segments then let the rest process
number sieveMPI(number lowerBound, number upperBound) {

  number i, j;
  //All odd numbers set to primes
  //Since only odd numbers can be primes, we trim down the array to half it's size
  //(excluding all even numbers from the start)
  number prime_arraySize = (upperBound - lowerBound + 1)/2; //+1 to include the last number
  //cout << "\n---\nLower bound: " << lowerBound << ". Upper bound: " << upperBound << ". Prime ArraySize: " << prime_arraySize << "\n---\n";
  char *isPrime = NULL;
  isPrime = (char*)malloc(prime_arraySize*sizeof(char));

  if(isPrime == NULL){
    cout << "Memory allocation failed (isPrime)\n";
    exit(0);
  }

  for (i = 0; i <= prime_arraySize; i++){
    isPrime[i] = 1;
  }

  //For optimization purpose, we calculate comparable variables
  //out of the for() statement
  number iSquare;
  //Segmented Sieve for odd numbers
  for (i = 3, iSquare=i*i; iSquare <= upperBound; i+=2, iSquare=i*i){

    //Skipping multiples of 3, 5, 7, 11, 13 and 17
    if (  (i >= 3  * 3  && i % 3  == 0)
       || (i >= 5  * 5  && i % 5  == 0)
       || (i >= 7  * 7  && i % 7  == 0)
       || (i >= 11 * 11 && i % 11 == 0)
       || (i >= 13 * 13 && i % 13 == 0)
       || (i >= 17 * 17 && i % 17 == 0))
      continue;

    //Calculate offset of segmnent
    number startValue = ((lowerBound + i - 1)/i)*i;

    //cout << "StartValue is = " << startValue << endl;
    if (startValue < i*i) {
      startValue = i*i;
      if(DEBUG)
      cout << "\tstartValue changed to = " << startValue << ". because < i*i" << endl;
    }

    if(DEBUG)
    cout << "startValue is = " << startValue << endl;
    //We only calculate from odd numbers
    if ((startValue % 2) == 0){
      startValue += i;
      if(DEBUG)
      cout << "\tstartvalue is pair, so changed to svalue + i : " << startValue << endl;
    }

    //Optimization purpose
    number iDouble = 2*i;
    //Removing all non-prime odds
    for (j = startValue; j<=upperBound; j+=iDouble){
      number nonPrimeIndex = j - lowerBound;
      isPrime[nonPrimeIndex/2] = 0;
      //cout << "\t\tstartValue is <= upperBound so nonPrimeIndex= " << nonPrimeIndex << ". j= " << j << ". isPrime[" << nonPrimeIndex/2 <<"] = 0." << endl;
    }
  }

  if(DEBUG)
  cout << "Iteration ended at i= " << i << endl;

  //Counting primes on array
  number prime_count = 0;

  // 2 is the only even prime number, added to the count if it's in the segment
  if (lowerBound == 2){
    prime_count++;
  }

  for (i = 0; i < prime_arraySize; i++) {
    prime_count += isPrime[i];
  }

    //  cout << "|||prime count neste processo: " << prime_count << "|||" << endl << endl;

  free(isPrime);
  return prime_count;
}

number sieveHybrid(number lowerBound, number upperBound, int nr_threads) {

  number segmentSize;
  if(DEBUG)
  segmentSize = 100;
  if(!DEBUG)
  segmentSize = L1 * L2;

  number segmentLowerBound, segmentUpperBound;
  number prime_count = 0;

  omp_set_num_threads(nr_threads);
  clock_gettime(CLOCK_REALTIME, &startTime);

  // Main Loop
  #pragma omp parallel for reduction (+:prime_count) schedule (dynamic)
    for (segmentLowerBound = lowerBound; segmentLowerBound <= upperBound; segmentLowerBound += segmentSize){
      number segmentUpperBound = segmentLowerBound + segmentSize;
      if (segmentUpperBound > upperBound){
        segmentUpperBound = upperBound;
      }

    prime_count += sieveMPI(segmentLowerBound, segmentUpperBound);
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
    //TODO ADD OTHER INPUT VALUES
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

    /*Variables to use in MPI world*/
    int rank_id;
    int world_size;
    number i, j;
    number prime_count;

    /*Initializing MPI world*/

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_id);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(rank_id == 0){
      switch(opt){
        case 1:
          cout << "Executing as a Distributed Memory System in " << world_size << " Cores." << endl;
          break;
        case 2:
          cout << "Executing as Hybrid System in " << world_size << " Cores and " << nr_threads << " threads PER Core." <<  endl;
          break;
        default:
          cout << "Wrong option! opt=" << opt << ". Please use 1 or 2." << endl;
          exit(0);
          break;
      }
    }

    clock_gettime(CLOCK_REALTIME, &startTime);


    if(rank_id == 0){
      //The remainder from sqrt(N) to N is divided by each thread
      number segmentSize = limit/world_size;
      number bounds_buff[2];             //0 as the lowerBound, 1 as the upperBound of the segment
      number lowerBound = segmentSize;      //First lowerBound is the 2nd thread's one = First upperBound of thread 0

      for(i=1; i<world_size; i++){
        //The last thread receives the remainder from the 2nd last until N
        if(i != world_size-1){
          bounds_buff[0] = lowerBound;
          bounds_buff[1] = lowerBound + segmentSize;
          lowerBound +=segmentSize; //Increments the lower bound for next segment
        }else{
          bounds_buff[0] = lowerBound;
          bounds_buff[1] = limit;
        }

        MPI_Send(bounds_buff, 2, MPI_LONG_LONG, i, 1, MPI_COMM_WORLD);
      }

      number prime_count;

      switch(opt){
        case 1:
          prime_count = sieveMPI(2, segmentSize);
          break;
        case 2:
          prime_count = sieveHybrid(2, segmentSize, nr_threads);
          break;
        default:
          break;
      }

      number prime_count_thread;

      for(i=1; i<world_size; i++){
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
          prime_count_thread = sieveMPI(bounds_buff[0], bounds_buff[1]);
          break;
        case 2:
          prime_count_thread = sieveHybrid(bounds_buff[0], bounds_buff[1], nr_threads);
          break;
        default:
          break;
      }

      MPI_Send(&prime_count_thread, 1, MPI_LONG_LONG, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
