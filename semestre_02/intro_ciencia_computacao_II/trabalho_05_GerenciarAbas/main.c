/**
 * Trabalho de Introdução a Ciencia da Computacao II
 * Título: T5 - Gerenciador de Abas de Navegador
 * Autor:  Gabriel Van Loon
 * Prof.:  Moacir Ponti
 * Data:   Outubro/2018
 * 
 * DESCRIÇÃO
 * O programa implementa um gerenciador de Abas de Navegador utilizando uma
 * lista encadeada.
 *
 * Dito isso, o usuário pode realizar as ações de Criar nova aba, Exibir a lista,
 * Alterar posição de abas e por fim Ordenar com base na hora de abertura.
 * 
 * Obs. Esse projeto não foi devidamente comentado, porém seu funcionamento
 * é enxuto e 100% intuitivo.
 */
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

/**
 * @Protótipos da main.c
 */ 
	void gerarNovaAba(Aba* b);

int main(int argc, char* argv[]){

	Lista abas;
	Aba   aux;
	int   opcao, novaPosicao;

	// Preparando a variavel para uso.
	criarLista(&abas);

	do{
		scanf("%d", &opcao);
		switch(opcao){
			case 1: // Inserir nova aba.
				gerarNovaAba(&aux);
				pushBackLista(&abas, aux);
				// printf("Item inserido com sucesso!!\n\n");
				break;

			case 2: // Alterar posição da aba.
				scanf(" %30[^\n]", aux.titulo); getchar();
				scanf(" %d", &novaPosicao);
				// printf("Reposicionando [%s] para a %dª posicao....\n", aux.titulo, novaPosicao);
				reposicionarElemento(&abas,  aux.titulo, novaPosicao);
				//printf("Aba movida com sucesso!!\n\n");
				break;

			case 3: // Ordenar lista.
				ordenarLista(&abas);
				break;

			case 4: // Exibir  lista.
				printLista(&abas);
				break;
		}
	}while(opcao != 5);

	// Limpando memória alocada.
	removerLista(&abas);

	return 0;
}

/**
 * @
 */ 
void gerarNovaAba(Aba* a){
	scanf(" %30[^\n]",    a->titulo);    getchar();
	scanf(" %1024[^\n]",  a->url);       getchar();
	scanf(" %d",          &a->dt.dia);
	scanf(" %d",          &a->dt.mes);
	scanf(" %d",          &a->hr.hora);
	scanf(" %d",          &a->hr.minuto);
}