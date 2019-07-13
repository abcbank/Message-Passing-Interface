    #include <mpi.h>
    #include <stdio.h>
    void main (int argc, char *argv[]){
        int i, myrank, ista, iend;
        double a[9], sum, tmp[3];
        
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        
        ista = myrank*3;
        iend = ista + 2;
        
        for(i = 0; i < 3; i++)
            tmp[i] = 0.0;

        for(i = ista; i<iend+1; i++) 
            a[i] = i+1;

        sum = &a[ista];

        MPI_Reduce(sum, tmp, 3, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // sum: sendbuf, tmp: recvbuf
        sum = tmp[0] + tmp[1] + tmp[2];
    
        if(myrank == 0) 
            printf("sum = %f \n" , sum);

        MPI_Finalize();
    }