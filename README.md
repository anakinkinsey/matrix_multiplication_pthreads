# matrix_multiplication

## Overview

Helper files to show the benefits of threading when performing matrix multiplication.

## How to run

run `make` to execute the makefile. This will compile the binaries listed below

## Helper functions
make-matrix
  - generates an mxn matrix and populates it with rand numbers
  - execute with `./make-matrix -m ## -n ## -l ## -u ## -o outputFile` with the following flags
    -m: rows
    -n: columns
    -l: lower bound for rand number generator
    -u: upper bound
    -o outputfile (typically in the form of #.dat)
print-matrix
  - prints a matrix created with make-matrix
  - execute with `print-matrix -i infile.dat`
pth_mat_vect_rand_split.c
 - multiplies two matrices together and outputs the resultant matrix and time stats. This is done in the form of Ax=y
 - execute with `./pth_mat_vect_rand_split  -t <thread_count> -A <A.dat> -x <x.dat> -y <y.dat>`
  -t: number of threads to process with
  -A: input matrix
  -x: input matrix
  -y: output matrix
 
