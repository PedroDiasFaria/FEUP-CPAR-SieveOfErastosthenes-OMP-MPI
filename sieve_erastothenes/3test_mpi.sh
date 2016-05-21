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
echo "Always using 8 Cores"
echo "Nr of Nodes = Nr of PCs"
echo ""
echo "Execute ./mpi"
echo ""
date


echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 1 Node -> Expected 9592"
mpirun --hostfile 1hostfile ./mpi HUNDRED_THOUSAND 1
date
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 2 Nodes -> Expected 9592"
mpirun --hostfile 2hostfile ./mpi HUNDRED_THOUSAND 1
date
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 3 Nodes -> Expected 9592"
mpirun --hostfile 3hostfile ./mpi HUNDRED_THOUSAND 1
date
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Segmented Sieve Algorithm with 4 Nodes -> Expected 9592"
mpirun --hostfile 4hostfile ./mpi HUNDRED_THOUSAND 1
date


echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 1 Node -> Expected 664579"
mpirun --hostfile 1hostfile ./mpi TEN_MILLION 1
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 2 Nodes -> Expected 664579"
mpirun --hostfile 2hostfile ./mpi TEN_MILLION 1
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 3 Nodes -> Expected 664579"
mpirun --hostfile 3hostfile ./mpi TEN_MILLION 1
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Segmented Sieve Algorithm with 4 Nodes -> Expected 664579"
mpirun --hostfile 4hostfile ./mpi TEN_MILLION 1
date


echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 1 Node -> Expected 2063689"
mpirun --hostfile 1hostfile ./mpi two_pow_25 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 2 Nodes -> Expected 2063689"
mpirun --hostfile 2hostfile ./mpi two_pow_25 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 3 Nodes -> Expected 2063689"
mpirun --hostfile 3hostfile ./mpi two_pow_25 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Segmented Sieve Algorithm with 4 Nodes -> Expected 2063689"
mpirun --hostfile 4hostfile ./mpi two_pow_25 1
date

echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 1 Node -> Expected 50847534"
mpirun --hostfile 1hostfile ./mpi BILLION 1
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 2 Nodes -> Expected 50847534"
mpirun --hostfile 2hostfile ./mpi BILLION 1
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 3 Nodes -> Expected 50847534"
mpirun --hostfile 3hostfile ./mpi BILLION 1
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Segmented Sieve Algorithm with 4 Nodes -> Expected 50847534"
mpirun --hostfile 4hostfile ./mpi BILLION 1
date


echo ""
echo ""
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 1 Node -> Expected 203280221"
mpirun --hostfile 1hostfile ./mpi two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 2 Nodes -> Expected 203280221"
mpirun --hostfile 2hostfile ./mpi two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 3 Nodes -> Expected 203280221"
mpirun --hostfile 3hostfile ./mpi two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Segmented Sieve Algorithm with 4 Nodes -> Expected 203280221"
mpirun --hostfile 4hostfile ./mpi two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "test_mpi.sh Done"
echo "--- --- --- --- --- --- --- ---"
