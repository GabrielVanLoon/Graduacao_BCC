#include "lista_encad.h"
#include <stdlib.h>
#include <stdio.h>

void novaListaEncadeada(ListaEnc *l){
	l->ini = NULL;
}

void removerListaEncadeada(ListaEnc *l){
	if(l->ini == NULL) return;
	No* temp;
	
	while(l->ini != NULL){
		temp = l->ini->prox;
		l->ini = l->ini->prox;
		free(temp);
	}
}

void inserirElemento(ListaEnc *l, int chave, int back, int tempo){

	// Caso seja o primeiro item da lista
	if(l->ini == NULL){
		l->ini = (No*) malloc(sizeof(No));
		
		l->ini->chave = chave;
		l->ini->tempo = tempo;
		l->ini->prox  = NULL;
		l->ini->back  = NULL;
	
	} else {  
		No* temp = l->ini;

		// Auxiliares para guardar o ponteiro para o back
		int delay = back-1;
		No* anterior = l->ini;
		
		// Navegando para o ultimo no disponivel
		while(temp->prox != NULL) {
			temp = temp->prox;

			// Avançando o "Back" com delay de posições
			if(delay > 0)
				delay--;
			else
				anterior = anterior->prox;
		}

		temp->prox = (No*) malloc(sizeof(No));
		
		temp->prox->chave = chave;
		temp->prox->tempo = tempo;
		temp->prox->prox  =  NULL;

		if(back  > 0 && delay == 0){
			temp->prox->back  =  anterior;
		} else {
			temp->prox->back  =  NULL;
		}

	}
}

void removerElemento(ListaEnc *l, int chave){
	if(l->ini == NULL) 
		return;
	
	No* atual    = l->ini;
	No* anterior = NULL;
	
	// Navegando até o Nó desejado
	while(atual->prox != NULL && atual->chave != chave){
		anterior = atual;
		atual = atual->prox;
	}
	
	// Caso o Nó com a chave mencionada não exista
	if(atual->prox == NULL && atual->chave != chave)
		return;
		
	// Apaga o no atual e linka o anterior com o prox
	if(anterior == NULL)
		l->ini =  atual->prox;
	else
		anterior->prox = atual->prox;
	
	free(atual);
	
	// Navega o resto da lista apagando os que referencianvam o atual
	No* aux = (anterior == NULL) ? l->ini : anterior->prox;
	while(aux != NULL){
		if(aux->back == atual)
			aux->back = NULL;
		aux = aux->prox;
	}
	
}

void printarListaEncadeada(ListaEnc *l){
	
	if(l->ini == NULL){	
		printf("-1\n");
		return;
	}
	
	No* atual = l->ini;
	int pos = 0;
	
	while(atual != NULL){
		
		// Atualizando a posicao enquanto percorre o print
		atual->pos = pos++; 
		
		if(atual->back != NULL)
			printf("[%d,%d,%d] ", atual->chave, atual->tempo, atual->back->pos);
		else
			printf("[%d,%d] ", atual->chave, atual->tempo);
		
		atual = atual->prox;
	}
	printf("\n");
}


























