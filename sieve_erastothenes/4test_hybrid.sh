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
echo "Always using 8 Threads PER Core   AND   8 Cores PER node"
echo "Nr of Nodes = Nr of PCs"
echo "Execute ./mpi"
echo ""
date

echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 1 Node, 8 Cores and 8 Threads -> Expected 9592"
mpirun --hostfile 1hostfile ./mpi HUNDRED_THOUSAND 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 2 Nodes, 8 Cores and 8 Threads  -> Expected 9592"
mpirun --hostfile 2hostfile ./mpi HUNDRED_THOUSAND 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 3 Nodes, 8 Cores and 8 Threads  -> Expected 9592"
mpirun --hostfile 3hostfile ./mpi HUNDRED_THOUSAND 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 4 Nodes, 8 Cores and 8 Threads  -> Expected 9592"
mpirun --hostfile 4hostfile ./mpi HUNDRED_THOUSAND 2 8
date


echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 1 Node, 8 Cores and 8 Threads  -> Expected 664579"
mpirun --hostfile 1hostfile ./mpi TEN_MILLION 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 2 Nodes, 8 Cores and 8 Threads  -> Expected 664579"
mpirun --hostfile 2hostfile ./mpi TEN_MILLION 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 3 Nodes, 8 Cores and 8 Threads  -> Expected 664579"
mpirun --hostfile 3hostfile ./mpi TEN_MILLION 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 4 Nodes, 8 Cores and 8 Threads  -> Expected 664579"
mpirun --hostfile 4hostfile ./mpi TEN_MILLION 2 8
date


echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 1 Node, 8 Cores and 8 Threads  -> Expected 2063689"
mpirun --hostfile 1hostfile ./mpi two_pow_25 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 2 Nodes, 8 Cores and 8 Threads  -> Expected 2063689"
mpirun --hostfile 2hostfile ./mpi two_pow_25 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 3 Nodes, 8 Cores and 8 Threads  -> Expected 2063689"
mpirun --hostfile 3hostfile ./mpi two_pow_25 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 4 Nodes, 8 Cores and 8 Threads  -> Expected 2063689"
mpirun --hostfile 4hostfile ./mpi two_pow_25 2 8
date

echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 1 Node, 8 Cores and 8 Threads  -> Expected 50847534"
mpirun --hostfile 1hostfile ./mpi BILLION 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 2 Nodes, 8 Cores and 8 Threads  -> Expected 50847534"
mpirun --hostfile 2hostfile ./mpi BILLION 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 3 Nodes, 8 Cores and 8 Threads  -> Expected 50847534"
mpirun --hostfile 3hostfile ./mpi BILLION 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 4 Nodes, 8 Cores and 8 Threads  -> Expected 50847534"
mpirun --hostfile 4hostfile ./mpi BILLION 2 8
date


echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 1 Node, 8 Cores and 8 Threads  -> Expected 203280221"
mpirun --hostfile 1hostfile ./mpi two_pow_32 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 2 Nodes, 8 Cores and 8 Threads  -> Expected 203280221"
mpirun --hostfile 2hostfile ./mpi two_pow_32 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 3 Nodes, 8 Cores and 8 Threads  -> Expected 203280221"
mpirun --hostfile 3hostfile ./mpi two_pow_32 2 8
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 4 Nodes, 8 Cores and 8 Threads  -> Expected 203280221"
mpirun --hostfile 4hostfile ./mpi two_pow_32 2 8
date


echo "--- --- --- --- --- --- --- ---"
echo "test_hybrid.sh Done"
echo "--- --- --- --- --- --- --- ---"
