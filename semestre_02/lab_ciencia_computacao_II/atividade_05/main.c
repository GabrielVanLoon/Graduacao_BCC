/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex05. 	Campeonato Desordenado.
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * O programa recebe uma lista desordenada de atletas da FEDERAL e do CAASO e 
 * deve retornar essa mesma lista na ordem correta. A ordenação pode ser feita
 * tanto pelo nome quanto pelo id, sendo o tipo especificado na última linha do
 * programa.
 * 
 * DESCRIÇÃO
 * - O programa lê linha por linha as entradas, verificando se elas representam
 *   o nome do time ou se possuem o formato "id nome_atleta".
 * 
 * Obs.: O programa realiza um MergeSort, havendo porém um limite X de divisões
 * que podem ser feitas. Esse limite é especificado também na última linha de 
 * entrada junto com o tipo de ordenação.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista.h"

int main(void){

	Lista corredores;
	Elemento atleta;
	char strLine[60], aux[60];
	int qtdMerges;

	corredores = novaLista();

	do {
		scanf("%[^\n]", strLine);
		sscanf(strLine, "%s", aux);

		if(strcmp(aux, "FEDERAL") == 0){
			atleta.facul = FEDERAL;

		} else if(strcmp(aux, "CAASO") == 0) {
			atleta.facul = CAASO;
		
		} else if( '0' <= aux[0] && aux[0] <= '9' ){
			sscanf(strLine, "%d %[^\n]", &atleta.id, atleta.nome);
			inserirElemento(&corredores, atleta);
		
		} else if(strcmp(aux, "ID") == 0) {
			sscanf(strLine, "%s %d", aux, &qtdMerges);
			ordernarPeloID(&corredores, qtdMerges);
			break;

		} else if(strcmp(aux, "NAME") == 0) {
			sscanf(strLine, "%s %d", aux, &qtdMerges);
			ordenarPeloNome(&corredores, qtdMerges);
			break;
		
		}
		
		getchar();

	}while(1);

	printLista(&corredores);

	liberarLista(&corredores);
	
	return 0;
}