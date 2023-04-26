# Makefile to build binaries and clean directory

CC = gcc
CC2 = /opt/opencilk/bin/clang
CFLAGS = -fopenmp
CFLAGS2 = -fopencilk 

all: fib-cilk fib-omp

fib-cilk:fib-cilk.c fib-omp
	$(CC2) $(CFLAGS2) -O3 $< -o $@
# $< signifies the first dependency while $^ signifies all dependencies
fib-omp:fib-omp.c
	$(CC) $(CFLAGS) -O3 $^ -o $@

# Target to delete the files
clean:
	rm -f *.txt
	rm -f fib-omp
	rm -f fib-cilk

