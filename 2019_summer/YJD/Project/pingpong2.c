#include "mpi.h"
#include <stdio.h>

#define LIMIT 100
int Task(int nodeRank, int dataSize);

int main(int argv, char **argc){
	int i, rank, size, dataPerNode, result = 0;
	int irecv[100];

	MPI_Status status;

	MPI_Init(&argv, &argc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	dataPerNode = LIMIT / size;

	Task(rank, dataPerNode);

	if(rank == 0){
		for(i = 0; i < size; i++)
			MPI_Recv(irecv+i, 1, MPI_INTEGER, i,i, MPI_COMM_WORLD, &status);
		for(i = 0; i < size; i++){
			printf("irecv[%d]: %d\n ", i, irecv[i]);
			result += irecv[i];
		}

		printf("result: %d\n", result);
	}

	MPI_Finalize();
	return 0;
}

int Task(int nodeRank, int dataSize){
	int i = 0;
	int result = 0;

	for(i = nodeRank * dataSize; i < (nodeRank + 1) *dataSize; i++)
		result += i;

	MPI_Send(&result, 1, MPI_INTEGER, 0, nodeRank, MPI_COMM_WORLD);
	return result;
}
