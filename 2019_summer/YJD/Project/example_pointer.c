#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv){
	int rank, size;
	int irecv, isend[10];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	printf("irecv of processer %d: %p \n",rank, isend);

	MPI_Finalize();

	return 0;
}
