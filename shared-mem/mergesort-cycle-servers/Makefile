# Makefile to build binaries and clean directory

CC = g++
CC2 = ~/opt/opencilk/bin/clang++
CFLAGS = -fopenmp
CFLAGS2 = -fopencilk 

all: ms-cilk ms-omp

ms-cilk:ms-cilk.cpp ms-omp
	$(CC2) $(CFLAGS2) -O3 $< -o $@
# $< signifies the first dependency while $^ signifies all dependencies
ms-omp:ms-omp.cpp
	$(CC) $(CFLAGS) -O3 $^ -o $@

# Target to delete the files
clean:
	rm -f *.txt
	rm -f ms-omp
	rm -f ms-cilk
	rm -f ms-tbb

