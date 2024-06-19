#!/bin/bash



#SBATCH -J benchmark
#SBATCH -t 0:05:00
#SBATCH -p skylake-96
#SBATCH --cpus-per-task=1
#SBATCH -o taskbench_skylake.out
#SBATCH -e taskbench_skylake.err
#SBATCH --mail-type=NONE
#SBATCH --exclusive
#SBATCH -N 1
#SBATCH --mem 0

num_cores=(1 2 3 4 5 6 7 8 9 10 11 12) 


for i in ${num_cores[@]}; do
OMP_NUM_THREADS=$i ./taskbench
done
