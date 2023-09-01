#!/bin/bash

file=result-ms-cilk.txt
rm -f $file
touch $file
for iteration in $(seq 1 10)
do
	for j in 1000000 10000000 100000000 1000000000
	do
		for i in $(seq 1 $(sysctl -n hw.physicalcpu))
		do
			CILK_NWORKERS=$i ./ms-cilk $j >> $file 
			echo "===================================" >> $file
		done
	done
done
