  #include <mpi.h>

  #include <stdio.h>

  void main (int argc, char *argv[]){

    int nprocs, myrank ;

    MPI_Status status;

    double a[100], b[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank ==0) {
      MPI_Send(a, 100, MPI_DOUBLE, 1, 17, MPI_COMM_WORLD);
      // send first
      MPI_Recv(b, 100, MPI_DOUBLE, 1, 19, MPI_COMM_WORLD, &status);
    }


    else if (myrank==1) {
     MPI_Send(a, 100, MPI_DOUBLE, 0, 19, MPI_COMM_WORLD);
     // send first
     MPI_Recv(b, 100, MPI_DOUBLE, 0, 17, MPI_COMM_WORLD, &status);
    }

    MPI_Finalize();
  }