#include <stdlib.h>
#include <stdio.h>
#include "arvore_bb.h"

void _destroiNosArvoresBB(NoArvoreBB *no);
void _printPosOrdem(NoArvoreBB *no);
void _printPreOrdem(NoArvoreBB *no);
void _printInOrdem(NoArvoreBB *no);

/**
 * @void criarArvoreBB();
 */
void criarArvoreBB(ArvoreBB *abb){
	abb->raiz = NULL;
}

/**
 * @void destruirArvoreBB();
 */
void destruirArvoreBB(ArvoreBB *abb){
	_destroiNosArvoresBB(abb->raiz);
}

/**
 * @int abb_inserirElemento(ArvoreBB *abb, Elem e);
 */
int abb_inserirElemento(ArvoreBB *abb, Elem e){

	NoArvoreBB **pai   = &(abb->raiz);
	NoArvoreBB  *atual =   abb->raiz;

	// Percorrendo a arvore de forma iterativa
	while(atual != NULL && atual->info != e){
		pai   = (atual->info > e) ? &(atual->left) : &(atual->right); 
		atual = (atual->info > e) ?   atual->left  :   atual->right; 
	}

	// Erro, o elemento já foi insido na árvore
	if(atual != NULL){
		return 1;
	}

	// Criando o novo nó
	atual = malloc(sizeof(ArvoreBB));
	atual->info = e;
	atual->left = atual->right = NULL;

	// Ajustando o ponteiro do pai para o filho
	*pai = atual;

    abb->size += 1;

	return 0;
}

/**
 * @int abb_removerElemento(ArvoreBB *abb, Elem e);
 */
int abb_removerElemento(ArvoreBB *abb, Elem e){

	NoArvoreBB **pai    = &(abb->raiz);
	NoArvoreBB  *atual  =   abb->raiz;
	NoArvoreBB  *aux    = NULL;
	NoArvoreBB  *paiAux = NULL;

	// Percorrendo a arvore de forma iterativa ate encontrar o elemento
	while(atual != NULL && atual->info != e){
		pai   = (atual->info > e) ? &(atual->left) : &(atual->right); 
		atual = (atual->info > e) ?   atual->left  :   atual->right; 
	}

	// Erro, não encontrou o elemento
	if(atual == NULL)
		return 1;

	// Se o nó achado for uma folha, basta removê-lo e ajustar o pai
	if(atual->left == NULL && atual->right == NULL){
		free(atual);
		*pai = NULL;
		return 0;
	}

	// Se ele tiver apenas um dos filhos, entao o filho assume o lugar
	if(atual->left == NULL && atual->right != NULL){
		*pai = atual->right;
		free(atual);

		abb->size -= 1;
		return 0;
	} else if(atual->left != NULL && atual->right == NULL){
		*pai = atual->left;
		free(atual);

		abb->size -= 1;
		return 0;
	}

	// No caso de ter os dois filhos, ele vai olhar para o menor deles (left)
	// Se aux não tiver filhos no right, aux se torna o nó removido.
	// Se aux tiver filhos no right, o filho mais à direita se torna o removido.
	/* 
	aux = atual->left;

	if(aux->right == NULL){
		aux->right = atual->right;
		*pai = aux;
		free(atual);
	
	} else {		
		while(aux->right != NULL){
			paiAux = aux;
			aux = aux->right;	
		} 

		atual->info = aux->info;

		paiAux->right = (aux->left == NULL) ? NULL : aux->left;
		free(aux);
	}*/

	aux = atual->right;

	if(aux->left == NULL){
		aux->left = atual->left;
		*pai = aux;
		free(atual);
	
	} else {		
		while(aux->left != NULL){
			paiAux = aux;
			aux = aux->left;	
		} 

		atual->info = aux->info;

		paiAux->left = (aux->right == NULL) ? NULL : aux->right;
		free(aux);
	}

	abb->size -= 1;
	return 0;
}

/**
 * @int abb_buscarElemento(ArvoreBB *abb, Elem e);
 */
int abb_buscarElemento(ArvoreBB *abb, Elem e){
	NoArvoreBB  *atual =   abb->raiz;

	// Percorrendo a arvore de forma iterativa
	while(atual != NULL && atual->info != e){
		atual = (atual->info > e) ?   atual->left  :   atual->right; 
	}

	// O elemento foi encontrado >> Retorna 1
	if(atual == NULL)
		return 0;
	else
		return 1;
}

/**
 * @int abb_printInOrdem(ArvoreBB *abb);
 */
int abb_printInOrdem(ArvoreBB *abb){
	// printf("InOrdem: ");
	_printInOrdem(abb->raiz);
	// printf("\n");
}

/**
 * @int abb_printPreOrdem(ArvoreBB *abb);
 */
int abb_printPreOrdem(ArvoreBB *abb){
	printf("PreOrdem: ");
	_printPreOrdem(abb->raiz);
	printf("\n");
}

/**
 * @int abb_printPosOrdem(ArvoreBB *abb);
 */
int abb_printPosOrdem(ArvoreBB *abb){
	printf("PosOrdem: ");
	_printPosOrdem(abb->raiz);
	printf("\n");
}

/**
 * @int abb_printLargura(ArvoreBB *abb);
 */
int abb_printLargura(ArvoreBB *abb){
	Lista l;
	NoArvoreBB* aux;

	printf("Largura: ");
	
	criarLista(&l);

	// Print em largura
	pushBackLista(&l, (void*) abb->raiz);

	while(!estaVaziaLista(&l)){

		aux = (NoArvoreBB*) frontLista(&l);
		popFrontLista(&l);

		if(aux->left != NULL)
			pushBackLista(&l, (void*) aux->left);

		if(aux->right != NULL)
			pushBackLista(&l, (void*) aux->right);

		printf("%d ", aux->info);
	}	
	printf("\n");

	removerLista(&l);
	return 0;
}

// Auxiliares.
	void _destroiNosArvoresBB(NoArvoreBB *no){
		if(no == NULL) return;
		
		_destroiNosArvoresBB(no->left);
		_destroiNosArvoresBB(no->right);
		free(no);
	}

	// esquerda >> raiz >> direita
	void _printInOrdem(NoArvoreBB *no){
		if(no == NULL) return;

		_printInOrdem(no->left);
		printf("%d ", no->info);
		_printInOrdem(no->right);
	}

	// Raiz >> esquerda >> direita
	void _printPreOrdem(NoArvoreBB *no){
		if(no == NULL) return;

		printf("%d ", no->info);
		_printPreOrdem(no->left);
		_printPreOrdem(no->right);
	}

	// esquerda >> direita >> raiz
	void _printPosOrdem(NoArvoreBB *no){
		if(no == NULL) return;

		_printPosOrdem(no->left);
		_printPosOrdem(no->right);
		printf("%d ", no->info);
	}