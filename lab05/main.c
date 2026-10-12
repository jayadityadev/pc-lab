// Write an MPI program to demonstrate MPI_Send and MPI_Recv.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int send_data, recv_data;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Run the program using at least 2 processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        send_data = 42;
        printf("Process %d sending data: %d\n", rank, send_data);
        MPI_Send(&send_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received data: %d\n", rank, recv_data);
    }

    MPI_Finalize();
    return 0;
}