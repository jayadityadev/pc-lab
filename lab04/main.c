// Write an OpenMP program to find the prime numbers from 1 to n employing parallel for directive. Record both serial and parallel execution time.

#include <stdio.h>
#include <omp.h>

int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int limit = 10000000;
    double startTime, endTime;

    printf("The range of numbers is from 1 to %d\n", limit);

    // Serial execution
    startTime = omp_get_wtime();
    for (int i = 1; i <= limit; i++) {
        isPrime(i);
    }
    endTime = omp_get_wtime();
    printf("Time to compute prime numbers serially: %.6f seconds\n", endTime - startTime);

    // Parallel execution
    startTime = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 1; i <= limit; i++) {
        isPrime(i);
    }
    endTime = omp_get_wtime();
    printf("Time to compute prime numbers in parallel: %.6f seconds\n", endTime - startTime);

    return 0;
}