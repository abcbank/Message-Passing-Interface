#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	int nprocs, myrank, i;
	MPI_Status status;

	int sum = 0, result = 0;
	int irecv[100];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	for(i = (100/nprocs) * myrank; i < (100/nprocs) * myrank + 100/nprocs; i++){
		sum += i;
	}

	irecv[myrank] = sum;

	printf("irecv[%d] = %d\n", myrank, irecv[myrank]);


	if(myrank == 0){

		for(i = 1; i < nprocs; i++){
			MPI_Recv(&irecv[i], 1, MPI_INTEGER, i, i, MPI_COMM_WORLD, &status);
		}

		for(i = 0; i <nprocs; i++){
			result += irecv[i];
		}

		printf("%d\n", result);
	}

	else{
		MPI_Send(&sum, 1, MPI_INTEGER, 0, myrank, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
