// Write an OpenMP program to sort an array of 'n' elements using both sequential and parallel merge sort (using sections). Record the difference in execution time.

#include <stdio.h>
#include <omp.h>

void merge(int array[], int left, int middle, int right) {
    int temp[100];
    int i = left;
    int j = middle + 1;
    int k = left;

    while (i <= middle && j <= right)
        temp[k++] = (array[i] <= array[j]) ? array[i++] : array[j++];

    while (i <= middle)
        temp[k++] = array[i++];

    while (j <= right)
        temp[k++] = array[j++];

    for (i = left; i <= right; i++)
        array[i] = temp[i];
}

void sequentialMergeSort(int array[], int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;
        sequentialMergeSort(array, left, middle);
        sequentialMergeSort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

void parallelMergeSort(int array[], int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(array, left, middle);

            #pragma omp section
            parallelMergeSort(array, middle + 1, right);
        }

        merge(array, left, middle, right);
    }
}

int main() {
    int n, array1[100], array2[100];
    double sequentialTime, parallelTime;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array1[i]);
        array2[i] = array1[i]; // Copy for parallel sort
    }

    // Sequential merge sort
    sequentialTime = omp_get_wtime();
    sequentialMergeSort(array1, 0, n - 1);
    sequentialTime = omp_get_wtime() - sequentialTime;

    printf("Sequential Merge Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", array1[i]);
    printf("\n");

    // Parallel merge sort
    parallelTime = omp_get_wtime();
    parallelMergeSort(array2, 0, n - 1);
    parallelTime = omp_get_wtime() - parallelTime;

    printf("Parallel Merge Sort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", array2[i]);
    printf("\n");

    printf("Sequential time: %f\n", sequentialTime);
    printf("Parallel time: %f\n", parallelTime);

    return 0;
}