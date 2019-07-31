#include"mpi.h"
#include <stdio.h>

void main(int argc, char *argv[]) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_COmm_rank(MPI_COMM_WORLD, &size);
	int sum = 0;
	int irecv[100];
	for (i=100/size*rank; i<100/size*(rank+1);i++ ){
		sum=sum+i;
	}
	
	for (i=0,i<rank+1; i++) data[i]=i; {
		int MPI_Send(data, rank, MPI_INT, 0, , MPI_COMM_WORLD);

	printf("irecv[%d] : %d", rank, irecv[rank]);

	MPI_Finalize();
}
