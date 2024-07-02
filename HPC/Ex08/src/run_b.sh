#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 0:10:00
#SBATCH -p epyc-256
#SBATCH -o epyc_b.out
#SBATCH -e epyc_b.err
#SBATCH --mail-type=NONE
#SBATCH -N 2
#SBATCH --ntasks-per-node=2
#SBATCH --mem 10GB

module purge
module load openmpi/latest
mpic++ -O3 -o main_alt main_alt.cpp

echo "Running main_alt"
mpirun ./main_alt

module purge