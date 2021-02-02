/*
 * Integrantes
 * Gabriel van Loon Bode da Costa Dourado Fuentes Rojas (10391607)
 * João Ricardo Minoru Nagasava (10734449)
 * Mathias Fernandes Duarte Coelho (10734352)
 * Luiz Miguel Di Mano Saraiva (10425420)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]){

    // Inicializando o MPI
    int rank, num_proccess;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proccess);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Abrindo o arquivo de leitura no mestre
    FILE *inputfile;     
    char *inputfilename; 

    if(rank == 0){
        if (argc < 2){
            printf("Mestre: Nr errado de argumentos. Execute passando <arq_entrada> como argumento. \n");
            exit(-1);
        }

        inputfilename = (char*) malloc(256*sizeof(char));
        strcpy(inputfilename,argv[1]);

        if ((inputfile=fopen(inputfilename,"r")) == 0) {
		    printf("Mestre: Erro ao abrir arquivo de entrada %s. Saindo. \n", inputfilename);
		    exit(-1);
        }
    }

    // Declarando as variáveis principais
    int L, C, W;
    char *MS, *MF;

    // Lendo e transmitindo os  valores de L e C
    if(rank == 0)
        fscanf(inputfile, " %d %d", &L, &C);
    
    MPI_Bcast(&L, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&C, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Lendo os valores de MS (apenas o mestre possui MS completa)
    if(rank == 0){
        MS = (char*) calloc(L*(C+1), sizeof(char));
        for(int i = 0; i < L; i++)
            fscanf(inputfile, " %[^\r\n]", &(MS[(C+1)*i]));
    }

    // Lendo e transmitindo W
    if(rank == 0)
        fscanf(inputfile, " %d", &W);

    MPI_Bcast(&W, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Alocando MF em todos os processos
    MF = (char*) calloc(W*(C+1), sizeof(char));

    // Lendo e transmitindo os valores de MF e fechando o arquivo (fim input) 
    if(rank == 0){
        for(int i = 0; i < W; i++)
            fscanf(inputfile, " %[^\r\n]", &(MF[(C+1)*i]));
        
        fclose(inputfile);
    }
    
    MPI_Bcast(MF, W*(C+1), MPI_CHAR, 0, MPI_COMM_WORLD);

    // Preparando as matrizes e variáveis para distribuir MS dentre os processos
    // GLOBAL_FOUND irá possuir os valores das linhas e colunas de cada MF[i] no fim.
    int  *MAT_SIZES, *MAT_DSP, N_BLOCK, N_BLOCK_RESTO, PL, *GLOBAL_FOUND, *VET_FOUND;
    char *PMS;

    // Particionando as linhas de MS dentre os processos
    N_BLOCK       = L/num_proccess;
    N_BLOCK_RESTO = L%num_proccess;

    // Preparando os vetores para o Scatterv
    MAT_SIZES = (int*) malloc(num_proccess * sizeof(int));
    MAT_DSP   = (int*) malloc(num_proccess * sizeof(int));

    // Preparando o vetor PMS (MS local ao processo)
    PMS = (char*) malloc((N_BLOCK+N_BLOCK_RESTO)*(C+1)*sizeof(char));

    // Preparando o vetor que irá salvar as respostas encontradas
    VET_FOUND = (int*) malloc(2*W*sizeof(int));
    memset(VET_FOUND, -1, 2*W*sizeof(int));

    if(rank == 0){
        GLOBAL_FOUND = (int*) malloc(2*W*sizeof(int));
        memset(GLOBAL_FOUND, -1, 2*W*sizeof(int));
    }
    
    // Calculo os valores de MAT_SIZES e MAT_DSP e transmitindo para os processos
    if(rank == 0){
        int pos = 0;
        for(int p = 0; p < num_proccess; p++){
            MAT_DSP[p]   = pos;
            MAT_SIZES[p] = (p < N_BLOCK_RESTO) ? (C+1)*(N_BLOCK+1) : (C+1)*N_BLOCK;
            pos         += MAT_SIZES[p];
        }
    }

    MPI_Scatterv(MS, MAT_SIZES, MAT_DSP, MPI_CHAR, PMS, (C+1)*(N_BLOCK+N_BLOCK_RESTO), MPI_CHAR, 0, MPI_COMM_WORLD);
    
    // Quantidade de linhas recebidas no Scatter (L local ao processo)
    PL = (rank < N_BLOCK_RESTO) ? (N_BLOCK+1) : (N_BLOCK);

    // Paralelizando a busca de cada palavra linha a linha
    #pragma omp parallel for collapse(2) 
    for(int w = 0; w < W; w++){
        for(int l = 0; l < PL; l++){
            char* search_ptr = strstr( &(PMS[(C+1)*l]), &(MF[(C+1)*w]));

            // obs: Não é região crítica devido à garantia dada pelo enunciado
            if( search_ptr != NULL){
                VET_FOUND[2*w] = l;
                VET_FOUND[2*w] += (rank < N_BLOCK_RESTO) ? (N_BLOCK+1)*rank : (N_BLOCK+1)*N_BLOCK_RESTO + (rank-N_BLOCK_RESTO)*N_BLOCK;
                VET_FOUND[2*w+1] = search_ptr - &(PMS[(C+1)*l]);
            }
        }
    }
    
    // Reduzindo as respostas para o mestre
    MPI_Reduce(VET_FOUND, GLOBAL_FOUND, (2*W), MPI_INT, MPI_MAX, 0,  MPI_COMM_WORLD);

    // Exibindo os valores encontrados
    if(rank == 0){
        for(int w = 0; w < W; w++){
            printf("%s,%d,%d\n", &(MF[(C+1)*w]), GLOBAL_FOUND[2*w], GLOBAL_FOUND[2*w+1]);
        }
    }

    // Desalocando as memórias
    if(rank == 0)
        free(inputfilename);

    if(rank == 0)
        free(MS);
    free(MF);
    
    free(MAT_SIZES);
    free(MAT_DSP);
    free(PMS);

    free(VET_FOUND);

    if(rank == 0)
      free(GLOBAL_FOUND);

    MPI_Finalize();
    return 0;

}

