#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
#include <sys/time.h>

using namespace std;

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
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mergeSort(left, mid);
        }
        #pragma omp section
        {
            mergeSort(right, size - mid);
        }
    }
    merge(arr, left, mid, right, size - mid);
    delete[] left;
    delete[] right;
}

int main(int argc, char** argv) {
    int n = 1000000;
    if (argc > 1)
        n = atoi(argv[1]);
    int* arr = new int[n];
    srand(time(NULL));
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
    char* env_var = getenv("OMP_NUM_THREADS");
    cout << "Number of threads: " << atoi(env_var) << endl;
    cout << "Elapsed time: " << elapsedTime << " seconds" << endl;
    delete[] arr;
    return 0;
}
