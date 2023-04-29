#!/bin/bash

file=result-qs-omp.txt
rm -f $file
touch $file
for iterations in {1..10..1}
do
	for j in 1000000 10000000 100000000 1000000000
	do
		for i in $(seq 1 $(nproc))
		do
			export OMP_NUM_THREADS=$i && perf stat -e instructions,inst_retired.any,cycles,cpu_clk_unhalted.thread,cycle_activity.stalls_total,L1-dcache-load-misses,L1-dcache-loads,L1-dcache-store-misses,L1-dcache-stores,L1-icache-load-misses,L1-icache-loads,l2_rqsts.miss,l2_rqsts.references,LLC-load-misses,LLC-loads,LLC-store-misses,LLC-stores,branches,branch-misses,icache_64b.iftag_miss,itlb_misses.walk_completed,dTLB-load-misses,dTLB-loads,dTLB-store-misses,dTLB-store,iTLB-load-misses -o $file --append ./qs-omp $j >> $file 
			echo "====================================================================" >> $file
		done
	done
done
