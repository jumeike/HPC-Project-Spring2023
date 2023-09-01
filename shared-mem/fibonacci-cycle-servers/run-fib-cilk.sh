#!/bin/bash

file=result-fib.txt
rm -f $file
touch $file
for iteration in {1..10..1}
do
	for j in 10 20 30 40 50 
	do
		for i in $(seq 1 $(nproc))
		do
			CILK_NWORKERS=$i ./fib-cilk $j >> $file 
			echo "==========================" >> $file
		done
	done
done
