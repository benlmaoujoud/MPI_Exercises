#include <stdio.h>
#include <mpi.h>

#define ARRAY_SIZE 10
#define MASTER 0

int main(int argc, char** argv) {
    int rank, size, i;
    int local_sum = 0, global_sum = 0;
    int array[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_array[ARRAY_SIZE / size]; // each process will hold ARRAY_SIZE / size elements

    // Initialize array on the master process
    if (rank == MASTER) {
        for(i = 0; i < ARRAY_SIZE; i++) {
            array[i] = 1;
        }
    }
    // 1 1 1 1 1    1 1 1 1 1 

    // Scatter the array to all processes
    MPI_Scatter(array, ARRAY_SIZE / size, MPI_INT, local_array, ARRAY_SIZE / size, MPI_INT, MASTER, MPI_COMM_WORLD);

    // Each process calculates the local sum
    for(i = 0; i < ARRAY_SIZE / size; i++) {
        local_sum += local_array[i];
    }

    // Gather local sums into the global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);

    if (rank == MASTER) {
        printf("Total sum is %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
