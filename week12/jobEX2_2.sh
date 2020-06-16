#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N ResEx2_2

# Redirect output stream to this file.
#$ -o ResEx2_2.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

#$ -l h_vmem=2G


# Set up any environment variables
#export OMP_NUM_THREADS=8

# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0
 gcc -std=c11 -O1 -fopenmp EX2_1.c -o EX2_1.out
perf stat -e r01C7 ./EX2_1.out
perf stat -e r02C7 ./EX2_1.out
perf stat -e r04C7 ./EX2_1.out
perf stat -e r08C7 ./EX2_1.out
perf stat -e r10C7 ./EX2_1.out
perf stat -e rF1C7 ./EX2_1.out
 gcc -std=c11 -O1 -fopenmp EX2_2.c -o EX2_2.out
perf stat -e r01C7 ./EX2_2.out
perf stat -e r02C7 ./EX2_2.out
perf stat -e r04C7 ./EX2_2.out
perf stat -e r08C7 ./EX2_2.out
perf stat -e r10C7 ./EX2_2.out
perf stat -e rF1C7 ./EX2_2.out
#export OMP_NUM_THREADS=1
