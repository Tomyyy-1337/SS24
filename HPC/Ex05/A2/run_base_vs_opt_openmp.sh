#!/bin/bash



#SBATCH -J benchmark
#SBATCH -t 00:20
#SBATCH -p skylake-96
#SBATCH --cpus-per-task=1
#SBATCH -o benchmark_results.out
#SBATCH -e errors.err
#SBATCH --mail-type=NONE
#SBATCH --exclusive
#SBATCH -N 1
#SBATCH --mem 0


./diffusion_base_openmp

./diffusion_opt_openmp
