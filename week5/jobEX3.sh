#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N ResEx3

# Redirect output stream to this file.
#$ -o ResEx3.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

#$ -l h_vmem=2G


# Set up any environment variables
export OMP_NUM_THREADS=8

# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0
gcc -O3 -std=c99 -fopenmp EX3Rec.c -o EX3.out
./EX3.out 1 5000000
./EX3.out 2 5000000
./EX3.out 3 5000000
./EX3.out 1 10000000
./EX3.out 2 10000000
./EX3.out 3 10000000
./EX3.out 1 15000000
./EX3.out 2 15000000
./EX3.out 3 15000000
./EX3.out 1 20000000
./EX3.out 2 20000000
./EX3.out 3 20000000

./EX3.out 4 5000000
./EX3.out 4 10000000
./EX3.out 4 15000000
./EX3.out 4 20000000