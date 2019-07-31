#include "mpi.h"
#include "stdio.h"

void main(int argc, char *argv[]){
	int rank, size, a;
	int sum=0, result=0;
	int irecv[100];
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	a=100/size;

	for(int i=a*rank; i<a*(rank+1);i++){
		sum+=i;	}
	printf("irecv[%d]:%d\n",rank, sum);

	if(rank!=0){
	MPI_Send(&sum, 1, MPI_INTEGER, 0, rank, MPI_COMM_WORLD);
	}

	else{
		MPI_Send(&sum, 1, MPI_INTEGER, 0, rank, MPI_COMM_WORLD);

		for(int j=0; j<size; j++){
			MPI_Recv(&irecv[j], 1, MPI_INTEGER, j, j, MPI_COMM_WORLD, &status);
		}
		for(int k=0; k<size; k++){
			result+=irecv[k];
		}
		printf("result:%d\n",result);
	}
MPI_Finalize();
}
