/**
 * Implementa um token ring que passa um token para todos os 
 * processos e ao retornar ao inicial exibe o valor final do token.
 */

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){

    int rank, num_proccess, rank_send, rank_from, token;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proccess);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    rank_send = (rank+1)%num_proccess;
    rank_from = (rank + num_proccess - 1)%num_proccess;
    token = 0;

    if(num_proccess == 1){
        // garante que caso só haja 1 processo não vai dar deadlock

    } else if(rank == 0){ 
        MPI_Send(&token, 1, MPI_INT, rank_send, 0, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_INT, rank_from, 0, MPI_COMM_WORLD, &status);
    } else {
        MPI_Recv(&token, 1, MPI_INT, rank_from, 0, MPI_COMM_WORLD, &status);
        token += 1;
        MPI_Send(&token, 1, MPI_INT, rank_send, 0, MPI_COMM_WORLD);
    }

    if(rank == 0) 
        printf("%d\n", token);
        
    MPI_Finalize();

    return 0;
}