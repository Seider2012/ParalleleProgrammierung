#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N Result8

# Redirect output stream to this file.
#$ -o Result8.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

#$ -l h_vmem=2G


# Set up any environment variables
export OMP_NUM_THREADS=8


# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0

./EX1.out 1