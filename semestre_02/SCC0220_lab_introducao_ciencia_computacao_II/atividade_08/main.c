/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex08. 	Contagem de Operações nas Ordenações
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * A fim de verificar o desempenho de diferentes algoritmos de ordenação, o programa
 * recebe um array desordenado de tamanho N e em seguida testa X algoritmos de
 * ordenação, especificados via input.
 *
 * Após as ordenações, o programa retorna qual foi o algoritmo que realiçou mais
 * e menos Comparações/Movimentações.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"

typedef struct {
	char nome[20];
	int moves;
	int comps;
	elem* vet;
} Algoritmo;

int main(void){
	
	Algoritmo algs[5];
	elem vetOriginal[30005];
	int qtdAlgoritmos, tamArray;
	
	// Lendo as entradas
	scanf(" %d", &qtdAlgoritmos);
	scanf(" %d", &tamArray);

	for(int i = 0; i < qtdAlgoritmos; i++){
		algs[i].moves = 0;
		algs[i].comps = 0;
		algs[i].vet = malloc((tamArray+1)*sizeof(elem));
		scanf(" %s", algs[i].nome);
	}

	for(int i = 0; i < tamArray; i++)
		scanf("%d", &vetOriginal[i]);

	// Executando os sorts
	for(int i = 0; i < qtdAlgoritmos; i++){

		// printf("Executando %s...\n", algs[i].nome);

		if(strcmp(algs[i].nome, "INSERTIONSORT") == 0){

			for(int j = 0; j < tamArray; j++) 
				algs[i].vet[j] = vetOriginal[j];

			insertionSort(algs[i].vet, tamArray, &algs[i].comps, &algs[i].moves);

		} else if(strcmp(algs[i].nome, "BUBBLESORT") == 0){

			for(int j = 0; j < tamArray; j++) 
				algs[i].vet[j] = vetOriginal[j];
			
			bubbleSort(algs[i].vet, tamArray, &algs[i].comps, &algs[i].moves);

		} else if(strcmp(algs[i].nome, "MERGESORT") == 0){

			for(int j = 0; j < tamArray; j++) 
				algs[i].vet[j] = vetOriginal[j];

			mergeSort(algs[i].vet, 0, tamArray-1, &algs[i].comps, &algs[i].moves);

		} else if(strcmp(algs[i].nome, "HEAPSORT") == 0){

			for(int j = 0; j < tamArray; j++) 
				algs[i].vet[j+1] = vetOriginal[j];

			heapSort(algs[i].vet, tamArray, &algs[i].comps, &algs[i].moves); 

		} else if(strcmp(algs[i].nome, "QUICKSORT") == 0){

			for(int j = 0; j < tamArray; j++) 
				algs[i].vet[j] = vetOriginal[j];

			quickSort(algs[i].vet, 0, tamArray-1, &algs[i].comps, &algs[i].moves);

		}

		free(algs[i].vet);
	}

	int    menorC = 0x3f3f3f3f, maiorC = 0;
	char  *nomeMenorC, *nomeMaiorC;

	int    menorM = 0x3f3f3f3f, maiorM = 0;
	char  *nomeMenorM, *nomeMaiorM;

	for(int i = 0; i < qtdAlgoritmos; i++){
		
		if(algs[i].comps < menorC){
			menorC = algs[i].comps;
			nomeMenorC = algs[i].nome;
		}

		if(algs[i].comps > maiorC){
			maiorC = algs[i].comps;
			nomeMaiorC = algs[i].nome;
		}
		
		if(algs[i].moves < menorM){
			menorM = algs[i].moves;
			nomeMenorM = algs[i].nome;
		}
	
		if(algs[i].moves > maiorM){
			maiorM = algs[i].moves;
			nomeMaiorM = algs[i].nome;
		}

	}

	printf("Menor C: %s\n", nomeMenorC);
	printf("Maior C: %s\n", nomeMaiorC);
	printf("Menor M: %s\n", nomeMenorM);
	printf("Maior M: %s\n", nomeMaiorM);

	return 0;
}


/* EXEMPLOS DE RETORNOS

	// vet[0] = 99;
	// vet[1] = 37;
	// vet[2] = 9;
	// vet[3] = 1;
	// vet[4] = 22;
	// vet[5] = 38;
	// vet[6] = 13;
	// vet[7] = 14;
	// vet[8] = 99;
	// bubbleSort(vet, 8, &comps, &moves);    // Moves 51 e Comps 28
	// insertionSort(vet, 8, &comps, &moves); // Moves 33 e Comps 25
	// mergeSort(vet, 0, 7, &comps, &moves);  // Moves 48 e Comps 15
	// quickSort(vet, 0, 7, &comps, &moves);  // Moves 42 e Comps 35
	// heapSort(vet, 8, &comps, &moves);      // Moves 63 e 12 Comps
*/