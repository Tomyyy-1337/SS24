#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 0:10:00
#SBATCH -p epyc-256
#SBATCH -o epyc_2a.out
#SBATCH -e epyc_2a.err
#SBATCH --mail-type=NONE
#SBATCH -N 1
#SBATCH --ntasks-per-node=2
#SBATCH --mem 2GB

module purge
module load openmpi/latest
mpic++ -O3 -o main2 main2.cpp

echo "Running main on 1 node with 2 tasks per node"
mpirun ./main2

module purge