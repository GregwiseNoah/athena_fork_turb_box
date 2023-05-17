#!/bin/sh
#
#SBATCH -J !!JOB_NAME!!
#SBATCH -o !!JOB_NAME!!."%j".out
#SBATCH -e !!JOB_NAME!!."%j".err
#SBATCH --mail-user hitesh@mpa-garching.mpg.de
#SBATCH --partition=!!QUEUE!!
#SBATCH --mail-type=ALL
#SBATCH --nodes=!!NODES!!
#SBATCH --ntasks-per-node=!!NTASKS_PER_NODE!!
#SBATCH --time=!!TIME_LIMIT!!

set -e
SECONDS=0

module purge
module load intel/19.1.2
module load impi/2019.8
module load fftw-mpi/3.3.8
module load hdf5-mpi/1.8.21
module list

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HDF5_HOME/lib
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$FFTW_HOME/lib
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$I_MPI_ROOT/intel64/lib
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$I_MPI_ROOT/intel64/lib/release/

cd /ptmp/!!DIR_PATH_ADD!!hitesh/athena_fork_turb_box/!!WORK_DIR!!

cp ../!!TURB_DIR!!/Turb.hst ./
mv ../!!TURB_DIR!! ../Turbulence/

srun ./athena_turb -r !!RST_FILE!! -i !!INPUT_FILE!! -t !!TIME_LIMIT_RST!!

echo "Elapsed: $(($SECONDS / 3600))hrs $((($SECONDS / 60) % 60))min $(($SECONDS % 60))sec"

echo "Boom!"
