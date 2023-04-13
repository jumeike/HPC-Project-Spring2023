We profile some HPC applications on two broad categories.

Shared Memory Parallelism:
- Here we perform a comparative study of the performance of various micro-architectures on these HPC application and report our findings.
- Our target application are Cilk-based implementation of Monte Carlo algorithm, Fourier Transform, Graph, and image processing.
- We scale the number of cores and report micro-architectural parameters such as L1 miss rate, L2 miss rate, CPU Utilization, Branch prediction miss rate.
- Extensively profile these application of Intel Chip, ARM Chip, and M1 Silicon Chips.

Distributed Memory Parallelism:
- We explore the performance of HPC applications on a distributed cluster. For this analysis, we use ITTC Research Cluster with over 24,000 cores.
- Our target benchmark are NAS Parallel Benchmarks (Lower-Upper Gauss-Seidel Solver, Multi-Grid Solver, Conjugate Gradient, Integer Solver, Block Tri-Diagonal Solver), and Intel MPI Benchmark for measuring the performance of Message Passing Interface.
- Three main MPI libraries are evaluated OpenMPI, MPICH2, and Cilk.
- We scale the number of cores and report micro-architectural parameters such as Execution time, latency, bandwidth, MOPs, & Speedup.

