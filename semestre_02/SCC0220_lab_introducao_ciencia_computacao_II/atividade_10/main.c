/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex10. 	Representar Imagem com TAD de Árvore Quartenária
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * O programa utiliza uma árvore quartenária que representa uma imagem de 1024px,
 * cujos pixels podem apresentar a cor preta ou branca.
 *
 * O objetivo do programa é realizar a sobreposição pares de árvores e contar a
 * quantidade total de pixels pretos após o fim de cada sobreposição.
 *
 * Os filhos de um nó representam os quadrantes do pai, e dividem a sua quantidade
 * de pixel em 4 partes. Portanto, uma imagem com apenas a raíz é totalmente branca,
 * ou preta. Já uma árvore com uma raíz e 4 filhos pode possuir os 4 quadrantes
 * de cores distintas.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_quart.h"

int main(){
	
	// tamanho máximo que a string pode assumir, soma de PG {1,4¹,4²,4³,4⁵,4⁶} == [1*(4⁶-1)/4-1] == 1366
	ArvoreQuart arv1, arv2;
	int n;
	char *str; 
	size_t maxlen = 1366, strSize1, strSize2;
	
	
	str = malloc(sizeof(char)*maxlen); 
	
	// Lendo a quantidade de comparacoes que serao feitas
	scanf("%d", &n);
	getchar();
	
	for(int i = 1; i <= n; i++){
		
		// Construindo as arvores com as strings
			scanf("%1366[^\n]", str); getchar();
			strSize1 = strlen(str);
			construirArvore(&arv1, str, strSize1);
			// printArvore(&arv1);

			scanf("%1366[^\n]", str); getchar();
			strSize2 = strlen(str);
			construirArvore(&arv2, str, strSize2);
			// printArvore(&arv2);
			
			printf("%d %d pixels pretos.\n", i, mesclarCores(&arv1, &arv2));

			destruirArvore(&arv1);
			destruirArvore(&arv2);
	}
	
	return 0;
}
