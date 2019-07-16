    /*reduce*/
    #include <mpi.h>
    #include <stdio.h>
    void main (int argc, char *argv[]){
        int i, myrank, ista, iend;
        double a[9], sum, tmp;
        
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        
        ista = myrank*3;
        iend = ista + 2;
        
        for(i = ista; i<iend+1; i++) 
            a[i] = i+1;

        sum = 0.0;
        
        for(i = ista; i<iend+1; i++) 
            sum = sum + a[i];
        // 부분합 구하기. 해당 연산은 reduce를 통해 하는것이 아님을 유의하자.

        MPI_Reduce(&sum, &tmp, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        // sum: sendbuf, tmp: recvbuf
        sum = tmp;
    
        if(myrank == 0) 
            printf("sum = %f \n" , sum);

        MPI_Finalize();
    }