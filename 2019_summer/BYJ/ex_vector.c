/*type_vector*/
#include <mpi.h>
#include <stdio.h>
void main (int argc, char *argv[]){
    int i, myrank, ibuf[20];
    MPI_Datatype inewtype;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    
    if(myrank==0)
        for(i=0; i<20; i++)
            ibuf[i]=i+1;
    else
        for(i=0; i<20; i++)
            ibuf[i]=0;
    
    MPI_Type_vector(4, 2, 3, MPI_INTEGER, &inewtype);
    MPI_Type_commit(&inewtype);
    
    MPI_Bcast(ibuf, 1, inewtype, 0, MPI_COMM_WORLD);
    
    printf( "%d : ibuf =" , myrank);
    for(i=0; i<20; i++)
        printf( " %d" , ibuf[i]);
    printf( "\n" );
    MPI_Finalize();
}
