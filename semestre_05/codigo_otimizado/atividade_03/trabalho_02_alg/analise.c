#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "analise.h"

/**
 * @clock_t tempo_insercao(int n, int opt, int (*insere)(void*, int)); 
 */
double tempo_insercao(int n, int opt, int (*insere)(void*, int), void* tad, void (*aux)(void*)){
	if(insere == NULL) return 0.0;

	clock_t clk_ini, clk_fim;
	int 	valor;
	
	clk_ini = clock();
	
	if(opt == CRESCENTE) {
		// Insere os 'n' elementos em ordem crescente
		for(int i = 0; i < n; i++)
			if(insere(tad, i))	i--;
		
	} else if(opt == DECRESCENTE) {
		// Insere os 'n' elementos em ordem descrescente
		for(int i = n-1; i > 0; i--)
			if(insere(tad, i))	i++;
	
	} else {
		srand(time(NULL));
		
		// Insere os 'n' elementos em ordem crescente
		for(int i = 1; i <= n; i++){
			valor = (rand() % n);
			if(insere(tad, valor)) i++;
		}
		
	}
	
	if(aux != NULL)
		aux(tad); // Funcao Auxiliar
	
	clk_fim = clock();
	
	// Retire o comententário para ver o tempo de cada execução.
	// printf("Tempo de Exec. %lf\n", ((double) clk_fim - clk_ini)/CLOCKS_PER_SEC );

	return ((double) clk_fim - clk_ini)/CLOCKS_PER_SEC;
}

/**
 * @clock_t tempo_insercao(int n, int opt, int (*insere)(void*, int)); 
 * 
 * Testa o tempo para inserir n elementos em um tad de elementos inteiros
 */
double tempo_remocao(int n, int opt, int (*remove)(void*, int), void* tad){
	if(remove == NULL) return 0.0;

	clock_t clk_ini, clk_fim;
	int 	valor;
	
	clk_ini = clock();
	
	if(opt == CRESCENTE) {
		// Remove n/2 elementos existentes
		for(int i = 0; i < n/2; i++)
			remove(tad, i);

	} else if(opt == DECRESCENTE) {
		// Remove n/2 elementos existentes em ordem decrescente
		for(int i = (n/2)-1; i >= 0; i--)
			remove(tad, i);
	
	} else {
		srand(time(NULL));
		// Remove n/2 elementos existentes
		for(int i = (n/2)-1; i < n/2; i++)
			remove(tad, i);

		// Insere os 'n' elementos em ordem crescente
		// for(int i = 1; i <= n; i++){
		//	valor = rand()%n;
		//	if(remove(tad, valor)) i++;
		//}
	}

	// Remove n/4 elementos não existentes pequenos
	for(int i = 0; i < n/4; i++)
		remove(tad, i);
	// Remove n/4 elementos não existentes grandes
	for(int i = 0; i < n/4; i++)
		remove(tad, n+i);
	
	clk_fim = clock();
	
	return ((double) clk_fim - clk_ini)/CLOCKS_PER_SEC;
}

/**
 * @clock_t tempo_insercao(int n, int opt, int (*busca)(void*, int)); 
 * 
 * Testa o tempo para inserir n elementos em um tad de elementos inteiros
 */
double tempo_busca(int n, int opt, int (*busca)(void*, int), void* tad){
	if(busca == NULL) return 0.0;

	clock_t clk_ini, clk_fim;
	int 	valor;
	
	clk_ini = clock();
	
	if(opt == CRESCENTE) {
		// busca n/2 elementos existentes
		for(int i = 0; i < (n/2); i++)
			busca(tad, i);
		
	} else if(opt == DECRESCENTE) {
		// busca n/2 elementos existentes decrescentes
		for(int i = (n/2)-1; i >= 0; i--)
			busca(tad, i);
	
	} else {
		srand(time(NULL));
		
		for(int i = (n/2)-1; i < n/2; i++)
			busca(tad, i);

		// Insere os 'n' elementos em ordem crescente
		//for(int i = 1; i <= n; i++){
		//	valor = rand()%n;
		//	busca(tad, valor);
		//}
	}
	
	// Remove n/4 elementos não existentes pequenos
	for(int i = 0; i < n/4; i++)
		busca(tad, i);
	// Remove n/4 elementos não existentes grandes
	for(int i = 0; i < n/4; i++)
		busca(tad, n+i);

	clk_fim = clock();
	
	return ((double) clk_fim - clk_ini)/CLOCKS_PER_SEC;
}
