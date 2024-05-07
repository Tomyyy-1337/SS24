#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 00:10 
#SBATCH -p skylake-96
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=10
#SBATCH -o benchmark_results.out
#SBATCH -e errors.err
#SBATCH --mail-type=NONE

lstopo topo.png
lscpu
./version1
./version2
./version3
./version4
./version5