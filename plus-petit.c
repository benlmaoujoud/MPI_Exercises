#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 3

int main(int argc, char** argv) {
    int size, rank, i,j;
    int local_min, global_min;
    int *matrix;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Allocate memory for the matrix on process 0
    if (rank == 0) {
        matrix = (int*) malloc(N*N * sizeof(int));
        printf("Init the matrix : \n");
        for (i = 0; i < N; i++) {
           for (j = 0; j < N; j++) {
                matrix[i*N +j] = rand() %1000;
                printf("%d \t",matrix[i*N +j]);
            }
            printf("\n");
        }
    }

    // Scatter the matrix to all processes
    int *local_matrix = (int*) malloc(N * sizeof(int));
    MPI_Scatter(
        matrix,
        N,
        MPI_INT,
        local_matrix,
        N,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    // Find the local minimum
    local_min = local_matrix[0];
    for (i = 0; i < N; i++) {
        if (local_matrix[i] < local_min) {
            local_min = local_matrix[i];
        }
    }

    // Reduce the local minimums to find the global minimum
    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("The minimum element of the matrix is %d\n", global_min);
        free(matrix);
    }
    free(local_matrix);

    MPI_Finalize();
    return 0;
}
