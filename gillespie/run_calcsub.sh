#!/bin/bash
#PBS -l walltime=00:10:00
#PBS -l mem=1gb
#PBS -l nodes=1:ppn=1
#PBS -q batch
#PBS -N gillespie
##PBS -M michele.castellana@curie.fr
#PBS -e /data/users/mcastel1/gillespie/
#PBS -o /data/users/mcastel1/gillespie/


cd /data/users/mcastel1/gillespie/
g++ -O3 -o rescaling_vii_cr.o -I ./ -lgsl -lgslcblas -lm rescaling_vii_cr.cpp -Wall


#timeout -s TERM 240h ./rescaling_vii_cr.o -s 0.9 -T 20 -N 256 -S 8 -Q 18 -R 8 -o /data/tmp/mcastel1/rg1/
