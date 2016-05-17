#!/bin/bash
clear
echo "Execute Makefile - NOT COMPLETE - NEED TO USE THE HOSTFILE AND NR CORES"
make mpi
echo "--- --- --- --- --- --- --- ---"
echo ""
echo ""
echo "Testing MPI system in C/C++ - Distributed Memory System - Using only MPI"
echo "Execute ./mpi"
echo ""
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm -> Expected 2063689"
./mpi two_pow_25 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm -> Expected 203280221"
./openmp two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 8 threads  -> Expected 2063689"
./openmp two_pow_25 1 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 8 threads -> Expected 203280221"
./openmp two_pow_32 1 8
date
echo "--- --- --- --- --- --- --- ---"
echo "test_optimized.sh Done"
echo "--- --- --- --- --- --- --- ---"
#tem que ser com mpirun
