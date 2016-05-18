/*
Program in C++ to test Sieve of Erastosthenes
(i)in sequential mode, on a single CPU-Core;
(ii)in parallel, on a shared memory system, using OpenMP
*/

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
const int L1 = 128;   //256;   //L1 cache size  - 128@FEUP; 256@Home
const int L2 = 1024;  //L2 cache size
const int DEBUG = 0;

/*Primes Calculation*/
number sieveBySequence(number upperBound, int nr_threads){
  number i, j;

  number prime_arraySize = upperBound + 1;

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

  for(i = 2; i*i < prime_arraySize; i++) {
  	if(isPrime[i] == 1) {
  			for (j = 2; j*i < prime_arraySize ; j++) {
  				isPrime[i*j] = 0;
  			}
  		}
  	}

  number prime_count = 0;

  for (i = 2	; i < prime_arraySize; i++) {
    if (isPrime[i]) {
      prime_count++;
    }
  }

  cout << endl;

  clock_gettime(CLOCK_REALTIME, &endTime);

  double executionTime = ( endTime.tv_sec - startTime.tv_sec ) + (double)( endTime.tv_nsec - startTime.tv_nsec ) / (double)BILLION;
  cout << "\nTotal Time of execution: " << setprecision(3) << executionTime << " seconds" << endl << endl;

  free(isPrime);
  return prime_count;
}


//Segmented Sieve
number countByBlock(number lowerBound, number upperBound) {

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

  for(i = 0; i <= prime_arraySize; i++){
    isPrime[i] = 1;
  }

  //For optimization purpose, we calculate comparable variables
  //out of the for() statement
  number iSquare;
  //Segmented Sieve for odd numbers
  for (i = 3, iSquare=i*i; iSquare <= upperBound; i+=2, iSquare=i*i){

    // Skip numbers before block's range
    //cout << "LBound = " << lowerBound << " | UBound = " << upperBound << endl;
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
      if(DEBUG)
        cout << "\t   startValue is <= upperBound so nonPrimeIndex= " << nonPrimeIndex << ". j= " << j << ". isPrime[" << nonPrimeIndex/2 <<"] = 0." << endl;
    }
  }

  if(DEBUG)
  cout << "Iteration ended at i= " << i << endl;

  //Counting primes on array
  number prime_count = 0;

  // 2 is the only even prime number, added to the count if it's in the block
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

number sieveByBlock(number upperBound, int nr_threads){

  //TODO adjust size!

  number blockSize;
  if(DEBUG)
  blockSize = 100;
  if(!DEBUG)
  blockSize = L1 * L2;

  number blockLowerBound, prime_count = 0;

  omp_set_num_threads(nr_threads);
  clock_gettime(CLOCK_REALTIME, &startTime);

  // Main Loop
  #pragma omp parallel for reduction (+:prime_count)
    for (blockLowerBound = 2; blockLowerBound <= upperBound; blockLowerBound += blockSize){
      number blockUpperBound = blockLowerBound + blockSize;
      if (blockUpperBound > upperBound){
        blockUpperBound = upperBound;
      }

    prime_count += countByBlock(blockLowerBound, blockUpperBound);
  }
  clock_gettime(CLOCK_REALTIME, &endTime);

  double executionTime = ( endTime.tv_sec - startTime.tv_sec ) + (double)( endTime.tv_nsec - startTime.tv_nsec ) / (double)BILLION;
  cout << "\nTotal Time of execution: " << setprecision(3) << executionTime << " seconds" << endl << endl;

  return prime_count;
}
/**/

/*Main*/
int main (int argc, char *argv[])
{
  /*Main execution*/
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
      cout << "Executing Sequential Algorithm" << endl;
      cout << "Number of primes to " << limit << ": " << sieveBySequence(limit, nr_threads) << endl << endl;
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
