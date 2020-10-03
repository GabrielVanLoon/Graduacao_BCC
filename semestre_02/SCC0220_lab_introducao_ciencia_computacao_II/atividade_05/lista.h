#ifndef LISTA_H
	#define LISTA_H
	
	typedef enum _faculdade{
		CAASO, FEDERAL
	}Faculdade;

	typedef struct _elemento{
		int id;
		char nome[60];
		Faculdade facul;
	}Elemento; 

	typedef struct _lista{
		int size;
		Elemento* vet;
	}Lista;

	Lista novaLista();

	void liberarLista(Lista *l);

	void inserirElemento(Lista *l, Elemento e);

	void ordenarPeloNome(Lista *l, int max);

	void ordernarPeloID(Lista *l, int max);

	void printLista(Lista *l);
	
#endif