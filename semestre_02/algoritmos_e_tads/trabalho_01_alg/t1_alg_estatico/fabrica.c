#include <stdlib.h>
#include <stdio.h>
#include "fabrica.h"

/**
 * @typedef Esteira de Brinquedos- Lista Circular
 */
	// Cria uma nova ListaCirc Circular vazia
	ListaCirc criar_lista(){
		ListaCirc l;
		l.vet = (Brinquedo*) malloc(MAX_SIZE*sizeof(Brinquedo));
		l.ini  =  0;
		l.fim  = -1;
		l.size =  0;
		return l;
	}

	// Remove as configurações de uma variável do tipo ListaCirc
	void remover_lista(ListaCirc *l){
		if(l->vet != NULL) free(l->vet);
		l->ini  =  0;
		l->fim  = -1;
		l->size =  0;
	}

	// Insere um brinquedo no final da lista;
	int inserir_na_lista(ListaCirc *l, Brinquedo b){
		if(esta_cheia_lista(l)) return 1;

		l->fim = ((l->fim+1) < MAX_SIZE) ? l->fim+1 : 0;
		l->vet[l->fim] = b;
		l->size += 1;

		return 0;
	}

	// Remove e retorna o brinquedo na posição i da lista
	// Obs.: posicao One Based {1, 2 ...... Size}
	int remover_da_lista(ListaCirc *l, int i, Brinquedo *b){
		
		if(i > l->size) return 1; // A posicao nao existe na lista

		// Ajustando o index
		if((i = i-1+l->ini) >= MAX_SIZE)
			i = i-MAX_SIZE;

		// Retornando o brinquedo
		*b = l->vet[i];

		// Como a lista é sequencial, precisa shiftar o espaço vazio que ficou
		if (i == l->ini) 
			l->ini = ((l->ini+1) < MAX_SIZE ) ? l->ini+1 : 0;
		// Pior caso para implementações sequenciais  
		else { 
			if(i != l->fim){
				for(int j = i+1; j != l->fim; j++){
					
					if(j >= MAX_SIZE){
						j = 0;
						l->vet[MAX_SIZE-1] = l->vet[j];
					} else {
						l->vet[j] = l->vet[j];
					}
				}
				l->vet[l->fim-1] = l->vet[l->fim];
			}
			l->fim = ((l->fim-1) >= 0 ) ? l->fim-1 : MAX_SIZE-1; 
		}

		l->size -= 1;

		return 0;
	}

	// Retorna “true” se a lista estiver vazia; “false”, caso contrário;
	int esta_vazia_lista(ListaCirc *l){
		return (l->size == 0) ? TRUE : FALSE;
	}

	// Retorna “true” se a lista estiver cheia; “false”, caso contrário;
	int esta_cheia_lista(ListaCirc *l){
		return (l->size == MAX_SIZE) ? TRUE : FALSE;
	}

	void print_lista(ListaCirc *l){
		for(int i = 0; i < l->size; i++){
			int pos = i + l->ini;

			if(pos >= MAX_SIZE)
				pos = pos - MAX_SIZE;

			printf("%d:<%s,%d> ", pos, l->vet[pos].nome, l->vet[pos].numSerie);
		}
		printf("\n");
	}

/** 
 * @typedef Caixa de Brinquedos - Pilha
 */
	// Cria uma pilha vazia
	Pilha criar_pilha(int c){
		Pilha p;
		p.max_size = c;
		p.topo = -1;
		p.vet = (Brinquedo*) malloc(p.max_size*sizeof(Brinquedo));
		return p;
	}

	// Limpa uma variável do tipo Pilha
	void remover_pilha(Pilha *p){
		if(p->vet != NULL) free(p->vet);
		p->topo = -1;
	}

	// Insere  um  brinquedo  na  pilha/caixa segundo a  ordenação
	// LIFO,  em que o último a entrar é o primeiro a sair;
	int push(Pilha *p, Brinquedo b){
		if(esta_cheia_pilha(p)) return 1;
		p->topo++;
		p->vet[p->topo] = b;
		return 0;
	}

	// Retorna o brinquedo no topo da pilha/caixa, sem removê-lo
	Brinquedo top(Pilha *p){
		return p->vet[p->topo];
	}

	// Remove o brinquedo no topo da pilha/caixa
	void pop(Pilha *p){
		if(!esta_vazia_pilha(p)) 
			--p->topo;
	}

	// Retorna “true” se a pilha estiver vazia; “false”, caso contrário;
	int esta_vazia_pilha(Pilha *p){
		return (p->topo == -1) ? TRUE : FALSE;
	}

	// Retorna “true” se a pilha estiver cheia; “false”, caso contrário;
	int esta_cheia_pilha(Pilha *p){
		return (p->topo+1 == p->max_size) ? TRUE : FALSE;
	}

	// Realiza um print do conteudo da pilha começando do topo:
	void print_pilha(Pilha *p){
		for(int i = p->topo; i >= 0; i--)
			printf("<%s, %d>\n", p->vet[i].nome, p->vet[i].numSerie);
		printf("\n");
	}

/**
 * @typedef Fila de Caixas - Fila Circular
 */
	// Cria uma nova Fila Circular vazia
	Fila criar_fila(){
		Fila f;
		f.vet  = (Pilha*) malloc(MAX_SIZE*sizeof(Pilha)); 
		f.ini  =  0;
		f.fim  = -1;
		f.size =  0;
		return f;
	}

	// Remove as configurações de uma variável do tipo ListaCirc
	void remover_fila(Fila *f){
		if(f->vet != NULL) free(f->vet);
		f->ini  =  0;
		f->fim  = -1;
		f->size =  0;
	}

	// Insere uma caixa/pilha no final da fila;
	int inserir_na_fila(Fila *f, Pilha p){
		if(esta_cheia_fila(f)) return 1;

		f->fim = ((f->fim+1) < MAX_SIZE) ? f->fim+1 : 0;
		f->vet[f->fim] = p;
		f->size += 1;

		return 0;
	}

	// Remove e retorna a Caixa/Pilha no inicio da fila
	int remover_da_fila(Fila *f, Pilha *p){
		
		if(esta_vazia_fila(f)) return 1;

		// Retornando o brinquedo
		*p = f->vet[f->ini];

		// Ajustando o inicio
		f->ini = ((f->ini+1) < MAX_SIZE ) ? f->ini+1 : 0;

		f->size -= 1;

		return 0;
	}

	// Retorna “true” se a fila estiver vazia; “false”, caso contrário;
	int esta_vazia_fila(Fila *f){
		return (f->size == 0) ? TRUE : FALSE;
	}

	// Retorna “true” se a fila estiver cheia; “false”, caso contrário;
	int esta_cheia_fila(Fila *f){
		return (f->size == MAX_SIZE) ? TRUE : FALSE;
	}