#include <omp.h>
#include <stdio.h>
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

/*Primes Calculation*/
number sieveBySequence(number limit, int nr_threads){
  return 0;
}

number countByBlock(number start, number end) {
  //All odd numbers set to primes

  //Since only odd numbers can be primes, we trim down the array to half it's size 
  //(excluding all even numbers from the start)

  number prime_arraySize = (end - start ) / 2;
  char* isPrime = (char*) malloc(prime_arraySize*sizeof(char));
  number i, j;
  for (i = 0; i < prime_arraySize; i++){
    isPrime[i] = 1;
  }

  //TODO refactor
  // Main loop
  number iDouble;
  for (i = 3; i*i <= end; i += 2){

    // Skip numbers before block's range
    number startValue = ((start + i - 1) / i)*i;
    if (startValue < i*i) {
      startValue = i*i;
    }

    // Ensuring start value is off
    if ((startValue % 2) == 0){
      startValue += i;
    }

    // Secondary Loop
    iDouble = 2 * i;
    for (j = startValue; j <= end; j += iDouble){
      number index = j - start;
      isPrime[index >> 1] = 0;
    }
  }

  //Counting primes on array
  number prime_count = 0;

  // 2 is the only even prime number, added to the count if it's in the block
  if (start <= 2){
    prime_count++; 
  }

  for (i = 0; i < prime_arraySize; i++) {
    prime_count += isPrime[i];
  }

  free(isPrime);
  return prime_count;
}

number sieveByBlock(number limit, int nr_threads){

  number blockSize = 128 * 1024;
  char st[100];

  omp_set_num_threads(nr_threads);

  number start, prime_count = 0;

  clock_gettime(CLOCK_REALTIME, &startTime);

  // Main Loop
  #pragma omp parallel for reduction (+:prime_count)
    for (start = 2; start <= limit; start += blockSize){
      number end = start + blockSize;
      if (end > limit){
        end = limit;
      }

    prime_count += countByBlock(start, end);
  }
  clock_gettime(CLOCK_REALTIME, &endTime);

  double executionTime = ( endTime.tv_sec - startTime.tv_sec ) + (double)( endTime.tv_nsec - startTime.tv_nsec ) / (double)BILLION;
  sprintf(st, "\nTotal Time of execution: %3.3lf seconds\n\n", executionTime);
  cout << st;

  return prime_count;
}
/**/

/*Main*/
int main (int argc, char *argv[])
{
  /*Main execution*/
  char c;
  int nr_threads=1;
  number limit;
  int opt=0;

  if(argc < 2){
    cout <<
    endl << "Usage: ./openmp <nr> <opt> <?nr_threads>" <<
    endl << "opt:" <<
    endl << "1. Sequential Algorithm" <<
    endl << "2. Optimized (By block) Algorithm" <<
    endl;
    return 0;
  }else{
    limit = atoll(argv[1]);
    opt = atoi(argv[2]);

    if(argv[3])
      nr_threads = atoi(argv[3]);
  }

  switch(opt){
    case 1:
      cout << "Executing Sequential Algorithm" << endl;
      cout << "Number of primes to " << limit << ": " << sieveBySequence(limit, nr_threads) << endl << endl; 
      //TODO call naive
      break;
    case 2:
      cout << "Executing Optimized (By block) Algorithm" << endl;
      cout << "Number of primes to " << limit << ": " << sieveByBlock(limit, nr_threads) << endl << endl; 
      break;
    default:
      cout << "Wrong option! opt=" << opt << ". Please use 1 or 2." << endl;
      exit(0);
      break;
  }

}