#include "mpi.h"
#include "stdio.h"
void main (int argc, char *argv[]){
	int rank, size, total, sum=0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank==size-1){
		for (int k=(10000/size)*rank; k<=10000; k++)
			sum=sum+k;
	}
	else{
	for (int j=(10000/size)*rank; j<(10000/size)*(rank+1); j++)
		sum=sum+j;
	}
	MPI_Reduce(&sum, &total, 1, MPI_INTEGER, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank==0)
		printf("sum=%d\n", total);
	MPI_Finalize();
}
