#!/bin/bash
gcc -Wall -I/home/mario/gsl/include -c traj.c 
gcc -L/home/mario/gsl/lib traj.o -lgsl -lgslcblas -lm
LD_LIBRARY_PATH=/home/mario/gsl/lib
export LD_LIBRARY_PATH
GSL_RNG_SEED=345 GSL_RNG_TYPE="ran3" ./a.out
