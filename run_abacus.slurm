#!/bin/bash
#SBATCH --job-name=gillespie
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --mem=1gb
#SBATCH --time=00:05:00
##SBATCH --account=recherche_prod
#SBATCH --partition=dev


RUN="/mnt/beegfs/home/mcastel1/gillespie"
OUT="/mnt/beegfs/gillespie"

rm -rf $OUT
mkdir $OUT

cd $RUN

g++ main.cpp -I /mnt/beegfs/home/mcastel1/gsl/include/gsl  -I/mnt/beegfs/home/mcastel1/gsl/include/ -L/mnt/beegfs/home/mcastel1/gsl/lib/ -lgsl -lgslcblas -lm -O3 -Wno-deprecated  -o  main.o -DHAVE_INLINE

#./main.o -N 16 -S 6 -s 0 -o $OUT
#./main.o -N 32 -S 6 -s 0 -o $OUT
#./main.o -N 64 -S 6 -s 0 -o $OUT
./main.o -N 128 -S 5 -s 0 -o $OUT
