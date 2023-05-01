#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
    int range, size;
    int next , prev ; 
    MPI_Status status; 
    int value,tmp; 
int main(int argc, char** argv) {

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&range);

    next = (range+1) % size;
    prev = (size +range-1) % size;


    if(range != 0){
        tmp = range+1000;
        MPI_Recv(&value,1,MPI_INT,prev,99,MPI_COMM_WORLD,&status);
        MPI_Send(&tmp,1,MPI_INT,next,99,MPI_COMM_WORLD);
    }else{
        tmp = range+1000;
        MPI_Send(&tmp,1,MPI_INT,next,99,MPI_COMM_WORLD);
        
        MPI_Recv(&value,1,MPI_INT,prev,99,MPI_COMM_WORLD,&status);

    }
    printf (" Moi, le processus %d ,j’ai reçu %d du processus %d \n", range,value,prev);


    MPI_Finalize();
    return 0;
}