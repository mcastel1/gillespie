#!/bin/sh
#SBATCH --job-name=gillespie
#SBATCH --time=00-00:30:00
##SBATCH --mail-user=michele.castellana@curie.fr --mail-type=ALL
#SBATCH --clusters=mesopsl2
#SBATCH --qos=mesopsl2_def_long
#SBATCH --account=castellana
##SBATCH --partition=hi
#SBATCH --ntasks-per-node=1
#SBATCH --nodes=1

RUN="/obs/mcastellana/gillespie/"
#OUT="/travail/mcastellana/an1/"
#IN="/travail/mcastellana/mc1plus2/"

cd $RUN
gcc main.cpp  -I/usr/include/gsl -lstdc++  -lgsl -lgslcblas -lm -O3 -Wno-deprecated -o main.o -Wall -DHAVE_INLINE

./main.o -s 0 -S 6

