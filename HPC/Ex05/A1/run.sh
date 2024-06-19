#!/bin/bash



#SBATCH -J benchmark
#SBATCH -t 08:00 
#SBATCH -p epyc-256
#SBATCH --cpus-per-task=1
#SBATCH -o benchmark_results.out
#SBATCH -e errors.err
#SBATCH --mail-type=NONE
#SBATCH --exclusive
#SBATCH -N 1
#SBATCH --mem 0

for i in $(seq $SLURM_CPUS_ON_NODE); do
OMP_NUM_THREADS=$i ./task1
done
