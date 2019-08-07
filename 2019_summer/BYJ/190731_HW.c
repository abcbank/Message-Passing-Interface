#include <mpi.h>
#include <stdio.h>

void main(int argc, char *argv[]) {
        int rank, size;
	int mid_sum, sum = 0;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	for (int i = (100/size)*rank; i<(100/size)*(rank+1); i++) {
		mid_sum += i;
	}
	printf("mid_sum = %d of %d:rank\n", mid_sum, rank);

	MPI_Send(&mid_sum, size, MPI_INTEGER, 0, rank, MPI_COMM_WORLD);
	MPI_Recv(&sum, size, MPI_INTEGER, 0, rank, MPI_COMM_WORLD, &status);

	for (int i = 0; i < size; i++) {
		sum += mid_sum;
	}
        printf("all_sum = %d\n", sum);

        MPI_Finalize();
}
