#!/bin/bash

#SBATCH -J benchmark
#SBATCH -t 0:10:00
#SBATCH -p skylake-96
#SBATCH -o skylake_a.out
#SBATCH -e skylake_a.err
#SBATCH --mail-type=NONE	
#SBATCH -L impi			
#SBATCH --nodes=1		# requesting 2 nodes (identical -N 2)
#SBATCH --ntasks=4		# requesting 4 MPI tasks (identical -n 4)
#SBATCH --ntasks-per-node=4     # 2 MPI tasks will be started per node
#SBATCH --cpus-per-task=1       # each MPI task starts 4 OpenMP threads
#SBATCH --mem 10GB

module purge
module load intel/latest
mpiicpx -O3 -o main main.cpp
mpiicpx -O3 -o main_alt main_alt.cpp

echo "Main:"
mpiexec.hydra ./main
echo "Main_alt:"
mpiexec.hydra ./main_alt