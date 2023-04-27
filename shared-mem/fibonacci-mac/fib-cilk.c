#include <stdio.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include <sys/time.h>
// #include "ctimer.h"

long fib(long n) {
  if (n < 2)
    return n;
  long x, y;
  cilk_scope {
    x = cilk_spawn fib(n-1);
    y = fib(n-2);
  }
  return x + y;
}

int main(int argc, char *argv[]) {
  long n = 10;
  if (argc > 1)
    n = atol(argv[1]);
  struct timeval start, end;
  gettimeofday(&start, NULL);
  long result = fib(n);
  gettimeofday(&end, NULL);

  double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
  elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
  elapsedTime /= 1000.0;
  char* env_var = getenv("CILK_NWORKERS");
  printf("Number of threads: %d\n", atoi(env_var));
  printf("Elapsed time: %f seconds\n", elapsedTime);
  printf("fib(%ld) = %ld\n", n, result);

  return 0;
}