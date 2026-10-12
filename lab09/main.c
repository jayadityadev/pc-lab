#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int rank, size;
    int local_value;

    int sum, prod, max, min;
    int all_sum, all_prod, all_max, all_min;

    MPI_Init(&argc, &argv);

    // Get the rank and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process contributes its rank + 1
    local_value = rank + 1;

    // MPI_Reduce: Results are available only at the root process
    MPI_Reduce(&local_value, &sum, 1, MPI_INT,
               MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_value, &prod, 1, MPI_INT,
               MPI_PROD, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_value, &max, 1, MPI_INT,
               MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_value, &min, 1, MPI_INT,
               MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Results using MPI_Reduce (Root Process Only)\n");
        printf("Sum     = %d\n", sum);
        printf("Product = %d\n", prod);
        printf("Maximum = %d\n", max);
        printf("Minimum = %d\n", min);
    }

    // MPI_Allreduce: Results are available at every process
    MPI_Allreduce(&local_value, &all_sum, 1, MPI_INT,
                  MPI_SUM, MPI_COMM_WORLD);

    MPI_Allreduce(&local_value, &all_prod, 1, MPI_INT,
                  MPI_PROD, MPI_COMM_WORLD);

    MPI_Allreduce(&local_value, &all_max, 1, MPI_INT,
                  MPI_MAX, MPI_COMM_WORLD);

    MPI_Allreduce(&local_value, &all_min, 1, MPI_INT,
                  MPI_MIN, MPI_COMM_WORLD);

    printf("Process %d - MPI_Allreduce: "
           "Sum = %d, Product = %d, Maximum = %d, Minimum = %d\n",
           rank, all_sum, all_prod, all_max, all_min);

    MPI_Finalize();

    return 0;
}