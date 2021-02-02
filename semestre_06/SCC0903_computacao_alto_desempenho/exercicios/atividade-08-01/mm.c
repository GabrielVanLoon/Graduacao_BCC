#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){

    // Inicianlizando MPI
    int rank, num_proccess;
    // MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proccess);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N, *MAT, PN, *PMAT, N_BLOCK, N_BLOCK_RESTO, *GLOBAL_COUNT, *COLUMN_COUNT;
    int *MAT_SIZES, *MAT_DSP;
    int local_sum, global_sum, global_avg;

    // Primeira Etapa -> Calcular a média da matriz
    // Processo Mestre:
    // - Inicializas as variáveis N e MAT e passar estes 
    //   valores para todos os processos (ele incluso). 
    if(rank == 0) {
        scanf(" %d", &N);
    } 

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    N_BLOCK       = (N*N)/num_proccess;
    N_BLOCK_RESTO = (N*N)%num_proccess;

    PN = (rank < N_BLOCK_RESTO) ? N_BLOCK + 1 : N_BLOCK;

    MAT  = (int*) malloc((N*N)*sizeof(int));
    PMAT = (int*) malloc((N_BLOCK+N_BLOCK_RESTO)*sizeof(int));
    MAT_SIZES = (int*) malloc(num_proccess * sizeof(int));
    MAT_DSP   = (int*) malloc(num_proccess * sizeof(int));
    COLUMN_COUNT = (int*) calloc(N, sizeof(int));
    GLOBAL_COUNT = (int*) malloc(N * sizeof(int));
 
    if(rank == 0){
        // Lendo a matriz
        for(int j = 0; j < N; j++)
            for(int i = 0; i < N; i++)
                scanf(" %d", &MAT[i*N+j]);

        // Exibe a matriz lida
        // for(int j = 0; j < N; j++){
        //     for(int i = 0; i < N; i++)
        //         printf(" %d", MAT[i*N+j]);
        //     printf("\n");
        // }

        // Calcular quanto irá para cada processo
        int pos = 0;
        for(int p = 0; p < num_proccess; p++){
            MAT_DSP[p]   = pos;
            MAT_SIZES[p] = (p < N_BLOCK_RESTO) ? N_BLOCK + 1 : N_BLOCK;
            // printf("Processo %d, init: %d, size: %d\n", p, MAT_DSP[p], MAT_SIZES[p]);
            pos         += (p < N_BLOCK_RESTO) ? N_BLOCK + 1 : N_BLOCK;
        }

    }

    MPI_Scatterv(MAT, MAT_SIZES, MAT_DSP, MPI_INT, PMAT, (N_BLOCK+N_BLOCK_RESTO), MPI_INT, 0, MPI_COMM_WORLD);

    // Ajudando a construir a média da matriz
    local_sum = 0;
    #pragma omp parallel for reduction(+:local_sum)
    for(int i = 0; i < PN; i++){
        local_sum += PMAT[i];
    }
    // printf("Total sum do processo %d: %d\n", rank, local_sum);

    // Reduzindo a soma para o processo 0
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0,  MPI_COMM_WORLD);

    // Calculando a média da matriz
    if(rank == 0)
        global_avg = global_sum/(N*N) + ( (global_sum%(N*N)) ? 1 : 0 );
    
    // Distribuindo o global average para todos os processos
    MPI_Bcast(&global_avg, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Calculando indice inicial de referencia
    int indice_inicial = 0;
    if(rank < N_BLOCK_RESTO)
        indice_inicial = rank * (N_BLOCK + 1);
    else
        indice_inicial = N_BLOCK_RESTO*(N_BLOCK+1) + (rank-N_BLOCK_RESTO)*N_BLOCK;

    // Contagem dos valores por linha (coluna transposta)
    #pragma omp parallel for reduction(+:local_sum)
    for(int i = 0; i < PN; i++){
        if(PMAT[i] >= global_avg)
            continue;

        int linha = (indice_inicial + i)/N;
        #pragma omp atomic
        COLUMN_COUNT[linha] += 1;
    }

    // Reduzindo os resultados para o mestre
    MPI_Reduce(COLUMN_COUNT, GLOBAL_COUNT, N, MPI_INT, MPI_SUM, 0,  MPI_COMM_WORLD);

    if(rank == 0 ){
        for(int i = 0; i < N; i++)
            printf("%d ", GLOBAL_COUNT[i]);
        printf("\n");
    }

    // Testando reduce de vetores -> Descomentar para visualizar
        // COLUMN_COUNT[0] = rank;
        // COLUMN_COUNT[1] = 1;
        // MPI_Reduce(COLUMN_COUNT, GLOBAL_COUNT, N, MPI_INT, MPI_SUM, 0,  MPI_COMM_WORLD);
        // if(rank == 0){
        //     for(int i = 0; i < 3; i++)
        //         printf("%d ", GLOBAL_COUNT[i]);
        //     printf("\n");
        // }
    // Fim dos testes

    // Desalocando as memórias
    free(MAT);
    free(PMAT);
    free(MAT_SIZES);
    free(MAT_DSP);
    free(COLUMN_COUNT);
    free(GLOBAL_COUNT);

    MPI_Finalize();
    return 0;
}