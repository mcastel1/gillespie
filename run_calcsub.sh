#!/bin/bash
#PBS -l walltime=01:00:00
#PBS -l mem=1gb
#PBS -l nodes=1:ppn=1
#PBS -q batch
#PBS -N gillespie
##PBS -M michele.castellana@curie.fr
#PBS -e /data/users/mcastel1/gillespie/
#PBS -o /data/users/mcastel1/gillespie/


cd /data/users/mcastel1/gillespie/

g++ -O3 -o main.o -I ./ -lgsl -lgslcblas -lm main.cpp -Wall -I/usr/include/gsl

./main.o -N 128 -S 5 -s 0
./main.o -N 128 -S 6 -s 0
./main.o -N 128 -S 7 -s 0
