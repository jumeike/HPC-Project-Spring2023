#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

long fib(long n) {
  if (n < 2)
    return n;
  long x, y;
  #pragma omp parallel sections
  {
    #pragma omp section
    x = fib(n-1);
    #pragma omp section
    y = fib(n-2);
  }
  return x + y;
}

int main(int argc, char *argv[]) {
  long n = 10;
  if (argc > 1)
    n = atol(argv[1]);
  int num_threads = atoi(getenv("OMP_NUM_THREADS"));
  omp_set_num_threads(num_threads);
  struct timeval start, end;
  gettimeofday(&start, NULL);
  long result = fib(n);
  gettimeofday(&end, NULL);

  double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
  elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
  elapsedTime /= 1000.0;
  printf("Number of threads: %d\n", num_threads);
  printf("Elapsed time: %f seconds\n", elapsedTime);
  printf("fib(%ld) = %ld\n", n, result);

  return 0;
}
