#!/bin/bash



#SBATCH -J benchmark
#SBATCH -t 10:00
#SBATCH -p skylake-96
#SBATCH --cpus-per-task=1
#SBATCH -o benchmark_results.out
#SBATCH -e errors.err
#SBATCH --mail-type=NONE
#SBATCH --exclusive
#SBATCH -N 1
#SBATCH --mem 200


./diffusion_base

./diffusion_opt
