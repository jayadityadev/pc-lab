// Write an OpenMP program that divides the iterations into chunks containing 2 iterations, respectively (OMP_SCHEDULE = static, 2). Its input should be the number of iterations, and its output should be which iterations of a parallelized for loop are executed by which thread.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_iterations>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    #pragma omp parallel
    {
        #pragma omp for schedule(static, 2)   
        for (int i = 0; i < n; i++) {
            int thread_id = omp_get_thread_num();
            printf("Thread %d executes iteration %d ", thread_id, i);
        }
    }

    return 0;
}