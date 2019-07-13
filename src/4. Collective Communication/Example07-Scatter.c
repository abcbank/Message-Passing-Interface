#include <mpi.h>
#include <stdio.h>
void main (int argc, char *argv[]){
    int i, myrank ;
    int isend[3], irecv; 
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    for(i=0; i<nprocs; i++) 
        isend[i]=i+1;
    
    MPI_Scatter(isend, 1, MPI_INTEGER, &irecv, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);
    
    printf( " %d: irecv = %d\n" , myrank, irecv);
    
    MPI_Finalize();
}