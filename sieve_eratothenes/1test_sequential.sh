#!/bin/bash

echo "Execute Makefile"
make clean
make

echo "Testing Sequential Algorithm in C/C++"
echo "Execute ./openmp"
echo ""
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Basic Algorithm"
./openmp 33554432 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Basic Algorithm"
./openmp 4294967296 1
date
echo "--- --- --- --- --- --- --- ---"
echo "test_sequential.sh Done"
echo "--- --- --- --- --- --- --- ---"