// Write an MPI program to demonstrate deadlock using point-to-point communication and avoidance of deadlock by altering the call sequence.

#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank;
    int message = 42;
    char communication_mode[20] = "deadlock";

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc > 1)
        strcpy(communication_mode, argv[1]);

    if (strcmp(communication_mode, "deadlock") == 0) {
        MPI_Send(&message, 1, MPI_INT, 1 - rank, 0, MPI_COMM_WORLD);
        MPI_Recv(&message, 1, MPI_INT, 1 - rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d completed communication in deadlock mode.\n", rank);
    } else if (strcmp(communication_mode, "safe") == 0) {
        if (rank == 0) {
            MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
        printf("Process %d completed communication in safe mode.\n", rank);
    }
    
    MPI_Finalize();
    return 0;
}