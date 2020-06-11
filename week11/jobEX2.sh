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
gcc -std=c99 -O3 EX2.c -o EX2
perf stat -e cache-misses ./EX2 1 0
perf stat -e cache-misses ./EX2 2 0
perf stat -e cache-misses ./EX2 3 0
perf stat -e cache-misses ./EX2 4 0
perf stat -e cache-misses ./EX2 5 0
perf stat -e cache-misses ./EX2 6 0
perf stat -e cache-misses ./EX2 7 0
perf stat -e cache-misses ./EX2 8 0
perf stat -e cache-misses ./EX2 9 0
perf stat -e cache-misses ./EX2 10 0
perf stat -e cache-misses ./EX2 11 0
perf stat -e cache-misses ./EX2 12 0
perf stat -e cache-misses ./EX2 13 0
perf stat -e cache-misses ./EX2 14 0
perf stat -e cache-misses ./EX2 15 0
perf stat -e cache-misses ./EX2 16 0
export OMP_NUM_THREADS=1
