#include <stdio.h> 
#include<mpi.h>

void main(int argc, char *argv[]) {
    int rank,i;
    MPI_Status status;
    
    struct {
        int num; float x; double data[4];
    } a;
    
    int blocklengths[3]={1,1,4};
    // 데이터의 개수: int * 1, float * 1, double * 4
    MPI_Datatype types[3]={MPI_INT,MPI_FLOAT,MPI_DOUBLE};
    // 데이터의 종류
    MPI_Aint displacements[3];
    // offset
    MPI_Datatype restype;
    // new datatype
    MPI_Aint intex,floatex;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Type_extent(MPI_INT,&intex);
    // get size of MPI_INT
    MPI_Type_extent(MPI_FLOAT,&floatex);
    // get sizeof MPI_FLOAT
    
    displacements[0]= (MPI_Aint)0; displacements[1]=intex;
    displacements[2]=intex+floatex;
    // displacement(offset): int -> 0, float -> intex, double -> inted + floatex
    MPI_Type_struct(3,blocklengths,displacements,types,&restype);
    // create datatype
    MPI_Type_commit(&restype);
    // commit datatype
    if (rank==3){
        a.num=6; a.x=3.14; for(i=0;i<4;++i) a.data[i]=(double) i;
        MPI_Send(&a,1,restype,1,52,MPI_COMM_WORLD);
        // 3번과 1번이 1대1 통신 수행
    }
    else if(rank==1) {
        MPI_Recv(&a,1,restype,3,52,MPI_COMM_WORLD,&status);
        printf("P:%d my a is %d %f %lf %lf %lf %lf\n",
        rank,a.num,a.x,a.data[0],a.data[1],a.data[2],a.data[3]);
    }
    MPI_Finalize();
}
