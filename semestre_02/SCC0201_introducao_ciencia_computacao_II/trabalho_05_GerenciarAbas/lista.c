#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lista.h"

/**
 * @Protótipos da lista.c
 */ 
	void _bucketSort(Lista *l, int min, int max, int (*getIndice)(elem*));
	int getDia(elem *e);
	int getDia(elem *e);
	int getMes(elem *e);
	int getHora(elem *e);
	int getMinuto(elem *e);

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
int printLista(Lista *l){
	No *aux = l->ini;
	while(aux != NULL){
		printf("%s %s %02d/%02d %02d:%02d\n", aux->info.titulo, aux->info.url, aux->info.dt.dia, aux->info.dt.mes, aux->info.hr.hora, aux->info.hr.minuto);
		aux = aux->prox;
	}
	printf("\n");
}

/**
 * @
 */ 
elem frontLista(Lista *l){
	return l->ini->info; 
}

/**
 * @
 */ 
elem backLista(Lista *l){
	return l->fim->info;
}

/**
 * @
 */ 
int pushBackLista(Lista *l, elem e){
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
int pushFrontLista(Lista *l, elem e){
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
int reposicionarElemento(Lista *l, char *titulo, int novaPos){
	if(estaVaziaLista(l)) return 1;

	No *aux    = l->ini;
	No *auxAnt = NULL;
	int i   = 1; 

	// Percore até achar a posição desejeda ou o item que será movido
	while( aux != NULL && i < novaPos && strcmp(titulo, aux->info.titulo) != 0){
		auxAnt = aux;
		aux    = aux->prox;
		i++;
	}

	// O Nó já está na posicao que desejava ser movida
	if(i == novaPos && strcmp(titulo, aux->info.titulo) == 0){
		return 0;

	// Achou a posição, então o Nó precisa ser movido para trás.
	} else if(i == novaPos){
		No *target    = aux;
		No *targetAnt = auxAnt;

		while(target != NULL && strcmp(titulo, target->info.titulo) != 0){
			targetAnt = target;
			target    = target->prox;
		}

		// Caso não tenha achado o titulo pesquisado
		if(target == NULL) 
			return 1;
		
		// Removendo o Nó que queremos mover da lista
		if(targetAnt == NULL)    l->ini          = target->prox;
		else                     targetAnt->prox = target->prox;
		if(target->prox == NULL) l->fim = targetAnt;

		// Inserindo na posicao
		if(auxAnt == NULL) l->ini       = target;
		else               auxAnt->prox = target;
		if((target->prox = aux) == NULL) l->fim = target;

	// Achou o titulo, então o Nó será movido para frente da lista
	} else if(strcmp(titulo, aux->info.titulo) == 0){
		No* target = aux;
		No* targetAnt = auxAnt;

		// Navega até achar o Nó anterior à posição que queremos realocar
		while(target != NULL && i < (novaPos)){
			targetAnt = target;
			target = target->prox;
			i++;
		}

		// caso a posicao seja maior que o tamanho da lista, manda para o fim
		if(target == NULL && targetAnt != NULL){
			target = targetAnt;
			//return 1;
		}

		// Removendo o nó que queremos mover da lista
		if(auxAnt == NULL) l->ini       = aux->prox;
		else               auxAnt->prox = aux->prox;
		if(aux->prox == NULL) l->fim    = auxAnt;

		// Inserindo o nó na posicao
		aux->prox    = target->prox;
		target->prox = aux;
		if(aux->prox == NULL) l->fim = aux;
	}

	return 0;
}

/**
 * @
 */ 
int ordenarLista(Lista *l){
	_bucketSort(l, 0, 61, getMinuto);
	_bucketSort(l, 0, 24, getHora);
	_bucketSort(l, 0, 32, getDia);
	_bucketSort(l, 0, 13, getMes);
}

/**
 * @
 */ 
void _bucketSort(Lista *l, int min, int max, int (*getIndice)(elem*)){
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

/**
 * @
 */ 
int getDia(elem *e){    return e->dt.dia;    }
int getMes(elem *e){    return e->dt.mes;    }
int getHora(elem *e){   return e->hr.hora;   }
int getMinuto(elem *e){ return e->hr.minuto; }