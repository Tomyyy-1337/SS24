#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 0:10:00
#SBATCH -p epyc-256
#SBATCH -o epyc_a.out
#SBATCH -e epyc_a.err
#SBATCH --mail-type=NONE
#SBATCH -n 4
#SBATCH --mem 10000

module purge
module load openmpi/latest
mpic++ -O3 -o main main.cpp
mpic++ -O3 -o main_alt main_alt.cpp

echo "Running main"
mpirun ./main
echo "Running main_alt"
mpirun ./main_alt

module purge