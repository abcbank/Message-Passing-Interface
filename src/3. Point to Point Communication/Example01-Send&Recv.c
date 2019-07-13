#include <stdio.h>
#include <mpi.h>

void main(int argc, char *argv[]) {
  int rank, i, count;

  float data[100],value[200];

  MPI_Status status;

  MPI_Init(&argc,&argv);
  // initialize MPI

  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  // seperate rank

  if(rank==1) {

  for(i=0;i<100;++i) data[i]=i;
    MPI_Send(data,100,MPI_FLOAT,0,55,MPI_Comm_world);
    // buffer -> data, count -> 100, datatype -> MPI_FLOAT, dst -> rank 0, tag -> 55, communicator -> MPI_Comm_world
    // if rank is 1, send data to rank 0
  }

  else {
    MPI_Recv(value,200,MPI_FLOAT,MPI_ANY_SOURCE,55, MPI_COMM_WORLD,&status);
    // buffer -> value, count -> 200, datatype -> MPI_FLOAT, source -> all, tag -> all, commuicator -> all
    // if rank is not 1, receive data from all the other ranks

    printf("P:%d Got data from processor %d \n",rank, status.MPI_SOURCE);
    // rank: current rank, status.MPI_SOURCE: 1

    MPI_Get_count(&status,MPI_FLOAT,&count);
    // status -> status, datatype -> MPI_FLOAT, count -> count
    printf("P:%d Got %d elements \n",rank,count);
    printf("P:%d value[5]=%f \n",rank,value[5]);
  }
  MPI_Finalize();
}