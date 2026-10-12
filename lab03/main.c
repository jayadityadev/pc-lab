// Write an OpenMP program to calculate n Fibonacci numbers using tasks.

#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n < 2)
        return n;

    int firstValue, secondValue;

    #pragma omp task shared(firstValue) if (n > 10)
    firstValue = fibonacci(n - 1);

    #pragma omp task shared(secondValue) if (n > 10)
    secondValue = fibonacci(n - 2);

    #pragma omp taskwait
    return firstValue + secondValue;
}

int main() {
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    #pragma omp parallel
    {
        #pragma omp single
        for (int i = 0; i < n; i++) {
            int result = fibonacci(i);
            printf("fib(%d) = %d\n", i, result);
        }
    }

    return 0;
}