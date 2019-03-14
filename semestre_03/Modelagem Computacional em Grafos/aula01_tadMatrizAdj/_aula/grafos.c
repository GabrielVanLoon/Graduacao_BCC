#include "grafos.h"

struct _grafo{
	elem m[MAXNUMVERTICES][MAXNUMVERTICES];
	int numVertices;
};

grafo* criar_grafo(int *n, int* erro){
	if(*n > MAXNUMVERTICES) {
		*erro = 1;
		return NULL;
	}

	grafo* g =  (grafo*) malloc(sizeof(grafo));
	if(g == NULL) {
		*erro = 1;
		return g;
	}

	for(int i = 0; i < *n; ++i)
		for(int j = i; j < *n; ++j)
			g->m[i][j] = g->m[j][i] = VAZIO;

	g->numVertices = *n;
	*erro = 0;
	return g;
}

void finaizar_grafo(grafo* g, int* erro) {
	if(g == NULL) return NULL;
	free(g);
	g = NULL;
	*erro = 0;
}

void inserir_aresta(grafo* g,int* a, int* b, elem* p, int* erro){
	if( *a >= g->numVertices || b* >= g->numVertices){
		*erro = 1;
		return;
	}

	g->m[*a][*b] = *p;
	*erro = 0;
}

elem remover_aresta(grafo* g,int* a, int* b, int* erro) {
	if( *a >= g->numVertices || b* >= g->numVertices || g->m[*a][*b] == VAZIO){
		*erro = 1;
		return 0;
	}

	elem p = g->m[*a][*b];
	g->m[*a][*b] = VAZIO;
	*erro = 0;
	return p;
}

void exibir_transposta(grafo* g, int* erro) {
	int u = g->numVertices;
	for(int i = 0; i < u; ++i){
		for(int j = 0; j < u; ++j)
			printf("%d\t",g->m[j][i]);
		printf("\n");
	}
}

int listaAdjVazia(grafo *g, int *v, int *erro){
	if(*v >= g->numVertices){
		*erro=1;
		return 1;
	}
	else{
		*erro=0;
		int aux=0, lista_vazia=1;
		while((aux < g->numVertices) && (lista_vazia)){
			if(g->m[*v][aux] != VAZIO)
				lista_vazia = 0;
			else
				aux++;
		}
		return(lista_vazia);
	}
}

int PrimeiraListaAdj(grafo *g, int *v, int *erro){
	if(*v >= g->numVertices)
		*erro=1;
	else{
		*erro=0;
		int aux=0;
		while(aux < g->numVertices){
			if(g->m[*v][aux] != VAZIO)
				return(aux);
			else
				aux++;
		}
	}
	return (-1);
}

void ProxAdj(grafo *g, int *v, int *adj, elem *p, int *prox, int *fimListaAdj, int *erro){
	if(*v > g->numVertices)
		*erro=1;
	else{
		*erro=0;
		*adj = *prox;
		*p = g->m[*v][*prox];
		(*prox)++;
		while((*prox < g->numVertices) && (g->m[*v][*prox] == VAZIO))
			(*prox)++;
		if(*prox > g->numVertices)
			*fimListaAdj=1;
	}

}

void menorAresta(grafo *g, int* v, int *a, int *b, int *erro){
	elem min = -1;
	for(int i = 0; i < g->numVertices; i++){
		for(int j = 0; j < g->numVertices; i++){
			if(g->m[i][j] == VAZIO) continue;
			if(min == -1 || g->m[i][j] < min){
				min = g->m[i][j];
				*a = i;
				*b - j;
			} 
		}
	}


}





