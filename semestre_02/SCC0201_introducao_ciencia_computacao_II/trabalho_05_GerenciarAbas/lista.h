#ifndef LISTA_H
	#define LISTA_H
	
	typedef struct {
		int dia;
		int mes;
	}Data;

	typedef struct {
		int hora;   // {0..23}
		int minuto; // {0..60}
	}Hora;

	typedef struct _aba{
		char  titulo[32];
		char  url[1026];
		Data  dt;
		Hora  hr;
	}Aba;

	typedef Aba elem;

	typedef struct _no{
		elem        info;
		struct _no *prox;
	}No;

	typedef struct _lista{
		struct _no *ini, *fim;
	}Lista;

	/**
	 * @
	 */ 
	void criarLista(Lista *l);

	/**
	 * @
	 */ 
	void removerLista(Lista *l);

	/**
	 * @
	 */ 
	int estaVaziaLista(Lista *l);

	/**
	 * @
	 */ 
	int printLista(Lista *l);

	/**
	 * @
	 */ 
	elem frontLista(Lista *l);

	/**
	 * @
	 */ 
	elem backLista(Lista *l);

	/**
	 * @
	 */ 
	int pushBackLista(Lista *l, elem e);

	/**
	 * @
	 */ 
	int pushFrontLista(Lista *l, elem e);

	/**
	 * @
	 */ 
	int pushBackNodeLista(Lista *l, No *n);

	/**
	 * @
	 */ 
	int pushFrontNodeLista(Lista *l, No *n);

	/**
	 * @
	 */ 
	int popBackLista(Lista *l);

	/**
	 * @
	 */ 
	int popFrontLista(Lista *l);

	/**
	 * @
	 */ 
	No* popFrontNodeLista(Lista *l);

	/**
	 * @
	 */ 
	No* popBackNodeLista(Lista *l);

	/**
	 * @
	 */ 
	int reposicionarElemento(Lista *l, char *titulo, int novaPos);


	/**
	 * @
	 */ 
	int ordenarLista(Lista *l);

#endif