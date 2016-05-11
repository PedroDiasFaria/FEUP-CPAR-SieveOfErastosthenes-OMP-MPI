#!/bin/bash

echo "Execute Makefile"
make clean
make

echo "Testing Optimized (By block) Algorithm in C/C++"
echo "Execute ./openmp"
echo ""
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Basic Algorithm"
./openmp 33554432 2
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Basic Algorithm"
./openmp 4294967296 2
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Basic Algorithm with 8 threads"
./openmp 33554432 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Basic Algorithm with 8 threads"
./openmp 4294967296 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "test_sequential.sh Done"
echo "--- --- --- --- --- --- --- ---"