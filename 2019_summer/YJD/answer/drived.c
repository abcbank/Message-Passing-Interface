#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mpi.h"

typedef struct{
	int rank;
	int size;
	char name[10];
}node;

void main(int argv, char **argc){
	int rank, size, i, iblock[3];
	node nameTag, isend, irecv[20];
	MPI_Datatype inewtype;
	MPI_Datatype itype[3];
	MPI_Aint idisp[3];

	MPI_Init(&argv, &argc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	nameTag.size = size;
	nameTag.rank = rank;
	gethostname(nameTag.name, sizeof(nameTag.name));

	iblock[0] = 1; iblock[1] = 1; iblock[2] = 10;
	itype[0] = MPI_INTEGER; itype[1] = MPI_INTEGER; itype[2] = MPI_CHARACTER;
	idisp[0] = 0; idisp[1] = 4; idisp[2] = 8;

	MPI_Type_struct(3, iblock, idisp, itype, &inewtype);
	MPI_Type_commit(&inewtype);
	MPI_Gather(&nameTag, 1, inewtype, irecv, 1, inewtype, 0, MPI_COMM_WORLD);

	if(rank == 0){
		printf("Print nameTag\n");
			printf("-------------------------------------\n");
		for(i = 0; i < size; i++){
			printf("Proc%d:", i);
			printf("rank %d of %d proc|name: %s\n",
			 irecv[i].rank, irecv[i].size, irecv[i].name);
		}
	}

	MPI_Finalize();
}
