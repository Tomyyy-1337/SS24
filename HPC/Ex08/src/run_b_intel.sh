#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 0:10:00
#SBATCH -p skylake-96 
#SBATCH -o skylake_b.out
#SBATCH -e skylake_b.err
#SBATCH --mail-type=NONE			
#SBATCH -L impi			
#SBATCH --nodes=2		# requesting 2 nodes (identical -N 2)
#SBATCH --ntasks=4		# requesting 4 MPI tasks (identical -n 4)
#SBATCH --ntasks-per-node=2     # 2 MPI tasks will be started per node
#SBATCH --cpus-per-task=1       # each MPI task starts 4 OpenMP threads
#SBATCH --mem 10GB

module purge
module load intel/latest
mpiicpx -O3 -o main_alt main_alt.cpp

mpiexec.hydra ./main_alt
