#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 4

double t1 , t2; 
int main(int argc, char** argv) {
    int range, size , i, j, k;
    int A[N][N], B[N][N], C[N][N], row[N], col[N];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &range);
    
    
    if (range == 0) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                A[i][j] = 4;
                B[i][j] = 4;
            }
        }
     t1 = MPI_Wtime();
    }

    MPI_Scatter(A, N*N/size, MPI_INT, row, N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < N/size; i++) {
        for (j = 0; j < N; j++) {
            col[j] = B[j][i];
        }
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += row[k] * col[k];
            }
        }
    }
    MPI_Gather(C, N*N/size, MPI_INT, C, N*N/size, MPI_INT, 0, MPI_COMM_WORLD);
   
    
    if (range == 0) {
        printf("Je suis le processus 0 et voila Le produit des deux matrice : \n");
   
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
        t2 = MPI_Wtime();
         
        printf("le temps d'éxecution : %lf \n",t2-t1);
    }


    MPI_Finalize();
    return 0;
}