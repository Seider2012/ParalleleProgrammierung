#!/bin/bash

# Executes job in the queue "std.q" unless you have special requirements.
#$ -q std.q

# Changes to the current working directory before performing any further action
#$ -cwd

# Name of your job. Unless you use the -o and -e options, output will
# go to a unique file name.ojob_id for each job.
#$ -N Result

# Redirect output stream to this file.
#$ -o Result.dat

# Join the error stream to the output stream.
#$ -j yes

# Parallel environment for using OpenMP, allocates 8 cores on a single node
#$ -pe openmp 8

# Use gcc 8.2.0 as the default gcc
module load gcc/8.2.0

./EX2.out 0 10000 0
./EX2.out 0 20000 0
./EX2.out 0 30000 0
./EX2.out 1 10000 0
./EX2.out 1 20000 0
./EX2.out 1 30000 0
./EX2.out 3 10000 0
./EX2.out 3 20000 0
./EX2.out 3 30000 0
./EX2.out 4 10000 0
./EX2.out 4 20000 0
./EX2.out 4 30000 0
./EX2.out 3 10000 1
./EX2.out 3 20000 1
./EX2.out 3 30000 1
./EX2.out 4 10000 1
./EX2.out 4 20000 1
./EX2.out 4 30000 1
./EX2.out 3 10000 2
./EX2.out 3 20000 2
./EX2.out 3 30000 2
./EX2.out 4 10000 2
./EX2.out 4 20000 2
./EX2.out 4 30000 2