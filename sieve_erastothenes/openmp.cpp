/*
Program in C++ to test Sieve of Erastosthenes
(i)in sequential mode, on a single CPU-Core;
(ii)in parallel, on a shared memory system, using OpenMP by segments

based on
https://gist.github.com/coderplay/3711760
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
const number HUNDRED_THOUSAND = 100000;
const number TEN_MILLION = 10000000;
const number BILLION = 1000000000;
const number two_pow_25 = 33554432;
const number two_pow_32 = 4294967296;
const int L1 = 128;   //256;   //L1 cache size  - 128@FEUP; 256@Home
const int L2 = 1024;  //L2 cache size

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

  clock_gettime(CLOCK_REALTIME, &startTime);

  for(i = 0; i < prime_arraySize; i++){
    isPrime[i] = 1;
  }

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
  cout << "\nTotal Time of execution: " << setprecision(6) << executionTime << " seconds" << endl << endl;

  free(isPrime);
  return prime_count;
}


//Segmented Sieve
number countBySegment(number lowerBound, number upperBound) {

  number i, j;
  //All odd numbers set to primes
  //Since only odd numbers can be primes, we trim down the array to half it's size
  //(excluding all even numbers from the start)
  number prime_arraySize = (upperBound - lowerBound + 1)/2; //+1 to include the last number
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

    if (startValue < i*i) {
      startValue = i*i;
    }

    //We only calculate from odd numbers
    if ((startValue % 2) == 0){
      startValue += i;
    }

    //Optimization purpose
    number iDouble = 2*i;
    //Removing all non-prime odds
    for (j = startValue; j<=upperBound; j+=iDouble){
      number nonPrimeIndex = (j - lowerBound)/2;
      isPrime[nonPrimeIndex] = 0;
    }
  }

  //Counting primes on array
  // 2 is the only even prime number, added to the count if it's in the segment
  number prime_count = (lowerBound == 2);

  for (i = 0; i < prime_arraySize; i++) {
    prime_count += isPrime[i];
  }

  free(isPrime);
  return prime_count;
}

number sieveBySegment(number upperBound, int nr_threads){

  number segmentSize;
  segmentSize = L1 * L2;

  number segmentLowerBound, prime_count = 0;

  clock_gettime(CLOCK_REALTIME, &startTime);

  // Main Loop
  #pragma omp parallel for reduction (+:prime_count) schedule(dynamic) num_threads(nr_threads)
    for (segmentLowerBound = 2; segmentLowerBound <= upperBound; segmentLowerBound += segmentSize){
      number segmentUpperBound = segmentLowerBound + segmentSize - 1;
      if (segmentUpperBound > upperBound){
        segmentUpperBound = upperBound;
      }

    prime_count += countBySegment(segmentLowerBound, segmentUpperBound);
  }
  clock_gettime(CLOCK_REALTIME, &endTime);

  double executionTime = ( endTime.tv_sec - startTime.tv_sec ) + (double)( endTime.tv_nsec - startTime.tv_nsec ) / (double)BILLION;
  cout << "\nTotal Time of execution: " << setprecision(6) << executionTime << " seconds" << endl << endl;

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
    endl << "2. Optimized (By segment) Algorithm" <<
    endl;
    return 0;
  }else{

    opt = atoi(argv[2]);
    if(strcmp(argv[1], "two_pow_25") == 0){
      limit = two_pow_25;
    }else if(strcmp(argv[1], "two_pow_32") == 0){
      limit = two_pow_32;
    }else if(strcmp(argv[1],"HUNDRED_THOUSAND") == 0){
      limit = HUNDRED_THOUSAND;
    }else if(strcmp(argv[1],"TEN_MILLION") == 0){
      limit = TEN_MILLION;
    }else if(strcmp(argv[1],"BILLION") == 0){
      limit = BILLION;
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
      cout << "Executing Optimized (By Segment) Algorithm" << endl;
      cout << "Number of primes to " << limit << ": " << sieveBySegment(limit, nr_threads) << endl << endl;
      break;
    default:
      cout << "Wrong option! opt=" << opt << ". Please use 1 or 2." << endl;
      exit(0);
      break;
  }

}
