# Makefile to build binaries and clean directory

CC =gcc
CC2 = xcrun /opt/opencilk/bin/clang
LDFLAGS = -L/opt/homebrew/opt/libomp/lib
CFLAGS = -I/opt/homebrew/opt/libomp/include
CFLAGS2 = -fopencilk 

all: qs-cilk qs-omp

qs-cilk:qs-cilk-mac.c qs-omp
	$(CC2) $(CFLAGS2) -O3 $< -o $@
# $< signifies the first dependency while $^ signifies all dependencies
qs-omp:qs-omp-mac.c
	$(CC) $(LDFLAGS) $(CFLAGS) -lomp -O3 $^ -o $@

# Target to delete the files
clean:
	rm -f *.txt
	rm -f qs-omp
	rm -f qs-cilk

