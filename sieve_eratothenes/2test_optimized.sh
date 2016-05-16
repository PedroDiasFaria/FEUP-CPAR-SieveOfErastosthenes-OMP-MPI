#!/bin/bash
clear
echo "Execute Makefile"
make clean
make
echo "--- --- --- --- --- --- --- ---"
echo ""
echo ""
echo "Testing Optimized (By block) Algorithm in C/C++ - Shared Memory OpenMP"
echo "Execute ./openmp"
echo ""
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Basic Algorithm -> Expected 2063689"
./openmp two_pow_25 2
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Basic Algorithm -> Expected 203280221"
./openmp two_pow_32 2
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Basic Algorithm with 8 threads  -> Expected 2063689"
./openmp two_pow_25 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Basic Algorithm with 8 threads -> Expected 203280221"
./openmp two_pow_32 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "test_optimized.sh Done"
echo "--- --- --- --- --- --- --- ---"