#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cilk/cilk.h>

void merge(int *arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
 
    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));
 
    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
 
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}
 
void merge_sort(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
           cilk_spawn merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        cilk_sync;

        merge(arr, left, mid, right);
    }
}

int main(int argc, char** argv) {
    int n = 1000000;
    if (argc > 1)
        n = atoi(argv[1]);
    int *arr = (int *) malloc(n * sizeof(int));
    struct timeval start, end;
    for (int i = 0; i < n; i++) {
    arr[i] = rand() % n;
    }

    gettimeofday(&start, NULL);

    merge_sort(arr, 0, n - 1);

    gettimeofday(&end, NULL);

    // Calculate execution time
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Execution time: %.6lf seconds\n", elapsed_time);

    free(arr);

    return 0;
}

