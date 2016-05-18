#!/bin/bash
clear
echo "Execute Makefile"
make clean
make hybrid
echo "--- --- --- --- --- --- --- ---"
echo ""
echo ""
echo "Testing Hybrid system in C/C++ - Distributed Memory System With Shared Memory - Using MPI/OpenMP"
echo "NOTE:"
echo "x Core represents x Cores on each CPU		AND 	y Thread represents y Threads on each Core"
echo "Always using 4 Nodes (PCs)"
echo ""
echo "Execute ./mpi"
echo ""
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 1 Core & 1 Thread-> Expected 2063689"
mpirun --hostfile 1hostfile ./mpi two_pow_25 2 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 1 Core & 4 Thread-> Expected 2063689"
mpirun --hostfile 1hostfile ./mpi two_pow_25 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 1 Core & 8 Thread-> Expected 2063689"
mpirun --hostfile 1hostfile ./mpi two_pow_25 2 8
date

echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 4 Cores & 1 Thread -> Expected 2063689"
mpirun --hostfile 4hostfile ./mpi two_pow_25 2 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 4 Cores & 4 Thread-> Expected 2063689"
mpirun --hostfile 4hostfile ./mpi two_pow_25 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 4 Cores & 8 Thread -> Expected 2063689"
mpirun --hostfile 4hostfile ./mpi two_pow_25 2 8
date

echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 8 Cores & 1 Thread-> Expected 2063689"
mpirun --hostfile 8hostfile ./mpi two_pow_25 2 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 8 Cores & 4 Thread-> Expected 2063689"
mpirun --hostfile 8hostfile ./mpi two_pow_25 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 8 Cores & 8 Thread -> Expected 2063689"
mpirun --hostfile 8hostfile ./mpi two_pow_25 2 8
date

echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 1 Core & 1 Thread-> Expected 203280221"
mpirun --hostfile 1hostfile ./mpi two_pow_32 2 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 1 Core & 4 Thread -> Expected 203280221"
mpirun --hostfile 1hostfile ./mpi two_pow_32 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 1 Core & 8 Thread-> Expected 203280221"
mpirun --hostfile 1hostfile ./mpi two_pow_32 2 8
date


echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 4 Cores & 1 Thread -> Expected 203280221"
mpirun --hostfile 4hostfile ./mpi two_pow_32 2 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 4 Cores & 4 Thread -> Expected 203280221"
mpirun --hostfile 4hostfile ./mpi two_pow_32 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 4 Cores & 8 Thread -> Expected 203280221"
mpirun --hostfile 4hostfile ./mpi two_pow_32 2 8
date

echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 8 Cores & 1 Thread -> Expected 203280221"
mpirun --hostfile 8hostfile ./mpi two_pow_32 2 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 8 Cores & 4 Thread -> Expected 203280221"
mpirun --hostfile 8hostfile ./mpi two_pow_32 2 4
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 8 Cores & 8 Thread -> Expected 203280221"
mpirun --hostfile 8hostfile ./mpi two_pow_32 2 8
date

echo "--- --- --- --- --- --- --- ---"
echo "test_hybrid.sh Done"
echo "--- --- --- --- --- --- --- ---"	