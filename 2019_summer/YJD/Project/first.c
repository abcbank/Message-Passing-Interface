#include<stdio.h>
#include"stdlib.h"

#define DATA_SIZE 10000

int main(int *argv, char ** argc){
	int rank, nprocs, nPerRank;
	int sum = 0;
	int isend[5];

	MPI_Init(&argv, &argc);
	MPI_Comm_rank(MPI_COMM_WORLD, rank);
	MPI_Comm_size(MPI_COMM_WORLD, size);

	nPerRank = DATA_SIZE / size;

	switch(rank){
	case 0:
		for(i = 0; i < nPerRank; i++)
			sum += i;
		MPI_RECV
	case 1:
	}

}
