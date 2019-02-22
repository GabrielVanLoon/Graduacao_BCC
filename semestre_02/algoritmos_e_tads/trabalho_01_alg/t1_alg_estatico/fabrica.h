#ifndef FABRICA_H
	#define FABRICA_H
	
	#define MAX_SIZE 1000
	#define TRUE  1
	#define FALSE 0

	typedef struct _brinquedo{
		int numSerie;
		char nome[20];
	}Brinquedo;

	/**
	 * @typedef Esteira de Brinquedos- Lista Circular
	 */
		typedef struct _listaCirc{
			Brinquedo *vet;
			int ini, fim, size;
		}ListaCirc;

		// Cria uma nova ListaCirc Circular vazia
		ListaCirc criar_lista();

		// Remove as configurações de uma variável do tipo ListaCirc
		void remover_lista(ListaCirc *l);

		// Insere um brinquedo no final da lista;
		int inserir_na_lista(ListaCirc *e, Brinquedo b);

		// Remove e retorna o brinquedo na posição i da lista
		int remover_da_lista(ListaCirc *l, int i, Brinquedo *b);

		// Retorna “true” se a lista estiver vazia; “false”, caso contrário;
		int esta_vazia_lista(ListaCirc *l);

		// Retorna “true” se a lista estiver cheia; “false”, caso contrário;
		int esta_cheia_lista(ListaCirc *l);

		// Realiza um print da lista no formato abaixo:
		// "indexNaLista:<nome, numSerie> "
		void print_lista(ListaCirc *l);

	/**
	 * @typedef Caixa de Brinquedos - Pilha
	 */
		typedef struct _pilha {
			Brinquedo *vet;
			int topo, max_size;
		} Pilha;

		// Cria uma pilha vazia de tamanho maximo C
		Pilha criar_pilha(int c);

		// Limpa uma variável do tipo Pilha
		void remover_pilha(Pilha *p);

		// Insere  um  brinquedo  na  pilha/caixa segundo a  ordenação
		// LIFO,  em que o último a entrar é o primeiro a sair;
		int push(Pilha *p, Brinquedo b);

		// Retorna o brinquedo no topo da pilha/caixa, sem removê-lo
		Brinquedo top(Pilha *p);

		// Remove o brinquedo no topo da pilha/caixa
		void pop(Pilha *p);

		// Retorna “true” se a pilha estiver vazia; “false”, caso contrário;
		int esta_vazia_pilha(Pilha *p);

		// Retorna “true” se a pilha estiver cheia; “false”, caso contrário;
		int esta_cheia_pilha(Pilha *p);

		// Realiza um print do conteudo da pilha começando do topo:
		void print_pilha(Pilha *p);

	/**
	 * @typedef Fila de Caixas - Fila Circular
	 */
		typedef struct _fila{
			Pilha *vet;
			int ini, fim, size;
		} Fila;

		// Cria uma nova Fila Circular vazia
		Fila criar_fila();

		// Remove as configurações de uma variável do tipo ListaCirc
		void remover_fila(Fila *l);

		// Insere uma caixa/pilha no final da fila;
		int inserir_na_fila(Fila *e, Pilha p);

		// Remove e retorna a Caixa/Pilha no inicio da fila
		int remover_da_fila(Fila *l, Pilha *p);

		// Retorna “true” se a fila estiver vazia; “false”, caso contrário;
		int esta_vazia_fila(Fila *l);

		// Retorna “true” se a fila estiver cheia; “false”, caso contrário;
		int esta_cheia_fila(Fila *l);

#endif