#include <stdlib.h>
#include <stdio.h>
#include "fabrica.h"

/**
 * @typedef Esteira de Brinquedos- Lista Circular
 */
	// Cria uma nova ListaCirc Circular vazia
	ListaCirc criar_lista(){
		ListaCirc l;
		l.ini  =  NULL;
		l.fim  =  NULL;
		return l;
	}

	// Remove as configurações de uma variável do tipo ListaCirc
	void remover_lista(ListaCirc *l){
		if(esta_vazia_lista(l)) return;
		
		NoL *stopCase = l->ini;
		do { 
			free(l->ini);
			l->ini = l->ini->prox;
		
		} while(l->ini != stopCase);
	}

	// Insere um brinquedo no final da lista.
	int inserir_na_lista(ListaCirc *l, Brinquedo b){
		if(esta_cheia_lista(l)) return 1;

		// Criando um novo Nó de Lista
		NoL* temp = (NoL*) malloc(sizeof(NoL)); 

		if(esta_vazia_lista(l)){
			l->ini = temp;
			l->fim = temp;
		} else {
			l->fim->prox = temp;
			l->fim       = temp;
		}

		// Inserindo as infomacoes do Nó
		temp->info = b;
		temp->prox = l->ini;

		return 0;
	}

	// Remove e retorna o brinquedo na posição i da lista
	// Obs.: posicao One Based {1, 2 ...... Size}
	int remover_da_lista(ListaCirc *l, int i, Brinquedo *b){
		if(esta_vazia_lista(l)) return 1;

		NoL *aux    = l->ini;
		NoL *antAux = l->fim;
		i--;

		// Acessando o Nó que pretende remover
		while(i > 0){
			antAux = aux;
			aux = aux->prox;
  			i--;
  			// A posicao enviada eh maior do que a lista
  			if(aux == l->fim && i > 0)
  				return 1;
		}

		// Retornando o valor do Nó
		*b = aux->info;

		// Caso seja o último Nó restante da lista
		if(l->ini == l->fim){
			l->ini = NULL;
			l->fim = NULL;
		
		// O Nó é de início
		} else if(l->ini == aux){
			l->ini       = aux->prox;
			l->fim->prox = aux->prox;
		
		// O Nó é o final
		} else if(l->fim == aux){
			l->fim       = antAux;
			antAux->prox = l->ini;

		} else {
			antAux->prox = aux->prox;
		}

		free(aux);

		return 0;
	}

	// Retorna “true” se a lista estiver vazia; “false”, caso contrário;
	int esta_vazia_lista(ListaCirc *l){
		return (l->ini == NULL) ? TRUE : FALSE;
	}

	// Retorna “true” se a lista estiver cheia; “false”, caso contrário;
	int esta_cheia_lista(ListaCirc *l){
		return FALSE;
	}

	void print_lista(ListaCirc *l){
		if(esta_vazia_lista(l)) return;

		NoL *aux = l->ini;
		int pos = 0;
		do{
			printf("%d:<%s,%d> ", pos++, aux->info.nome, aux->info.numSerie);
			aux = aux->prox;
		
		} while (aux != l->ini);

		printf("\n");
	}

/** 
 * @typedef Caixa de Brinquedos - Pilha
 */
	// Cria uma pilha vazia
	Pilha criar_pilha(int c){
		Pilha p;
		p.size = 0;
		p.max_size = c;
		p.ini = NULL;
		return p;
	}

	// Limpa uma variável do tipo Pilha
	void remover_pilha(Pilha *p){
		while(p->ini != NULL){
			free(p->ini);
			p->ini = p->ini->prox;
		}
		p->size = 0;
	}

	// Insere  um  brinquedo  na  pilha/caixa segundo a  ordenação
	// LIFO,  em que o último a entrar é o primeiro a sair;
	int push(Pilha *p, Brinquedo b){
		if(esta_cheia_pilha(p)) return 1;
		
		// Criando e Preparando o novo Nó
		NoP *aux = (NoP*) malloc(sizeof(NoP));
		aux->info = b;
		aux->prox = p->ini;

		// Inserindo na pilha
		p->ini = aux;
		p->size += 1;

		return 0;
	}

	// Retorna o brinquedo no topo da pilha/caixa, sem removê-lo
	Brinquedo top(Pilha *p){
		return p->ini->info;
	}

	// Remove o brinquedo no topo da pilha/caixa
	void pop(Pilha *p){
		if(!esta_vazia_pilha(p)){
			free(p->ini);
			p->ini = p->ini->prox;
			p->size -= 1;
		}
	}

	// Retorna “true” se a pilha estiver vazia; “false”, caso contrário;
	int esta_vazia_pilha(Pilha *p){
		return (p->ini == NULL) ? TRUE : FALSE;
	}

	// Retorna “true” se a pilha estiver cheia; “false”, caso contrário;
	int esta_cheia_pilha(Pilha *p){
		return (p->size == p->max_size) ? TRUE : FALSE;
	}

	// Realiza um print do conteudo da pilha começando do topo:
	void print_pilha(Pilha *p){
		NoP *aux = p->ini;

		while(aux != NULL){
			printf("<%s, %d>\n", aux->info.nome, aux->info.numSerie);
			aux = aux->prox;
		}	
		printf("\n");
	}

/**
 * @typedef Fila de Caixas - Fila Circular
 */
	// Cria uma nova Fila Circular vazia
	Fila criar_fila(){
		Fila f;
		f.ini  = NULL;
		f.fim  = NULL;
		return f;
	}

	// Remove as configurações de uma variável do tipo ListaCirc
	void remover_fila(Fila *f){
		if(f->ini != NULL){
			free(f->ini);
			f->ini = f->ini->prox;
		}
		f->ini  = NULL;
		f->fim  = NULL;
	}

	// Insere uma caixa/pilha no final da fila;
	int inserir_na_fila(Fila *f, Pilha p){
		if(esta_cheia_fila(f)) return 1;

		// Criando um novo Nó
		NoF *temp = (NoF*) malloc(sizeof(NoF));
		temp->info = p;
		temp->prox = NULL;

		if(esta_vazia_fila(f)){
			f->ini = temp;
		} else {
			f->fim->prox = temp;
		}

		f->fim = temp;

		return 0;
	}

	// Remove e retorna a Caixa/Pilha no inicio da fila
	int remover_da_fila(Fila *f, Pilha *p){
		if(esta_vazia_fila(f)) return 1;

		NoF *aux = f->ini;

		// Retornando o brinquedo
		*p = aux->info;

		// Ajustando o inicio
		f->ini = aux->prox;

		// Liberando o Nó
		free(aux);

		return 0;
	}

	// Retorna “true” se a fila estiver vazia; “false”, caso contrário;
	int esta_vazia_fila(Fila *f){
		return (f->ini == NULL) ? TRUE : FALSE;
	}

	// Retorna “true” se a fila estiver cheia; “false”, caso contrário;
	int esta_cheia_fila(Fila *f){
		return FALSE;
	}