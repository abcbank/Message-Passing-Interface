/*type_struct*/
#include <mpi.h> 
#include <stdio.h>
void main (int argc, char *argv[]){
    int i, myrank ;
    int ibuf1[20], ibuf2[20], iblock[2];
    MPI_Datatype inewtype1, inewtype2;
    MPI_Datatype itype[2];
    MPI_Aint idisp[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if(myrank==0)
        for(i=0; i<20; i++) {
            ibuf1[i]=i+1; ibuf2[i]=i+1;
        }
    else
        for(i=0; i<20; i++){
            ibuf1[i]=0; ibuf2[i]=0;
        }
    
    iblock[0] = 3; iblock[1] = 2;
    idisp[0] = 0; idisp[1] = 5*4;
    itype[0] = MPI_INTEGER; itype[1] = MPI_INTEGER;
    
    MPI_Type_struct(2, iblock, idisp, itype, &inewtype1);
    MPI_Type_commit(&inewtype1);
    MPI_Bcast(ibuf1, 2, inewtype1, 0, MPI_COMM_WORLD);

    printf( "%d : Ex.1 :" , myrank);
    for(i=0; i<20; i++) 
        printf( " %d" , ibuf1[i]);
    printf( "\n" );

    iblock[0] = 1; iblock[1] = 3;
    idisp[0] = 0; idisp[1] = 2*4;
    itype[0] = MPI_DOUBLE;
    itype[1] = MPI_INTEGER;

    MPI_Type_struct(2, iblock, idisp, itype, &inewtype2);
    MPI_Type_commit(&inewtype2);
    MPI_Bcast(ibuf2, 2, inewtype2, 0, MPI_COMM_WORLD);

    printf( "%d : Ex.2 :" , myrank);
    for(i=0; i<20; i++) 
        printf( " %d" , ibuf2[i]);
    printf( "\n" );

    MPI_Finalize(); 
}