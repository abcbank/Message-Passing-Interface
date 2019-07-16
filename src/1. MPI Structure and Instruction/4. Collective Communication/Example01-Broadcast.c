/*broadcast*/

#include <mpi.h>
#include <stdio.h>

void main (int argc, char *argv[]){
    int i, myrank;
    int imsg[4];
    int jmsg[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank==0) for(i=0; i<4; i++) 
        imsg[i] = i+1;
    else for (i=0; i<4; i++) 
        jmsg[i] = imsg[i] = 0;
    
    #ifdef SAME_BUF
    printf("MPI with same buffer\n");
    printf( "%d: BEFORE:" , myrank);
    for(i=0; i<4; i++) 
        printf( " %d" , imsg[i]);
    printf( "\n" );

    MPI_Bcast(imsg, 4, MPI_INTEGER, 0, MPI_COMM_WORLD);

    printf( "%d: AFTER:" , myrank);

    for(i=0; i<4; i++) 
        printf( " %d" , imsg[i]); 
    printf( "\n" );
    #endif

    #ifndef SAME_BUF
    if(myrank == 0)
        MPI_Bcast(imsg, 4, MPI_INTEGER, 0, MPI_COMM_WORLD);
    else
        MPI_Bcast(jmsg, 4, MPI_INTEGER, 0, MPI_COMM_WORLD);

    #endif

    MPI_Finalize();
}