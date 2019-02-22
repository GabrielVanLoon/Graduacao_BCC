#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista.h"

/**
 * @Protótipos da lista.c
 */ 
	void _bucketSort(Lista *l, int min, int max, int (*getIndice)(elemLista*));

/**
 * @
 */ 
void criarLista(Lista *l){
	l->ini = NULL;
	l->fim = NULL;
}

/**
 * @
 */ 
void removerLista(Lista *l){
	if(estaVaziaLista(l)) return;

	No* aux;

	while(l->ini != NULL){
		aux = l->ini->prox;
		free(l->ini);
		l->ini = aux;
	}

	criarLista(l);
}

/**
 * @
 */ 
int estaVaziaLista(Lista *l){
	return (l->ini == NULL);
}


/**
 * @
 */ 
elemLista frontLista(Lista *l){
	return l->ini->info; 
}

/**
 * @
 */ 
elemLista backLista(Lista *l){
	return l->fim->info;
}

/**
 * @
 */ 
int pushBackLista(Lista *l, elemLista e){
	No *aux = malloc(sizeof(No)); 
	
	aux->info = e;
	aux->prox = NULL;

	if(estaVaziaLista(l))
		l->ini = aux;
	else 
		l->fim->prox = aux;
	
	l->fim = aux;

	return 0;
}

/**
 * @
 */ 
int pushFrontLista(Lista *l, elemLista e){
	No *aux = malloc(sizeof(No)); 
	
	aux->info = e;

	if(estaVaziaLista(l))
		l->fim = aux;
	else 
		aux->prox = l->ini;
	
	l->ini = aux;

	return 0;
}

/**
 * @
 */ 
int pushBackNodeLista(Lista *l, No *n){
	if(n == NULL) return 1;
	
	n->prox = NULL;
	if(l->fim == NULL) l->ini = n;
	else               l->fim->prox = n;
	l->fim = n;
	return 0;
}

/**
 * @
 */ 
int pushFrontNodeLista(Lista *l, No *n){
	if(n == NULL) return 1;
	
	n->prox = l->ini;
	l->ini  = n;
	if(l->fim == NULL) l->fim = n;
	return 0;
}

/**
 * @
 */ 
int popBackLista(Lista *l){
	return 1;
}

/**
 * @
 */ 
int popFrontLista(Lista *l){
	if(estaVaziaLista(l)) return 1;

	No* aux = l->ini;

	l->ini = l->ini->prox;
	l->fim = (l->ini == NULL) ? NULL : l->fim;

	free(aux);

	return 0;
}

/**
 * @
 */ 
No* popFrontNodeLista(Lista *l){
	No* aux = l->ini;
	l->ini  = l->ini->prox;
	if(l->ini == NULL) l->fim = NULL;
	return aux;
}

/**
 * @
 */ 
No* popBackNodeLista(Lista *l){
	return l->fim;
}

/**
 * @
 */ 
void _bucketSort(Lista *l, int min, int max, int (*getIndice)(elemLista*)){
	// Preparando o bucket para receber os elementos
	int   range = max-min+1, indice;
	Lista bucket[range];
	No    *aux;	

	// Preparando as listas do bucket
	for(int i = 0; i < range; i++){
		criarLista(&(bucket[i]));
	}

	// Removendo os Itens da Lista e inserindo no bucket
	while(!estaVaziaLista(l)){
		aux    = popFrontNodeLista(l);
		indice = getIndice(&(aux->info));
		pushBackNodeLista(&(bucket[indice]), aux);
	}

	// Removendo os itens do Bucket e inserindo novamente na lista
	for(int i = 0; i < range; i++){
		while(!estaVaziaLista(&(bucket[i]))){
			aux = popFrontNodeLista(&(bucket[i]));
			pushBackNodeLista(l, aux);
		}
	}

	// Obs. Não é preciso dar malloc nos buckets, pois houve apenas movimentação
	//      de nós pertencentes à lista L.
}
