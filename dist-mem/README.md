how do you use Intel MPI benchmarks (eg. pingpong) and OpenMPI or MPICH2

Using IMB with OpenMPI:

- Download the IMB source code from the Intel website.

- Compile the IMB program using the OpenMPI compiler and libraries. For example:

```
mpicc -o imb_pingpong -O -I<path-to-openmpi-include> <path-to-imb-src>/PingPong/imb_pingpong.c -lm -L<path-to-openmpi-lib> -lmpi
```

- Start the MPI job using the "mpirun" or "mpiexec" command. Use the "-np" option to specify the number of processes to use, and the "-host" option to specify the names of the nodes in the cluster. For example, to run pingpong with 2 processes on 2 nodes:

```
mpirun -np 2 -host node1,node2 ./imb_pingpong
```

Using IMB with MPICH2:

- Download the IMB source code from the Intel website.

- Compile the IMB program using the MPICH2 compiler and libraries. For example:

```
mpicc -o imb_pingpong -O -I<path-to-mpich2-include> <path-to-imb-src>/PingPong/imb_pingpong.c -lm -L<path-to-mpich2-lib> -lmpich
```

- Start the MPI job using the "mpiexec" command. Use the "-n" option to specify the number of processes to use, and the "-hosts" option to specify the names of the nodes in the cluster. For example, to run pingpong with 2 processes on 2 nodes:

