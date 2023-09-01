#!/bin/bash

file=result-omp.txt
rm -f $file
touch $file
for iterations in {1..10..1}
do
	for j in 10 20 30 40
	do
		for i in $(seq 1 $(nproc))
		do
			export OMP_NUM_THREADS=$i && ./fib-omp $j >> $file 
			echo "====================================================================" >> $file
		done
	done
done
