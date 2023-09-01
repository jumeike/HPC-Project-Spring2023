# Makefile to build binaries and clean directory

CC =g++
CC2 = xcrun /opt/opencilk/bin/clang++
LDFLAGS = -L/opt/homebrew/opt/libomp/lib
CFLAGS = -I/opt/homebrew/opt/libomp/include
CFLAGS2 = -fopencilk 

all: ms-cilk ms-omp

ms-cilk:ms-cilk-mac.cpp ms-omp
	$(CC2) $(CFLAGS2) -O3 $< -o $@
# $< signifies the first dependency while $^ signifies all dependencies
ms-omp:ms-omp-mac.cpp
	$(CC) $(LDFLAGS) $(CFLAGS) -lomp -O3 $^ -o $@

# Target to delete the files
clean:
	rm -f *.txt
	rm -f ms-omp
	rm -f ms-cilk

