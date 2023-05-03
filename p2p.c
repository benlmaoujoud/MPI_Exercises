#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>
#include<string.h>


int rank , size , status;
char *message ;
int main(int argc , char** argv){

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 1){
        message = malloc(1024*sizeof(char));
        MPI_Send(message,1024,MPI_CHAR,3,99,MPI_COMM_WORLD);
    }

    if(rank ==3){
        char* hello =malloc(1024*sizeof(char));
        MPI_Recv(hello,1024,MPI_CHAR,1,99,MPI_COMM_WORLD,&status);
    }






    MPI_Finalize();
    return 0 ; 
}