#!/bin/bash
clear
echo "Execute Makefile"
make clean
make mpi
echo "--- --- --- --- --- --- --- ---"
echo ""
echo ""
echo "Testing MPI system in C/C++ - Distributed Memory System - Using only MPI"
echo "NOTE:"
echo "x Core represents x Cores on each CPU"
echo "Always using 4 Nodes (PCs)"
echo ""
echo "Execute ./mpi"
echo ""
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 1 Core -> Expected 2063689"
mpirun --hostfile 1hostfile ./mpi two_pow_25 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 4 Cores -> Expected 2063689"
mpirun --hostfile 4hostfile ./mpi two_pow_25 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 8 Cores -> Expected 2063689"
mpirun --hostfile 8hostfile ./mpi two_pow_25 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 1 Core -> Expected 203280221"
mpirun --hostfile 1hostfile ./mpi two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 4 Cores -> Expected 203280221"
mpirun --hostfile 4hostfile ./mpi two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 8 Cores -> Expected 203280221"
mpirun --hostfile 8hostfile ./mpi two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "test_mpi.sh Done"
echo "--- --- --- --- --- --- --- ---"