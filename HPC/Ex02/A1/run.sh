#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 00:30 
#SBATCH -p skylake-96
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=3000
#SBATCH -o benchmark_results.out
#SBATCH -e errors.err
#SBATCH --mail-type=NONE

lstopo topo.png
lscpu
./noavx
./avx