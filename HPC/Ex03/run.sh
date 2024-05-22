#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 00:30 
#SBATCH -p skylake-96
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=2000
#SBATCH -o benchmark_results.out
#SBATCH -e errors.err
#SBATCH --mail-type=NONE

lscpu
./benchmark