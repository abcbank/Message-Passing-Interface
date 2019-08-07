#include "stdio.h"
#include "mpi.h"
#include "unistd.h"

void main(int argc, char *argv[]){
	typedef struct{
		int rank, size;
		char name[10];
	}node;

	int rank, size;

	node A;
	node irecv[10];
	int blocklengths[3]={1,1,10};
	MPI_Datatype types[3]={MPI_INTEGER, MPI_INTEGER, MPI_CHARACTER};
	MPI_Aint displacements[3];
	MPI_Datatype restype;
	MPI_Aint intex;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	A.rank = rank;
	A.size = size;

	MPI_Type_extent(MPI_INTEGER, &intex);
	gethostname(A.name, 10);

	displacements[0]=0; displacements[1]=intex; displacements[2]=2*intex;

	MPI_Type_struct(3, blocklengths, displacements, types, &restype);
	MPI_Type_commit(&restype);

	MPI_Gather(&A, 1, restype, irecv, 1, restype, 0, MPI_COMM_WORLD);

	if(irecv->rank==0)
		for(int i=0; i<size; i++){
			printf("Proc%d:rank %d of %d proc|name:%s\n",irecv[i].rank, irecv[i].rank, irecv[i].size, irecv[i].name);
		}
	MPI_Finalize();
}
