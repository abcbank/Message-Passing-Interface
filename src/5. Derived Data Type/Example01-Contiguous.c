/*type_contiguous*/
#include <mpi.h>
#include <stdio.h>
void main (int argc, char *argv[]){
    int i, myrank int, ibuf[20];
    MPI_Datatype inewtype;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    
    if(myrank==0) 
        for(i=0; i<20; i++) 
            ibuf[i]=i+1;
    else 
        for(i=0; i<20; i++) 
            ibuf[i]=0;

    MPI_Type_contiguous(3, MPI_INT, &inewtype);
    // int형을 세개 묶어서 하나의 데이터 타입으로 선언
    MPI_Type_commit(&inewtype);
    // 이후 배울 함수. 새로 선언한 데이터 타입을 등록하는 함수라 보면 됨

    MPI_Bcast(ibuf, 3, inewtype, 0, MPI_COMM_WORLD);

    printf( "%d : ibuf =" , myrank);
    for(i=0; i<20; i++) printf( " %d" , ibuf[i]);
    printf( "\n" );
    MPI_Finalize();
}