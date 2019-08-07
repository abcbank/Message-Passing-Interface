#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
void main(int argc, char *argv[])
{
   int rank, size;
   MPI_Status status;

   typedef struct
  {
	int rank;
	int size;
	char name[10];
  }node;

    node nametag;
    node irecv[10];

    int datalength[3]={1, 1, 10};
    MPI_Datatype types[3]={MPI_INT, MPI_INT, MPI_CHAR};
    MPI_Aint types_displacement[3];
    MPI_Datatype restype;
    MPI_Aint intex1, intex2;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Type_extent(MPI_INT,&intex1);
    MPI_Type_extent(MPI_INT, &intex2);

    nametag.rank = rank;
    nametag.size = size;
    gethostname(nametag.name, 10);

    types_displacement[0]= (MPI_Aint)0; types_displacement[1]=intex1; types_displacement[2]=intex1+intex2;

    MPI_Type_struct(3, datalength, types_displacement, types, &restype);
    MPI_Type_commit(&restype);

    MPI_Gather(&nametag, 1, restype, irecv, 1, restype, 0, MPI_COMM_WORLD);


    if (rank==0)
	{
		for(int i=0; i<size; i++)
		printf(" rank %d of %d proc | name : %s \n", irecv[i].rank, irecv[i].size, irecv[i].name);
	}


    MPI_Finalize();
}
