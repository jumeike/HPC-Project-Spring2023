# Makefile to build binaries and clean directory

CC = gcc
CC2 = ~/opt/opencilk/bin/clang
CFLAGS = -fopenmp
CFLAGS2 = -fopencilk 

all: qs-cilk qs-omp

qs-cilk:qs-cilk.c qs-omp
	$(CC2) $(CFLAGS2) -O3 $< -o $@
# $< signifies the first dependency while $^ signifies all dependencies
qs-omp:qs-omp.c
	$(CC) $(CFLAGS) -O3 $^ -o $@

# Target to delete the files
clean:
	rm -f *.txt
	rm -f qs-omp
	rm -f qs-cilk
	rm -f qs-tbb

