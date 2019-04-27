#include <stdlib.h>
#include <stdio.h>
#include "grafoM.h"

/**
 * Funções para criar o grafo e suas arestas
 */
    int criar_grafo(Grafo* g, int qtdVertices){
        if(g == NULL || qtdVertices > MAXNUMVERTICES)
            return 1;

        for(int i = 0; i < qtdVertices; i++){
            g->vertices[i].label = NULL;
            for(int j = i; j < qtdVertices; j++){
                g->matriz[i][j].peso = ARESTA_VAZIA;
                g->matriz[j][i].peso = ARESTA_VAZIA;
            }
        }

        g->numVertices = qtdVertices;
        return 0;
    }

    int destruir_grafo(Grafo* g){
        if(g == NULL)
            return 1;

        // Caso haja vértices com rótulos, retira.
        for(int i = 0; i < g->numVertices; i++){
            if(g->vertices[i].label != NULL){
                free(g->vertices[i].label);
                g->vertices[i].label = NULL;
            }
        }

        return 0;
    }

    int inserir_aresta(Grafo* g, int vOrigem, int vDestino, int digrafo){
        if(g == NULL || vOrigem >= g->numVertices || vDestino >= g->numVertices || vOrigem < 0 || vDestino < 0 )
            return 1;

        g->matriz[vOrigem][vDestino].peso = ARESTA_COMUM;
        if(!digrafo)
            g->matriz[vDestino][vOrigem].peso = ARESTA_COMUM;

        return 0;
    }

    int inserir_arestaPonderada(Grafo* g, int vOrigem, int vDestino, int peso, int digrafo){
        if(g == NULL || vOrigem >= g->numVertices || vDestino >= g->numVertices || vOrigem < 0 || vDestino < 0 )
            return 1;

        g->matriz[vOrigem][vDestino].peso = peso;
        if(!digrafo)
             g->matriz[vDestino][vOrigem].peso = peso;

        return 0;
    }

    int remover_aresta(Grafo* g, int vOrigem, int vDestino, int digrafo){
        if(g == NULL || vOrigem >= g->numVertices || vDestino >= g->numVertices || vOrigem < 0 || vDestino < 0 )
            return 1;

        g->matriz[vOrigem][vDestino].peso = ARESTA_VAZIA;
        if(!digrafo)
            g->matriz[vDestino][vOrigem].peso = ARESTA_VAZIA;
        return 0;
    }

    int  calcularGrauVertice(Grafo* g, int v){
        if(g == NULL ||  v >= g->numVertices || v < 0 )
            return -1;

        int grau = 0;
        for(int i = 0; i < g->numVertices; i++)
            if(g->matriz[v][i].peso != ARESTA_VAZIA)
                grau += 1;

        return grau;
    }

    void exibirGrafo(Grafo* g){
        if(g == NULL)
            return;

        printf("Grafo G = {V,A}\n");
        printf("V = {0, ... ,%d}\n", g->numVertices-1);
        printf("A = {\n");
        for(int i = 0; i < g->numVertices; i++){
            printf("\t");
            for(int j = 0; j < g->numVertices; j++){
                if(g->matriz[i][j].peso != ARESTA_VAZIA)
                    printf("(%d,%d), ", i, j);
            }
            printf("\n");
        }
            
        printf("}\n\n");
    }
    
/**
 * Funções para iterar nos vizinhos de um vertice
 */
    int possuiVerticesAdjacentes(Grafo* g, int v){
        if(g == NULL || v >= g->numVertices || v < 0 )
            return 0;

        for(int i = 0; i < g->numVertices; i++)
            if(g->matriz[v][i].peso != ARESTA_VAZIA)
                return 1;

        return 0;

    }

    int primeroVerticeAdjacente(Grafo* g, int v){
        if(g == NULL ||  v >= g->numVertices || v < 0 )
            return -1;

        for(int i = 0; i < g->numVertices; i++)
            if(g->matriz[v][i].peso != ARESTA_VAZIA)
                return i;

        return -1;
    }

    int proximoVerticeAdjacente(Grafo *g, int v, int adjAtual){
        if(g == NULL ||  v >= g->numVertices || v < 0 )
            return -1;

        for(int i = (adjAtual+1); i < g->numVertices; i++)
            if(g->matriz[v][i].peso != ARESTA_VAZIA)
                return i;

        return -1;
    }