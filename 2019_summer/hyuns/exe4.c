#include <mpi.h>
#include <stdio.h>
void main(int argc, char *argv[])
{
	int i, rank, nprocs;
	int isend, irecv[10], sum=0, finsum=0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for(int i=10000/nprocs*rank+1; i<=10000/nprocs*(rank+1); i++)
	{
		sum+=i;
	}
		isend=sum;

	MPI_Gather(&isend, 1, MPI_INTEGER, irecv, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);

	if(rank == 0)
	{
		for(int j=0; j<nprocs; j++)
		{
			printf("irecv[%d]=%d\n", j, irecv[j]);
			finsum+=irecv[j];
		}
		printf("final_sum=%d\n", finsum);
	}

	MPI_Finalize();
}
