#include <stdlib.h>
#include <stdio.h>
#include "arvore_quart.h"

/**
 * Protótipos
 */
	int _construirNo(No *node, char *str, int i, int size);
	void _freeNo(No* n);
	void _printNo(No* n);
	int _mesclarNos(No *n1, No *n2, int pxs);
	int _qtdNosPretos(No *n, int pxs);

/**
 * @construirArvore(char *str, int i, int size);
 * - Dada uma string, tamanho da string e uma arvore vazia, cria uma
 *   arvore binária.
 */
	void construirArvore(ArvoreQuart *arv, char *str, int size){
		No *raiz = malloc(sizeof(No)); 
		_construirNo(raiz, str, 0, size);
		arv->ini = raiz;
	}

	int _construirNo(No *node, char *str, int i, int size){

		// Caso de parada
		if(i >= size ) return -1;

		// Caso seja uma folha vazia ou preenchida ('e' >> empty || 'f' >> fill)
		if(str[i] == 'e' || str[i] == 'f'){
			node->tipo = FOLHA;
			node->cor  = (str[i] == 'e') ? BRANCO : PRETO ;

		// Caso seja um Nó pai | sub arvore
		} else if(str[i] == 'p'){
			for(int j = 0; j < 4 && i < size; j++){
				No *f = malloc(sizeof(No));
				node->tipo = SUB;
				node->filhos[j] = f;
				i = _construirNo(f, str, i+1, size);
			}
		}

		return i;
	}

/**
 * @destruirArvore(ArvoreQuart *arv);
 * - Desaloca uma variável do tipo ArvoreQuart da memória.
 */
	void destruirArvore(ArvoreQuart *arv){
		_freeNo(arv->ini);
	}

	void _freeNo(No* n){
		if(n->tipo == FOLHA)
			free(n);
		else if(n->tipo == SUB){
			for(int j = 0; j < 4; j++) _freeNo(n->filhos[j]);
			free(n);
		}
		
	}

/**
 * @printArvore(char *str, int i, int size);
 * - Realiza o print de uma arvore quartenaria linearmente
 */
	void printArvore(ArvoreQuart *arv){
		_printNo(arv->ini);
		printf("\n");
	}

	void _printNo(No* n){
		if(n->tipo == FOLHA){
			printf("%c", (n->cor == BRANCO) ? 'E' : 'F');
		
		} else if(n->tipo == SUB) {
			printf("P");
			for(int j = 0; j < 4; j++) _printNo(n->filhos[j]);
		
		}
	}

/**
 * @mesclarCores(ArvoreQuart *arv);
 * - Realiza a mescla de cores das arvores binarias, retornando a quanti-
 *   dade de pixels pretos.
 */
	int mesclarCores(ArvoreQuart *arv1, ArvoreQuart *arv2){
		return _mesclarNos(arv1->ini, arv2->ini, 1024);
	}

	int _mesclarNos(No *n1, No *n2, int pxs){
		int result = 0;
		
		// Caso ambos sejam folhas
		if(n1->tipo == FOLHA && n2->tipo == FOLHA){
			return (n1->cor == PRETO || n2->cor == PRETO) ? pxs : 0;
		
		// Caso AMBOS sejam subarvores
		} else if(n1->tipo == SUB && n2->tipo == SUB){
			for(int j = 0; j < 4; j++)
				result += _mesclarNos(n1->filhos[j], n2->filhos[j], pxs/4);
			return result;
		
		// Um deles é folha e o outro é uma subarvore
		} else {
			No* folha  = (n1->tipo == FOLHA) ? n1 : n2;
			No* arvore = (n1->tipo == SUB)   ? n1 : n2;

			// Se a folha for preta, entao todo o quadrante ficará preto
			if(folha->cor == PRETO) 
				return pxs;
			else
				return _qtdNosPretos(arvore, pxs);
		}
	}

	int _qtdNosPretos(No *n, int pxs){
		int result = 0;
		
		if(n->tipo == FOLHA)
			result = (n->cor == PRETO) ? pxs : 0;
		else if(n->tipo == SUB) 
			for(int j = 0; j < 4; j++) 
				result += _qtdNosPretos(n->filhos[j], pxs/4);
		
		return result;
	}