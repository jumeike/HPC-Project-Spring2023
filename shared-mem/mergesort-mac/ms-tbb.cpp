#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>
#include "tbb/parallel_sort.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/parallel_invoke.h"

using namespace std;
using namespace tbb;

// Merge two sorted arrays into a single sorted array
void merge(int* arr, int* left, int leftSize, int* right, int rightSize) {
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] < right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// Merge sort algorithm
void mergeSort(int* arr, int size) {
    if (size <= 1) {
        return;
    }
    int mid = size / 2;
    int* left = new int[mid];
    int* right = new int[size - mid];
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }
    parallel_invoke(
        [&] {mergeSort(left, mid);},
        [&] {mergeSort(right, size - mid);}
    );
    merge(arr, left, mid, right, size - mid);
    delete[] left;
    delete[] right;
}

int main(int argc, char * argv[]) {
    int n = 1000000;
    if (argc > 1)
        n = atoi(argv[1]);
    int* arr = new int[n];
    //srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    struct timeval start, end;
    gettimeofday(&start, NULL);
    mergeSort(arr, n);
    gettimeofday(&end, NULL);
    double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
    elapsedTime /= 1000.0;
    cout << "Elapsed time: " << elapsedTime << " seconds" << endl;
    delete[] arr;
    return 0;
}
