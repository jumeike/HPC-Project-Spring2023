# Makefile to build binaries and clean directory

CC =clang
CC2 = xcrun /opt/opencilk/bin/clang
LDFLAGS = -L/opt/homebrew/opt/libomp/lib
CFLAGS = -I/opt/homebrew/opt/libomp/include
CFLAGS2 = -fopencilk 

all: fib-cilk fib-omp

fib-cilk:fib-cilk.c fib-omp
	$(CC2) $(CFLAGS2) -O3 $< -o $@
# $< signifies the first dependency while $^ signifies all dependencies
fib-omp:fib-omp.c
	$(CC) $(LDFLAGS) $(CFLAGS) -lomp -O3 $^ -o $@

# Target to delete the files
clean:
	rm -f *.txt
	rm -f fib-omp
	rm -f fib-cilk

