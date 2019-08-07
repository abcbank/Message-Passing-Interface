#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

void main(int argc, char *argv[]) {
   
    int rank, size;
    MPI_Status status;
    
    typedef struct {
        int rank;
        int size;
        char name[10];
    } node;

    node a;
    node b[100];

    int len = 10;
    gethostname(a.name, len);

    int blocklengths[3]={1, 1, 10};
    MPI_Datatype types[3]={MPI_INT,MPI_INT,MPI_CHAR};
    MPI_Aint displacements[3];
    MPI_Datatype restype;
    MPI_Aint intex;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Type_extent(MPI_INT, &intex);
    
    displacements[0] = (MPI_Aint)0; 
    displacements[1] = intex;
    displacements[2] = intex*2;

    a.rank = rank;
    a.size = size;

    MPI_Type_struct(3, blocklengths, displacements, types, &restype);
    MPI_Type_commit(&restype);

    MPI_Gather(&a, 1, restype, b, 1, restype, 0, MPI_COMM_WORLD);

    if (rank == 0) {
	for(int i = 0; i < size; i++)
       	    printf("P:%d my node is %d %d %s\n", b[i].rank, b[i].rank, b[i].size, b[i].name);
    }

    MPI_Finalize();
}
