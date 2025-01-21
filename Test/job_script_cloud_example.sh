#!/bin/sh
#
#SBATCH -J m00M01
#SBATCH -o m00M01."%j".out
#SBATCH -e m00M01."%j".err
#SBATCH --mail-user hitesh@mpa-garching.mpg.de
#SBATCH --partition=p.test
#SBATCH --mail-type=ALL
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --time=00:29:00

set -e
SECONDS=0

module purge
module load intel/19.1.2
module load impi/2019.8
module load fftw-mpi/3.3.8
module load hdf5-mpi/1.8.21
module list

cd /ptmp/hitesh/athena_fork_turb_box/turb_v2/para_scan_Rlsh0_5_res0_256_rseed_1_M_0.25_chi_100_beta_100/

srun ./athena_turb  -i athinput_cloud.turb -t 00:25:00

echo "Elapsed: $(($SECONDS / 3600))hrs $((($SECONDS / 60) % 60))min $(($SECONDS % 60))sec"

echo "Boom!"
