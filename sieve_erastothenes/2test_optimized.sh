#!/bin/bash
clear
echo "Execute Makefile"
make clean
make openmp
echo "--- --- --- --- --- --- --- ---"
echo ""
echo ""
echo "Testing Optimized (By segment) Algorithm in C/C++ - Shared Memory OpenMP"
echo "Execute ./openmp"
echo ""
date

echo ""
echo "1 thread"
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 1 thread -> Expected 9592"
./openmp HUNDRED_THOUSAND 2
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 1 thread -> Expected 664579"
./openmp TEN_MILLION 2
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 1 thread -> Expected 2063689"
./openmp two_pow_25 2
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 1 thread -> Expected 50847534"
./openmp BILLION 2
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 1 thread -> Expected 203280221"
./openmp two_pow_32 2
date

echo""
echo"2 threads"
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 2 threads -> Expected 9592"
./openmp HUNDRED_THOUSAND 2 2
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 2 threads-> Expected 664579"
./openmp TEN_MILLION 2 2
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 2 threads  -> Expected 2063689"
./openmp two_pow_25 2 2
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 2 threads -> Expected 50847534"
./openmp BILLION 2 2
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 2 threads -> Expected 203280221"
./openmp two_pow_32 2 2
date

echo""
echo"4 threads"
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 4 threads -> Expected 9592"
./openmp HUNDRED_THOUSAND 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 4 threads-> Expected 664579"
./openmp TEN_MILLION 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 4 threads  -> Expected 2063689"
./openmp two_pow_25 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 4 threads -> Expected 50847534"
./openmp BILLION 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 4 threads -> Expected 203280221"
./openmp two_pow_32 2 4
date


echo""
echo"8 threads"
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 8 threads -> Expected 9592"
./openmp HUNDRED_THOUSAND 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 8 threads-> Expected 664579"
./openmp TEN_MILLION 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 8 threads  -> Expected 2063689"
./openmp two_pow_25 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 8 threads -> Expected 50847534"
./openmp BILLION 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 8 threads -> Expected 203280221"
./openmp two_pow_32 2 8
date

echo "--- --- --- --- --- --- --- ---"
echo "test_optimized.sh Done"
echo "--- --- --- --- --- --- --- ---"
