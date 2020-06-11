#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N ResEx2

# Redirect output stream to this file.
#$ -o ResEx2.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

#$ -l h_vmem=2G


# Set up any environment variables
#export OMP_NUM_THREADS=8

# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0
 gcc -std=c99 -O1 -fopenmp EX2.c -o EX2.out
./EX2.out 0 1000
./EX2.out 0 500
./EX2.out 0 100
./EX2.out 1 1000
./EX2.out 1 500
./EX2.out 1 100
#export OMP_NUM_THREADS=1
