/** Projeto 02 - Algoritmos e Estrutura de Dados
 *  Título     - Manipulação de Dados em Memórias primárias
 *	Descrição  - Programa que analisa as operações de inserção, busca e remoção
 *               de 6 Estruturas de Dados em distintos cenários e tamanhos.
 *  Retorno    - O programa imprime o resultade de custo médio de tempo para 
 *               cada uma das operações em diferentes cenários.
 *
 *  Atenção    - Dependendo das configurações, o código pode demorar até 3 horas
 *               para terminar todos os testes.
 *
 *  Autores    - Gabriel Van Loon & Giovani Lucafó
 *  ICMC-USP   - dezembro/2018
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "analise.h"
#include "tads/lista_ordenada.h"
#include "tads/listaord_sentinela.h"
#include "tads/abb.h"
#include "tads/buscabin.h"
#include "tads/listacirc_freq.h"
#include "tads/avl.h"

#define REPETICOES  10  // Valor ideal: 10
#define TAM_INICIAL 100 // Valor ideal: 100
#define CRESCIMENTO 2   // Valor entre: {1,2,3,4}
#define EXIBIR_LOGS 0   // 1 para ativar e 0 para desativar

int main(void){
	
	// Tads
	BuscaBin   		bb;  
	ListaOrdenada 	lo;
	ListaOrdSent	los;
	ABB				abb;
	AVL 			avl;
	ListaFreq 		lfreq;
	
	// Array que contem o ponteiro das tads
	void* tad[6];
	
	// Variáveis para as strings
	char titulos[9][70];
	char colunas[48];
	char linhas[6][10];
	
	/**
	 * Matrizes que salvam os resultados. Uma para cada tipo de teste.
	 * Os indices indicam: [TAD][TIPO][TAMANHO DO TESTE][OPERACAO] sendo que
	 * 
	 * [tad] >>	[0] =: BB			[tipo] >> [0] =: Crescente
	 * 			[1] =: LO					  [1] =: Decrescente
	 * 			[2] =: LOS					  [2] =: Desordenado
	 * 			[3] =: ABB			
	 * 			[4] =: AVL			[TAM]  >> []  =: 10, 10², 10³ ou 10⁵ 
	 * 			[5] =: LFREQ		                 Elementos.
	 */  
		double resultados[6][3][4][3] = {0};
	
	/**
	 * Associa um TAD às suas funções de: 

	 * - InserirElemento	[0];
	 * - RemoverElemento	[1]  
	 * - BuscarElemento		[2], 
	 */
		int (*funcoesInt[6][3])(void*, int);
	
	/**
	 * Associa um TAD às suas funções com retorno void
	 * - criarTAD		[0]; 
	 * - eliminarTAD	[1];
	 * - auxiliar		[3]  
	 */
		void (*funcoesVoid[6][3])(void*);
	
	/**
	 * Associando as funcoes void à matriz
	 */
		funcoesVoid[0][0] = bb_criarVetor; 					// BB
		funcoesVoid[0][1] = bb_finalizarVetor; 		
		funcoesVoid[0][2] = bb_ordenarElementos;
		
		funcoesVoid[1][0] = lo_criarListaOrdenada;			// LO
		funcoesVoid[1][1] = lo_finalizarListaOrdenada;
		funcoesVoid[1][2] = lo_ordenarLista;
		
		funcoesVoid[2][0] = los_criarLista;					// LOS
		funcoesVoid[2][1] = los_finalizarLista;
		funcoesVoid[2][2] = NULL;
		
		funcoesVoid[3][0] = abb_criarArvore;				// ABB
		funcoesVoid[3][1] = abb_eliminarArvore;
		funcoesVoid[3][2] = NULL;
		
		funcoesVoid[4][0] = avl_criarArvore;				// AVL
		funcoesVoid[4][1] = avl_finalizarArvore;
		funcoesVoid[4][2] = NULL;
		
		funcoesVoid[5][0] = lfreq_criarLista;				// LFREQ
		funcoesVoid[5][1] = lfreq_eliminarLista;	
		funcoesVoid[5][2] = NULL;	

	/**
	 * Associando as funcoes que vao ser testadas à matriz
	 */
		funcoesInt[0][0] = bb_inserirElemento; 		// BB
		funcoesInt[0][1] = bb_eliminarElemento;
		funcoesInt[0][2] = bb_buscarElemento;
		
		funcoesInt[1][0] = lo_inserirElemento; 		// LO
		funcoesInt[1][1] = lo_eliminarElemento; 
		funcoesInt[1][2] = lo_buscarElemento; 
		
		funcoesInt[2][0] = los_inserirElemento; 	// LOS
		funcoesInt[2][1] = los_eliminarElemento; 
		funcoesInt[2][2] = los_buscarElemento;
		
		funcoesInt[3][0] = abb_inserirElemento; 	// ABB
		funcoesInt[3][1] = abb_eliminarElemento; 
		funcoesInt[3][2] = abb_buscarElemento;
		
		funcoesInt[4][0] = avl_inserirElemento;		// AVL
		funcoesInt[4][1] = avl_eliminarElemento;
		funcoesInt[4][2] = avl_buscarElemento; 
		
		funcoesInt[5][0] = lfreq_inserirElemento;	// LFREQ
		funcoesInt[5][1] = lfreq_eliminarElemento;	
		funcoesInt[5][2] = lfreq_buscarElemento;	
	

	//Obs: Atribua NULL para as estruturas que você não pretende testar.
	tad[0] = &bb;
	tad[1] = &lo;
	tad[2] = &los;
	tad[3] = &abb;
	tad[4] = &avl;
	tad[5] = &lfreq;
	
	// Inserindo os valores das strings
	strcpy(titulos[0], 	"Tabela 1: Tempo de insercao crescente\n");
	strcpy(titulos[1], 	"Tabela 2: Tempo de insercao decrescente\n");
	strcpy(titulos[2], 	"Tabela 3: Tempo de insercao aleatoria\n");
	strcpy(titulos[3], 	"Tabela 4: Tempo de remocao crescente (apos insercao crescente)\n");
	strcpy(titulos[4], 	"Tabela 5: Tempo de remocao decrescente (apos insercao crescente)\n");
	strcpy(titulos[5], 	"Tabela 6: Tempo de remocao aleatoria (apos insercao aleatoria)\n");
	strcpy(titulos[6], 	"Tabela 7: Tempo de busca (apos insercao crescente)\n");
	strcpy(titulos[7], 	"Tabela 8: Tempo de busca (apos insercao decrescente)\n");
	strcpy(titulos[8], 	"Tabela 9: Tempo de busca (apos insercao aleatoria)\n");
	
	strcpy(colunas, 	"\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	strcpy(linhas[0], 	"BB");
	strcpy(linhas[1], 	"LO");
	strcpy(linhas[2], 	"LOS");
	strcpy(linhas[3], 	"ABB");
	strcpy(linhas[4], 	"AVL");
	strcpy(linhas[5], 	"LFREQ");
	
	/****************************
	 * AREA DE TESTES DAS TADS
	 ***************************
		avl_criarArvore(&avl);

		avl_inserirElemento(&avl, 10);
		avl_inserirElemento(&avl, 5);
		avl_inserirElemento(&avl, 11);
		avl_inserirElemento(&avl, 13);
		avl_printInOrdem(&avl);

		avl_inserirElemento(&avl, 12);
		avl_printInOrdem(&avl);

		// avl_eliminarElemento(&avl, 7);
		// avl_eliminarElemento(&avl, 8);
		// avl_printInOrdem(&avl);

		avl_finalizarArvore(&avl);

		return 0;*/

	/**
	 * Exmplicando o for abaixo triplamente aninhado:
	 * 	for( TAD ATUAL
	 * 		for( TIPO DE TESTE 
	 * 			for( TAMANHO DO TESTE
	 * 				for( REPETIÇÕES
	 */
	 int qtdElementos;
	 for(int i = 0; i < 6; i++){ 
		if(tad[i] == NULL) continue; // Erro: Tad não definido.
		
		for(int j = 0; j < 3; j++){     
			
			qtdElementos = TAM_INICIAL; // Tamanho inicial do teste
			for(int k = 0; k < CRESCIMENTO; k++){ // Ajuste entre k < {1..4} para aumentar a quantidade de elementos.
				
				resultados[i][j][k][0] = 0.0; 
				resultados[i][j][k][1] = 0.0; 
				resultados[i][j][k][2] = 0.0; 
				
				// Executa o teste no tad 10x e tira a média dos valores
				for(int r = 0; r < REPETICOES; r++){
					if(EXIBIR_LOGS ) printf("Teste no TAD %s, Modo %d, Quantidade %d, Repeticao nº%d.\n", linhas[i], j, qtdElementos, r+1);
					funcoesVoid[i][0](tad[i]); // Estancia
					resultados[i][j][k][0] += tempo_insercao(	qtdElementos, j, funcoesInt[i][0], tad[i], funcoesVoid[i][2]);
					resultados[i][j][k][2] += tempo_busca(		qtdElementos, j, funcoesInt[i][2], tad[i]);
					resultados[i][j][k][1] += tempo_remocao(	qtdElementos, j, funcoesInt[i][1], tad[i]);
					funcoesVoid[i][1](tad[i]); // Destroi
				}
				
				// Tirando a média dos resultados
				resultados[i][j][k][0] = resultados[i][j][k][0]/(double)REPETICOES; 
				resultados[i][j][k][1] = resultados[i][j][k][1]/(double)REPETICOES; 
				resultados[i][j][k][2] = resultados[i][j][k][2]/(double)REPETICOES; 
					
				qtdElementos *= 10; // Aumentando a qtd. elementos 
			}
		}
	 }
	 
	 /**
	 * Exmplicando o for abaixo triplamente aninhado:
	 * 	for( FUNÇÃO SENDO TESTADA
	 * 		for( TIPO DE TESTE {crescente, decrescente, aleatório}
	 * 			for( TAD ATUAL
	 */
	 int tb = 0;
	 
	 for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			
			printf("%s", titulos[tb]);
			printf("%s", colunas);
			
			for(int k = 0; k < 6; k++){
				printf("%s\t%lf\t%lf\t%lf\t%lf\n", linhas[k], resultados[k][j][0][i], resultados[k][j][1][i], resultados[k][j][2][i], resultados[k][j][3][i]);
			}
			
			printf("-\n");
			tb++;
		}
	 }
	
	return 0;
}
