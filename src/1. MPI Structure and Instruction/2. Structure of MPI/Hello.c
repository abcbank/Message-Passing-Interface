#include "mpi.h"
#include <stdio.h>
int main(int argc, char **argv) {

   int rank, p;

   MPI_Init(&argc, &argv);

   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &p);

   printf("Welcome to MPI world! %d out of %d processors.n", rank, p);

   MPI_Finalize();
   return 0;
}