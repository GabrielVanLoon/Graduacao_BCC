#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

/**
 * Funções básicas para manipulação de um grafo 'g'
 */
    grafo* criar_grafo(int n, int* erro){
        grafo* g;

        if(n > GRAFO_MAXSIZE || (g = malloc(sizeof(grafo))) == NULL){
            *erro = 1;
            return NULL;
        }

        for(int i = 0; i < n; i++)
            for(int j = i; j < n; j++)
                g->adj[i][j] = g->adj[j][i] = ARESTA_VAZIA;
        g->numVertices = n;

        *erro = 0;
        return g;
    }

    void destruir_grafo(grafo *g, int* erro){
        if(g != NULL) free(g);
        g == NULL;
        *erro = 0;
    }

    void inserir_aresta(grafo *g, int v1, int v2, aresta p, int* erro){
        if(g == NULL || v1 > g->numVertices || v2 > g->numVertices){
            *erro = 1;
            return;
        }

        #ifdef GRAFO_DIRECIONADO
            g->adj[v1][v2] = p;
        #else
            g->adj[v1][v2] = g->adj[v2][v1] = p; 
        #endif

        *erro = 0;
        return;
    }

    void remover_aresta(grafo *g, int v1, int v2, int* erro){
        if(g == NULL || v1 > g->numVertices || v2 > g->numVertices){
            *erro = 1;
            return;
        }

        #ifdef GRAFO_DIRECIONADO
            g->adj[v1][v2] = ARESTA_VAZIA;
        #else
            g->adj[v1][v2] = g->adj[v2][v1] = ARESTA_VAZIA; 
        #endif

        *erro = 0;
        return;
    }

    void exibir_matrizAdj(grafo *g){
        if(g == NULL){
            printf("Grafo não iniciado.\n");
            return;
        }

        for(int i = 0; i < g->numVertices; i++){
            for(int j = 0; j < g->numVertices; j++){
                if(g->adj[i][j] == ARESTA_VAZIA) printf(".\t");
                else printf("%d\t", g->adj[i][j]);
            }
            printf("\n");
        }
    }

/**
 * Geradores de grafos associados
 */
    grafo* criar_transposta(grafo* g, int* erro){
        if(g == NULL){
            *erro = 1;
            return NULL;
        }
        
        grafo *t = criar_grafo(g->numVertices, erro);

        for(int i = 0; i < g->numVertices; i++)
            for(int j = 0; j < g->numVertices; j++)
                t->adj[j][i] = g->adj[i][j];

        return t;
    }

    grafo* criar_complementar(grafo* g, int p, int* erro){
        if(g == NULL){
            *erro = 1;
            return NULL;
        }
        
        grafo *cpl = criar_grafo( g->numVertices, erro);

        for(int i = 0; i < g->numVertices; i++)
            for(int j = 0; j < g->numVertices; j++)
                if(g->adj[i][j] == ARESTA_VAZIA)
                    cpl->adj[i][j] = p;

        return cpl;
    }