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
        if(g == NULL || v1 >= g->numVertices || v2 >= g->numVertices){
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
        if(g == NULL || v1 >= g->numVertices || v2 >= g->numVertices){
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
        
        grafo *cpl = criar_grafo(g->numVertices, erro);

        for(int i = 0; i < g->numVertices; i++)
            for(int j = 0; j < g->numVertices; j++)
                if(g->adj[i][j] == ARESTA_VAZIA)
                    cpl->adj[i][j] = p;

        return cpl;
    }

/**
 * Algoritmos de Conectividade
 */ 
    void dfs(grafo* g, cor* vis, int v){
        
        printf("Grafo v: %d\n", v);
        // Marcando vertice atual como visitado.
        vis[v] = cinza;

        // Percorrendo os vertices vizinhos nao visitados.
        for(int i = 1; i < g->numVertices; i++){
            if(g->adj[v][i] != ARESTA_VAZIA && vis[i] == branco)
                dfs(g, vis, i);
        }

        // Marcando como totalmente visitado
        vis[v] = preto;
        return;
    }

    int existe_caminho(grafo* g, int origem, int destino, int *erro){
        if(g == NULL || origem >= g->numVertices || destino >= g->numVertices){
            *erro = 1;
            return 0;
        }

        /** A cor representa o status de cada vértice no decorrer do dfs.
         *  BRANCO: Não visitado
         *  CINZA:  Visitado com vizinhos não visitados
         *  PRETO:  Visitado sem vizinhos para visitar.
         */
        cor visitados[g->numVertices+1];

        for(int i = 0; i < g->numVertices; i++)
            visitados[i] = branco;

        dfs(g, visitados, origem);

        *erro = 0;
        return ((visitados[destino] == preto) ? 1 : 0);
    }

    int eh_fortemente_conectado(grafo *g, int vInicial, int *erro){
        if(g == NULL){
            *erro = 1;
            return 0;
        }

        cor visitadosG[g->numVertices+1];
        cor visitadosT[g->numVertices+1];
        grafo *t = criar_transposta(g, erro);

        // Preparando os vértices para as DFS's
        for(int i = 0; i < g->numVertices; i++)
            visitadosG[i] = visitadosT[i] = branco;
        
        // Fazendo o DFS no grafo principal
        dfs(g, visitadosG, vInicial);
        
        // Caso algum não tenha sido visitado, nao eh SCC
        for(int i = vInicial; i < g->numVertices; i++)
            if(visitadosG[i] != preto)
                return 0;
        
        // Fazendo o DFS no grafo transposto
        dfs(t, visitadosT, vInicial);

        // Caso algum não tenha sido visitado, nao eh SCC
        for(int i = vInicial; i < g->numVertices; i++)
            if(visitadosT[i] != preto)
                return 0;

        destruir_grafo(t, erro);

        return 1;
    }
