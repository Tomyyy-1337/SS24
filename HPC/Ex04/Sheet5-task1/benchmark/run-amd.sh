#!/bin/bash



#SBATCH -J benchmark
#SBATCH -t 17:00 
#SBATCH -p epyc-256
#SBATCH --cpus-per-task=1
#SBATCH -o benchmark_results_amd.out
#SBATCH -e errors_amd.err
#SBATCH --mail-type=NONE
#SBATCH --exclusive
#SBATCH -N 1
#SBATCH --mem 0

lscpu

for i in $(seq $SLURM_CPUS_ON_NODE); do
OMP_NUM_THREADS=$i ./stream
done
