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
export OMP_NUM_THREADS=1


# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0
gcc -O0 -std=c99 -fopenmp EX2.c -o EX2.out
gcc -O0 -std=c99 -fopenmp EX2Spr.c -o EX2Spr.out
gcc -O0 -std=c99 -fopenmp EX2Clo.c -o EX2Clo.out
./EX2.out 1500
./EX2Spr.out 1500
./EX2Clo.out 1500
export OMP_NUM_THREADS=2
./EX2.out 1500
./EX2Spr.out 1500
./EX2Clo.out 1500
export OMP_NUM_THREADS=4
./EX2.out 1500
./EX2Spr.out 1500
./EX2Clo.out 1500
export OMP_NUM_THREADS=8
./EX2.out 1500
./EX2Spr.out 1500
./EX2Clo.out 1500
export OMP_PLACES=threads(4)
export OMP_NUM_THREADS=1
./EX2.out 1500
./EX2Spr.out 1500
./EX2Clo.out 1500
export OMP_NUM_THREADS=2
./EX2.out 1500
./EX2Spr.out 1500
./EX2Clo.out 1500
export OMP_NUM_THREADS=4
./EX2.out 1500
./EX2Spr.out 1500
./EX2Clo.out 1500
export OMP_NUM_THREADS=8
./EX2.out 1500
./EX2Spr.out 1500
./EX2Clo.out 1500