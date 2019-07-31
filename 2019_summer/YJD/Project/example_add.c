#include "mpi.h"
#include <stdio.h>

#define GATHER

int main(int argc, char **argv){
	int rank, p;
	int i;
	int isend = 0, irecv[10] = {0};
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	#ifdef REDUCE

	for(i = 10000*rank; i < 10000*(rank + 1); i++)
		isend += i;

	MPI_Reduce(&isend, &irecv, 1, MPI_INTEGER, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0)
		printf("Result: %d\n", irecv[0]);

	#endif

	#ifdef GATHER

	for(i = 10000 * rank; i < 10000*(rank + 1); i++)
		isend += i;

	MPI_Gather(&isend, 1, MPI_INTEGER, irecv, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);

	if(rank == 0){
		printf("Result: ");
		for(i = 0; i < p; i++)
			printf("%d ", irecv[i]);
		printf("\n");
	}

	#endif

	MPI_Finalize();
	return 0;
}
