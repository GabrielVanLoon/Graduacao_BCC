/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex13. 	Tabela Hash V2
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * Ajuste da tabela hash implementada na tarefa 13 para que ela trate as colisões
 * utilizando uma árvore binária. Além disso, para que houvesse basntantes colisões
 * foi utilizado um hash simples de divisão. [x % 100].
 *
 * Obs.: Nem todos os comentários foram ajustados.
 */

#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

#define STR_MAXSIZE 40

int main(int argc, char* argv[]){

	HashTable hash;
	char opt;
	int  chave;

	criarHashTable(&hash);

	do{	

		// lendo o comando
		scanf("%c", &opt);

		if(opt != 'f' && opt != 'p'){
			scanf("%d", &chave);
		}

		// Opcoes do programa
		switch(opt){
			case 'i': // Inserir dado	
				ht_inserirDado(&hash, chave);
				break;

			case 'b': // Buscar dado
				if(ht_buscarDado(&hash, chave) == -1)
					printf("nao encontrado\n");
				else
					printf("encontrado\n");
				break;

			case 'r': // Remover dado
				ht_removerDado(&hash, chave);
				break;

			case 'p': // Imprime a hash table
				ht_printHashTable(&hash);
				break;

			case 'f':
				break;
		}

		// getchar();

	} while(opt != 'f');

	// printf("\n\nColisões da tabela: %d.\n\n", hash.colisoes);

	removerHashTable(&hash);

	return 0;
}