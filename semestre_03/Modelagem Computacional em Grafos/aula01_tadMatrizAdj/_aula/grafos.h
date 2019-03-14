#ifndef GRAFO_H
	
	#include <stdlib.h>
	
	#define GRAFO_H
	#define MAXNUMVERTICES 100
	#define SEMARESTA 0
	#define ARESTA 1
	#define VAZIO -1

	typedef int elem;
	typedef struct _grafo grafo;


	grafo* criar_grafo(int *n, int* erro);
	void finaizar_grafo(grafo* g, int* erro);

	/*
		a e b são os vertices.
	*/
	void inserir_aresta(grafo* g,int* a, int* b, elem* p, int* erro);
	elem remover_aresta(grafo* g,int* a, int* b, int* erro);
	void exibir_transposta(grafo* g, int* a, int* b, int* erro);
	int listaAdjVazia(grafo *g, int *v, int *erro);
	int PrimeiraListaAdj(grafo *g, int *v, int *erro);
	void ProxAdj(grafo *g, int *v, int *adj, elem *p, int *prox, int *fimListaAdj, int *erro);


#endif 