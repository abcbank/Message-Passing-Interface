    /*gatherv*/

    #include <mpi.h>
    #include <stdio.h>

    void main (int argc, char *argv[]){
        int i, myrank ;
        int isend[3], irecv[6];
        int iscnt, ircnt[3]={1,2,3}, idisp[3]={0,1,3};

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

        for(i=0; i<myrank+1; i++) 
            isend[i] = myrank + 1;
        
        iscnt = myrank +1;
        MPI_Gatherv(isend, iscnt, MPI_INTEGER, irecv, ircnt, idisp, MPI_INTEGER, 0, MPI_COMM_WORLD);
        
        if(myrank == 0) {
            printf( " irecv = " );
            for(i=0; i<6; i++) 
                printf( " %d" , irecv[i]);
            printf( "\n" );
        }
        
        MPI_Finalize();
    }