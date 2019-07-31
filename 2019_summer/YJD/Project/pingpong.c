#include "mpi.h"
#include <stdio.h>

#define STARTNUM 0
#define ODDTAG 1004
#define EVENTAG 2004

int oddTask(int nodeNum, int *num);
int evenTask(int nodeNum, int *num);

int main(int argc, char **argv){
	int rank, size, num = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	while(num < 10){
		if(num % 2 == 0)
			oddTask(rank, &num);
		else
			evenTask(rank, &num);
	}
	MPI_Finalize();
	return 0;
}

int oddTask(int nodeNum, int *num){
	int t = nodeNum % 2;
	MPI_Status status;

	switch(t){
	case 0:
		printf("%d process: %d\n", t, (*num)++);
		MPI_Send(num, 1, MPI_INTEGER, 1, ODDTAG, MPI_COMM_WORLD);
	break;

	case 1:
		MPI_Recv(num, 1, MPI_INTEGER, 0, ODDTAG, MPI_COMM_WORLD, &status);
	break;

	}
}

int evenTask(int nodeNum, int *num){
	int t = nodeNum % 2;
	MPI_Status status;

	switch(t){
	case 0:
		MPI_Recv(num, 1, MPI_INTEGER, 1, EVENTAG, MPI_COMM_WORLD, &status);
	break;

	case 1:
		printf("%d process: %d\n", t, (*num)++);
		MPI_Send(num, 1, MPI_INTEGER, 0, EVENTAG, MPI_COMM_WORLD);
	break;
	}
}
