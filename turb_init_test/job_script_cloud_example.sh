#!/bin/sh
#
#SBATCH -J turb_01
#SBATCH -o turb_01."%j".out	
#SBATCH -e turb_01."%j".err
#SBATCH --mail-user ashwin.george@uni-potsdam.de
#SBATCH --partition=p.test
#SBATCH --mail-type=ALL
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH --time=00:29:00

set -e
SECONDS=0

module purge
module load intel/19.1.2
module load impi/2019.8
module load fftw-mpi/3.3.8
module load hdf5-mpi/1.8.21
module list

cd /u/ageorge/athena_fork_turb_box/

srun ./bin/athena -i Test/athinput.turb -t 00:25:00

echo "Elapsed: $(($SECONDS / 3600))hrs $((($SECONDS / 60) % 60))min $(($SECONDS % 60))sec"

echo "Boom!"
