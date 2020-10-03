/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex12. 	Implementação de Árvore Binária
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * Realizar a implementação básica de uma Árvore Binária, além de implementar
 * todos so 4 diferentes tipos de exibição de seu conteúdo.
 */
#include <stdlib.h>
#include <stdio.h>
#include "arvore_bb.h"

int main(void){

	ArvoreBB abb;
	int      elem;
	char     opcao;

	criarArvoreBB(&abb);

	do{
		scanf("%c", &opcao);

		switch(opcao){
			case 'I': // Inserir novo elemnto
				scanf("%d", &elem);
				if(abb_inserirElemento(&abb, elem))
					printf("Chave existente\n");
				break;

			case 'D': // Remover elemento
				scanf("%d", &elem);
				if(abb_removerElemento(&abb, elem))
					printf("Nao encontrado\n");
				else
					printf("%d \n", elem);
				break;

			case 'B': // Buscar elemento
				scanf("%d", &elem);
				if(abb_buscarElemento(&abb, elem))
					printf("Encontrado\n");
				else
					printf("Nao encontrado\n");
				break;

			case 'N': // Imprimir In-ordem
				abb_printInOrdem(&abb);
				break;

			case 'E': // Imprimir Pré-ordem
				abb_printPreOrdem(&abb);
				break;

			case 'O': // Imprimir Pós-ordem
				abb_printPosOrdem(&abb);
				break;

			case 'L': // Imprimir Largura
				abb_printLargura(&abb);
				break;

			case 'Y': // Imprimir de todas as maneiras anteriores
				abb_printInOrdem(&abb);
				abb_printPreOrdem(&abb);
				abb_printPosOrdem(&abb);
				abb_printLargura(&abb);
				break;
		}


	}while(opcao != 'X' && opcao != 'x');

	destruirArvoreBB(&abb);

	return 0;
}