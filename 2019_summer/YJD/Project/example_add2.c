#include "mpi.h"
#include <stdio.h>

#define MAX 10000

int main(int argc,char **argv){
	int rank, p, i;
	int dataPerNode, sum, result;
	int irecv[10];

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	dataPerNode = MAX / p;
	sum = 0;

	for(i = dataPerNode * rank; i < dataPerNode * (rank + 1); i++)
		sum += i;

	MPI_Send(&sum, 1, MPI_INTEGER, 0, rank, MPI_COMM_WORLD);
	if(rank == 0){
		for(i = 0; i < p; i++)
			MPI_Recv(&(irecv[i]), 1, MPI_INTEGER, i, i, MPI_COMM_WORLD, &status);
		for(i = 0; i < p; i++){
			result += irecv[i];
			printf("irecv[%d] = %d\n", i, irecv[i]);
		}
		printf("result = %d\n", result);
	}
	MPI_Finalize();

}
