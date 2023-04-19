/*
 * qsort.c
 *
 * Copyright (c) 2007, 2008 Cilk Arts, Inc.  All rights reserved.
 *
 * An implementation of quicksort using Cilk parallelization.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// Partition array using last element of array as pivot
// (move elements less than last to lower partition
// and elements not less than last to upper partition
// return middle = the first element not less than last
int* partition(int* begin, int* end, int pivot) {
  while (begin < end) {
    if (*begin < pivot) {
      begin++;
    } else {
      end--;
      swap(begin, end);
    }
  }
  return end;
}


// Sort the range between pointers begin and end.
// end is one past the final element in the range.
// Use the Quick Sort algorithm, using recursive divide and conquer.
void sample_qsort(int* begin, int* end) {
  if (begin < end) {
    // get last element
    int last = *(end - 1);

    // we give partition a pointer to the first element and one past the last element
    // of the range we want to partition
    // move all values which are >= last to the end
    // move all value which are < last to the beginning
    // return a pointer to the first element >= last
    int * middle = partition(begin, end - 1, last);

    // move pivot to middle
    swap((end - 1), middle);

    // sort in parallel
    #pragma omp parallel sections 
    {
        #pragma omp section
        sample_qsort(middle+1, end); // sort upper partition w/o pivot
        #pragma omp section
        sample_qsort(begin, middle); // sort lower partition
    }
  }
}

void print_array(const int *a, size_t n) {
  assert(a > 0);
  printf("a: (%d", a[0]);
  int i;
  for (i = 1; i < n; ++i) {
    printf(", %d", a[i]);
  }
  printf(")\n");
}

// A simple test harness.  Program takes 2 optional arguments:
//   First argument specifies the length of the array to sort.
//   Defaults to 10 thousand.
//   Second argument specifies the number of trials to run.
//   Defaults to 1.
int main(int argc, char **argv) {
  int *a = NULL, failCount = 0;
  int failFlag;

  // get number of integers to sort, default 1 million
  int n = 1000*1000;
  if (argc > 1) {
    n = atoi(argv[1]);
  }
  printf("Sorting %d integers\n", n);

  // check arguments
  if (n < 1) {
    printf("array length must be positive\n");
    exit(-1);
  }

  // allocate memory for array
  a = (int *) malloc(sizeof(int)*n);
  if (!a) {
    printf("array allocation failed\n");
    exit(-1);
  }

  // initialize to pseudorandom inputs
  unsigned int seed = 13;
  for (int i = 0; i < n; ++i) {
    a[i] = rand_r(&seed);
  }

  struct timeval start, end;
  gettimeofday(&start,NULL);

  sample_qsort(a, a + n);

  gettimeofday(&end, NULL);

  // Confirm that a is sorted and that each element contains the index.
  failFlag = 0;
  for (int i = 1; i < n; ++i) {
    if (a[i] < a[i-1]) {
#ifdef DEBUG
      printf("Sort failed at location i = %d: a[i-1] = %d, a[i] = %d\n", i, a[i-1], a[i]);
#endif
      failFlag = 1;
    }
  }
  if (failFlag == 1) {
    ++failCount;
  }

  if (failCount == 0) {
    printf("All sorts succeeded\n");
  } else {
    printf("%d sorts failed\n", failCount);
  }
  int num_threads = atoi(getenv("OMP_NUM_THREADS"));

  double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
  elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
  elapsedTime /= 1000.0;
  printf("Number of threads: %d\n", num_threads);
  printf("Elapsed time: %f seconds\n", elapsedTime);

  // free integer array
  free(a);
  return failCount;
}
