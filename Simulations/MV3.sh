#!/bin/bash
gcc -Wall -I/home/mario/gsl/include -c MV3.c 
gcc -L/home/mario/gsl/lib MV3.o -lgsl -lgslcblas -lm
LD_LIBRARY_PATH=/home/mario/gsl/lib
export LD_LIBRARY_PATH
GSL_RNG_SEED=123 GSL_RNG_TYPE="mrg" ./a.out
