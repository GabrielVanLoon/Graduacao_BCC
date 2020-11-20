/*
 * INTEGRANTES
 * -----------
 * Gabriel van Loon Bode da Costa Dourado Fuentes Rojas (10391607)
 * João Ricardo Minoru Nagasava (10734449)
 * Mathias Fernandes Duarte Coelho (10734352)
 * Luiz Miguel Di Mano Saraiva (10425420)
 * 
 * RESUMO
 * ------
 * O programa irá receber como entrada 2N² valores numéricos que representam os elementos das 
 * 2 matrizes quadradas Ae B. O programa então deverá calcular uma nova matriz C cujos valores 
 * serão resultantes da expressão C=(A*B). No fim, a matriz C resultante deverá ser impressa 
 * para o usuário.
 * 
 * PARTICIONAMENTO
 * ---------------
 * O primeiro estágio se trata de receber os valores das duas matrizes A e B e se trata de uma 
 * tarefa sequencial.
 * 
 * Após a leitura dos dados, podemos realizar um particionamento por dados da multiplicação de 
 * A com B usando N³ tarefas, cada uma sendo responsável por três posições i, j e kque irão 
 * calcular a soma parcial da multiplicação dada por p[i, j] = a[i, k] * b[k, j].
 * 
 * Após as multiplicações, devemos somar os resultados parciais para encontrar o valor de cada 
 * posição c[i,j] da matriz C e para isso podemos utilizar N²(logN) tarefas ao fazer, para cada
 * posição de c[i,j] uma redução das somas parciais.
 * 
 * Por fim, uma tarefa mestre deverá exibir a matriz C resultante na tela do usuário.
 * 
 * COMUNICAÇÃO
 * -----------
 * No primeiro estágio cada uma das N3 tarefas deverá ser inicializada com as posições i,j e k
 * com que serão responsáveis. Elas também deverão receber de uma tarefa principal os valores 
 * necessários para o cálculo, que serão o valor a[i,k] e b[k, j].
 * 
 * Após o término de todas as tarefas, deverá haver uma sincronização para que as somas parciais 
 * calculadas sejam transmitidas (podendo utilizar, se possível, um método de redução de ordem 
 * logarítmica) para uma tarefa principal responsável por salvar os valores finais na matriz C.
 * 
 * Por fim, após o final do estágio da soma, a tarefa principal também deverá exibir os valores 
 * da matriz C para o usuário.
 *
 * AGLOMERAÇÃO
 * -----------
 * Durante a etapa de multiplicação, iremos aglomerar as tarefas p[i, j] = a[i, k] * b[k, j] em 
 * P processos tal que tarefas com o mesmo valor de i (ou seja, na mesma linha de A[i] e C[i]) 
 * estejam sempre no mesmo grupo. 
 * 
 * Cada processo P terá aproximadamente, portanto, N³/P multiplicações para serem executadas e 
 * N²logN/P tarefas de soma. Caso não seja possível dividir as tarefas igualmente de forma que
 * se respeite as regras de alinhamento, as tarefas restantes deverão ser entregues ao último 
 * processo ou distribuída dentre os primeiros N mod P processos.
 * 
 * Dessa forma, dada uma matriz A = [[2, 4], [2,4]] e B=[[1, 0], [0,1]] e P=2, cada processo 
 * receberá um bloco de dados 1x2 de A e a matriz inteira de B. 
 * 
 * Por fim, na etapa final do estágio da soma, cada processo deverá comunicar seus resultados
 * para um processo final realizar o armazenamento e, posteriormente, a exibição dos resultados.
 * 
 * MAPEAMENTO
 * ----------
 * Dado um ambiente de execução com K nós de processamento, cada um com C processadores de 
 * capacidade homogênea, podemos distribuir os P processos entre os K nós igualmente. Caso 
 * algum nó possua capacidade muito discrepante é possível realizar uma divisão que pondere 
 * a quantidade de processos de forma proporcional.
 * 
 * Após o mapeamento dos P processos ainda é possível mapear as tarefas dentre as C unidades de
 * processamento de um mesmo nó, para isso basta realizar um novo particionamento das tarefas 
 * seguindo a mesma lógica de particionamento, comunicação e aglomeração vistos anteriormente.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "mpi.h"

#define N 1000
#define NUMTHREADS 4

double** aloca_matriz(int LINHAS, int COLUNAS) {
	double **matriz = (double**) malloc(LINHAS*sizeof(double*));
	for (int i = 0; i < LINHAS; i++)
		matriz[i] = (double*) malloc(COLUNAS*sizeof(double));
	return matriz;
}

int main(int argc, char *argv[]){

	// Variáveis do MPI
	int rank, num_proccess;
	MPI_Status status;

	MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proccess);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(num_proccess <= 1){
		printf("[%d/%d] Please set more proccess to execute with -np X\n", rank, num_proccess);
		MPI_Finalize();
		return 0;
	}

	// Variáveis do Problema
	double** matrizA = NULL;
	double** matrizB = NULL;
    double** matrizC = NULL;
	int i = 0, j = 0, k = 0, l = 0;
	int L; // Linhas e Colunas da matriz A do processo

	// O mestre realiza as seguintes ações
	// - Leitura da matriz A e B, alocação completa de A B e C
	// - Distribui B completa para todas os processos
	// - Distribui as linhas de A para os processos (mestre incuso)
	if(rank == 0){
		matrizA = aloca_matriz(N,N);
		matrizB = aloca_matriz(N,N);
   		matrizC = aloca_matriz(N,N);

		// Lê a matriz A e B
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				scanf("%lf", &matrizA[i][j]);
			}
		}

		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				scanf("%lf", &matrizB[i][j]);
			}
		}
		
		// Broadcast da Matriz B
		// MPI_Bcast(matrizB, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		for(i = 0; i < N; i++)
			MPI_Bcast(matrizB[i], N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		// Distribuindo as linhas
		int linhas_per_proc = N/num_proccess;

		for(i = 1; i < num_proccess; i++){
			for(l = 0; l < linhas_per_proc; l++ ){
				int linha_send = l + linhas_per_proc*i;
				MPI_Send(matrizA[linha_send], N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			}
		}
			
		// Distribuindo as linhas sobressalentes para o ultimo processo
		for(l = linhas_per_proc*(num_proccess); l < N; l++)
			MPI_Send(matrizA[l], N, MPI_DOUBLE, (num_proccess-1), 0, MPI_COMM_WORLD);

		// Definindo a seção LxC que o processo 0 irá lidar
		L = linhas_per_proc;
		

	// Restante dos processos
	// - Aloca a matriz B completamente
	// - Alocar a matriz B e C apenas o necessário
	} else {

		// Recebe a matriz B completa
		matrizB = aloca_matriz(N,N);

		// Broadcast da Matriz B]
		// MPI_Bcast(matrizB, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		for(i = 0; i < N; i++)
			MPI_Bcast(matrizB[i], N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		// // Recebendo as linhas que foi designado e alocando
		int linhas_per_proc = N/num_proccess;
		linhas_per_proc += (rank == num_proccess-1) ? N%num_proccess : 0;

		matrizA = aloca_matriz(linhas_per_proc, N);
   		matrizC = aloca_matriz(linhas_per_proc, N);

		// // Recebendo os valores do mestre
		for(l = 0; l < linhas_per_proc; l++)
			MPI_Recv(matrizA[l], N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

		// Definindo a ordem LxC da matriz A
		L = linhas_per_proc;
		
	}
	
	// Todos os processos vão fazer a multiplicação de C = A * B de acordo com
	// a região que lhes foi designada e a multipliacação é melhora com OMP

	double t = omp_get_wtime();
    double soma_parcial = 0;

    #pragma omp parallel num_threads(NUMTHREADS) shared(matrizA, matrizB, matrizC) private(soma_parcial)
    {
        #pragma omp for collapse(2)  
        for(i = 0; i < L; i++) {
            for(j = 0; j < N; j++) {
                soma_parcial = 0;

                #pragma omp parallel for reduction(+:soma_parcial)
                for(k = 0; k < N; k++) {
                    soma_parcial += matrizA[i][k] * matrizB[k][j];
                }   
                matrizC[i][j] = soma_parcial;
            }
        }
    }
	t = omp_get_wtime() - t;

	// Após o computo das linhas de C
	// Os Slaves devem:
	// - Enviar as linhas de C computadas para o mestre
	if(rank != 0){
		for(l = 0; l < L; l++)
			MPI_Send(matrizC[l], N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

		// Desaloca matrizes originais
		for(int i = 0; i < L; i++) free(matrizA[i]);
		for(int i = 0; i < N; i++) free(matrizB[i]);
		for(int i = 0; i < L; i++) free(matrizC[i]);
	
	// O Mestre:
	// - Recebe e completa as linhas de C 
	// - Exibe a matriz C final para o usuário
	} else {
		int linhas_per_proc = N/num_proccess;

		// Recebendo as linha dos N-1 Slaves
		for(i = 1; i < num_proccess; i++){
			for(l = 0; l < linhas_per_proc; l++ ){
				int linha_recv = l + linhas_per_proc*i;
				MPI_Recv(matrizC[linha_recv], N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
			}
		}
			
		// Recebendo o sobrecalente do ultimo slave
		for(l = linhas_per_proc*(num_proccess); l < N; l++)
			MPI_Recv(matrizC[l], N, MPI_DOUBLE, (num_proccess-1), 0, MPI_COMM_WORLD, &status);

		// Imprimindo a matriz C
		for(int i = 0; i < N; i++) {
			for(j = 0; j < (N-1); j++) {
				printf("%.1lf ", matrizC[i][j]);
			}
			printf("%.1lf\n", matrizC[i][j]);
		}

		// Desaloca matrizes originais
		for(int i = 0; i < N; i++) free(matrizA[i]);
		for(int i = 0; i < N; i++) free(matrizB[i]);
		for(int i = 0; i < N; i++) free(matrizC[i]);
	}
    
	free(matrizA);
	free(matrizB);
	free(matrizC);

	MPI_Finalize();

    return 0;
}