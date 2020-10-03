#ifndef LISTA_H
	#define LISTA_H
	
	typedef void* elemLista;

	typedef struct _no{
		elemLista  info;
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
	elemLista frontLista(Lista *l);

	/**
	 * @
	 */ 
	elemLista backLista(Lista *l);

	/**
	 * @
	 */ 
	int pushBackLista(Lista *l, elemLista e);

	/**
	 * @
	 */ 
	int pushFrontLista(Lista *l, elemLista e);

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

#endif