    /*allgather*/
    #include <mpi.h>
    #include <stdio.h>
    void main (int argc, char *argv[]){
        int i, myrank ;
        int isend, irecv[3];
        
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        
        isend = myrank + 1;
        
        MPI_Allgather(&isend, 1, MPI_INTEGER, irecv, 1, MPI_INTEGER, MPI_COMM_WORLD);
        
        printf( "%d irecv = " );
        for(i=0; i<3; i++) 
            printf( " %d" , irecv[i]);
        printf( "\n" );

        MPI_Finalize();
    }