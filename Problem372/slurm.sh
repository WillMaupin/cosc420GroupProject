#!/bin/bash

#SBATCH --job-name=pencilsOfRays
#SBATCH --ntasks=128
#SBATCH --mem=2gb
#SBATCH --time=24:05:00    # Time limit in the form hh:mm:ss
#SBATCH --output=out/%j.log

module load mpi/openmpi3-x86_64


# For a C MPI project
mpirun ~/COSC420/Project1/Problem372/por
