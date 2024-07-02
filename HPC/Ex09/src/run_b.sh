#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 0:10:00
#SBATCH -p epyc-256
#SBATCH -o epyc_b.out
#SBATCH -e epyc_b.err
#SBATCH --mail-type=NONE
#SBATCH -N 2
#SBATCH --ntasks-per-node=1
#SBATCH --mem 2GB

module purge
module load openmpi/latest
mpic++ -O3 -o main main.cpp

echo "Running main on 2 nodes with 1 task per node"
mpirun ./main

module purge