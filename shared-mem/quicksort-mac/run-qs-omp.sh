#!/bin/bash

file=result-qs-omp.txt
rm -f $file
touch $file
for iterations in $(seq 1 10)
do
	for j in 1000000 10000000 100000000 1000000000
	do
		for i in $(seq 1 $(sysctl -n hw.physicalcpu))
		do
			OMP_NUM_THREADS=$i ./qs-omp $j >> $file 
			echo "==================================" >> $file
		done
	done
done
