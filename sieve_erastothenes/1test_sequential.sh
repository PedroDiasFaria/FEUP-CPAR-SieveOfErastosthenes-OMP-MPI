#!/bin/bash
clear
echo "Execute Makefile"
make openmp
echo "--- --- --- --- --- --- --- ---"
echo ""
echo ""
echo "Testing Sequential Algorithm in C/C++ - Single Core"
echo "Execute ./openmp"
echo ""
date
echo "--- --- --- --- --- --- --- ---"
echo "HUNDRED_THOUSAND Basic Algorithm -> Expected 9592"
./openmp HUNDRED_THOUSAND 1
date
echo "--- --- --- --- --- --- --- ---"
echo "TEN_MILLION Basic Algorithm -> Expected 664579"
./openmp TEN_MILLION 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^25 Basic Algorithm -> Expected 2063689"
./openmp two_pow_25 1
date
echo "--- --- --- --- --- --- --- ---"
echo "BILLION Basic Algorithm -> Expected 50847534"
./openmp BILLION 1
date
echo "--- --- --- --- --- --- --- ---"
echo "2^32 Basic Algorithm -> Expected 203280221"
./openmp two_pow_32 1
date
echo "--- --- --- --- --- --- --- ---"
echo "test_sequential.sh Done"
echo "--- --- --- --- --- --- --- ---"
