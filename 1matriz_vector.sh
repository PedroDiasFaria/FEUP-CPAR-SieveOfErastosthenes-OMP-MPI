#!/bin/bash

echo "Execute Makefile"
make clean
make

date

mpirun --hostfile hostfile -np 4 matrizvector