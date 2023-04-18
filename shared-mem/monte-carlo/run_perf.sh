#!/bin/bash

for i in {1..4}
do
    # Set number of workers
    export CILK_NWORKERS=$i

    # Compile cilk-based code
    gcc -fcilkplus -O3 -o mc-cilk mc-cilk.cpp

    # Run mc-cilk and measure performance using perf
    perf stat -e L1-dcache-load-misses,L1-dcache-loads,L2-cache-load-misses,L2-cache-loads,L3-cache-load-misses,L3-cache-loads,cpu-clock,task-clock,branches,branch-misses ./mc-cilk > perf_output_$i.txt

    # Clean up executable
    rm mc-cilk
done

