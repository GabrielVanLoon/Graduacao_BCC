/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex07. 	Lista Backward
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * Implentar uma Lista Dinâmica e não circular cujos nós possuam um ponteiro
 * que pode apontar para qualquer um dos nós anteriores ou para NULL.
 * 
 * O programa recebe qual das opções disponíveis executar e, por fim, exibe
 * a situação final da lista após as inserções e remoções.
 */
#include <stdlib.h>
#include <stdio.h>
#include "lista_encad.h"

int main(void){
	
	ListaEnc list;
	char action;
	int chave, back, tempo = 0;
	
	novaListaEncadeada(&list);
	
	do{
		scanf(" %c", &action);
		
		switch(action){
			case 'i': // Inserção de novo Nó
				scanf(" %d", &chave);
				scanf(" %d", &back);
				inserirElemento(&list, chave, back, tempo);
				break;
			case 'r': // Remover um Nó
				scanf(" %d", &chave);
				removerElemento(&list, chave);
				break;
			case 'p': // Printar lista atual
				printarListaEncadeada(&list);
				break;
		}

		tempo++;
		getchar(); // Impede leitura do \n

	}while(action != 'f');

	printarListaEncadeada(&list);
	
	removerListaEncadeada(&list);
	
	return 0;
}
