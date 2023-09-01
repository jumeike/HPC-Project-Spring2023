#!/bin/bash

file=result-fib.txt
rm -f $file
touch $file
for iteration in $(seq 1 10)
do
	for j in 10 20 30 40 50
	do
		for i in $(seq 1 $(sysctl -n hw.physicalcpu))
		do
			CILK_NWORKERS=$i ./fib-cilk $j >> $file 
			echo "===================================" >> $file
		done
	done
done
