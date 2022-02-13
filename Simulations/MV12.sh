#!/bin/bash
gcc -Wall -I/home/mario/gsl/include -c MV12.c 
gcc -L/home/mario/gsl/lib MV12.o -lgsl -lgslcblas -lm
LD_LIBRARY_PATH=/home/mario/gsl/lib
export LD_LIBRARY_PATH
GSL_RNG_SEED=456 GSL_RNG_TYPE="taus" ./a.out
