#include "mpi.h"
#include "stdio.h"

void main(int argc, char **argv){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int sum=0;
	int result=0;

	for(int i=(100/size)*rank+1;i<(100/size)*(rank+1)+1;i++){
		sum+=i;
	}

	int irecv[100];
	MPI_Send(&sum, 1, MPI_INTEGER, 0, rank, MPI_COMM_WORLD);

	MPI_Status status;
	if(rank==0){
		for(int i=0;i<size;i++){
			MPI_Recv(irecv, 1, MPI_INTEGER, rank, rank, MPI_COMM_WORLD, &status);
		}
		for(int i=0;i<size;i++){
			printf("irecv[%d] = %d\n", i, irecv[i]);
			result+=irecv[i];
		}
		printf("Result = %d\n", result);
	}
	MPI_Finalize();
}
