/**
 * Recebe como entrada um valor N, K e depois um vetor de N inteiros.
 * Exibe na tela de forma ordenada todos os indices i do vetor tal que:
 * - vet[i] > vet[k]
 */

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){

    int rank, num_proccess;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proccess);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int master_rank = 0;
    int n, k, *vet, limiar;

    if(num_proccess == 1){
        printf("Invalid num os proccess. Plese select np > 1\n");
        MPI_Finalize();
        return 0;
    }

    // 1ª etapa - Lendo e transmitindo n e k
    if(rank == 0)
        scanf("%d %d", &n, &k);
    MPI_Bcast(&n, 1, MPI_INT, master_rank, MPI_COMM_WORLD);

    // 2ª etapa - lendo os valores do vetor e vet[k] e transmitindo vet[k]
    if(rank == 0){
        vet = (int*) malloc(n * sizeof(int));
        for(int i = 0; i < n; i++)
            scanf("%d", &vet[i]);
        
        limiar = vet[k];
    }
    MPI_Bcast(&limiar, 1, MPI_INT, master_rank, MPI_COMM_WORLD);

    // 3ª etapa - distribuindo o vetor para as outras tarefas e transmitindo os dados
    int num_workers = num_proccess-1;
    int vet_slice   = n/num_workers;
    int overhead    = 0;

    if(rank == 0){
        for(int w = 1; w <= num_workers; w++ ){
            overhead = (w == num_workers) ? n%num_workers : 0;
            MPI_Send(vet + vet_slice * (w-1), vet_slice+overhead, MPI_INT, w, 0, MPI_COMM_WORLD);
        }
    } else {
        vet_slice += (rank == num_workers) ? n%num_workers : 0;
        vet = (int*) malloc(vet_slice * sizeof(int));
        MPI_Recv(vet, vet_slice, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    // 4ª Etapa - os workers vão encontrar os valores maiores que vet[k] e 
    // armazenar seus indexes em um vetor para ser retornado ao processo mestre
    //
    // já a tarefa mestre ia percorrer ordenadamente o n-1 workers e, para cada um deles:
    // -> Verificar quantos valores acima do limiar cada 1 achou
    // -> exibir os indices recebidos do worker atual e exibir na tela
    //
    // Primeiro indice de res indica quantos elementos foram achados pelo worker
    int m = 0, res_size = (n/num_workers + n%num_workers) + 1;
    int *res = (int*) malloc(res_size * sizeof(int));

    if(rank == 0){
        for(int w = 1; w <= num_workers; w++){
            MPI_Recv(res, res_size, MPI_INT, w, 0, MPI_COMM_WORLD, &status);
            
            int w_found = res[0];
            int vet_start_position = vet_slice * (w-1);

            for(int i = 1; i <= w_found; i++){
                // Exibe os valores
                // printf("%d ", vet[vet_start_position + res[i]]);

                // Exibe os indices
                printf("%d ", vet_start_position + res[i]);
            }
        }
        printf("\n");

    } else {
        for(int i = 0; i < vet_slice; i++){
            if(vet[i] > limiar){
                res[m+1] = i;
                m++;
            }
        }
        res[0] = m;
        MPI_Send(res, res_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    free(vet);
    free(res);
    
    MPI_Finalize();

    return 0;
}