#!/bin/bash

#SBATCH -J hello_world
#SBATCH -t 05:00 
#SBATCH -p skylake-96
#SBATCH --ntasks=3
#SBATCH --cpus-per-task=1
#SBATCH --mem=800
#SBATCH -o hello_world.out
#SBATCH -e hello_world.err
#SBATCH --mail-type=NONE

lstopo topo.png
lscpu
./hello_world_gcc_9_5
./hello_world_gcc_13_2
./hello_world_icx
