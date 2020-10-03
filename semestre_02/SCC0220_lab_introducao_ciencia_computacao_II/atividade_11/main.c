/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex11. 	Tabela Hash V1
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * Realizar a implementação básica de uma Tabela Hash que permita a inserção
 * e a busca de strings. 
 */
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

#define STR_MAXSIZE 40

int main(int argc, char* argv[]){

	HashTable hash;
	char *str, opt;

	criarHashTable(&hash);

	do{	
		// lendo o comando
		scanf("%c", &opt);

		if(opt != 'f'){
			str = malloc(STR_MAXSIZE*sizeof(char));
			scanf("%40s", str);
		}

		// Opcoes do programa
		switch(opt){
			case 'i': // Inserir dado
				// retorna -1 em caso de falha de inserção.
				if(ht_inserirDado(&hash, str) == -1) 
					free(str);
				break;

			case 'b': // Buscar dado
				if(ht_buscarDado(&hash, str) == -1)
					printf("nao encontrado\n");
				else
					printf("encontrado\n");
				free(str);
				break;

			case 'r': // Remover dado
				if(!ht_removerDado(&hash, str))
				free(str);
				break;
		}

		getchar();

	} while(opt != 'f');

	// printf("\n\nColisões da tabela: %d.\n\n", hash.colisoes);

	removerHashTable(&hash);

	return 0;
}