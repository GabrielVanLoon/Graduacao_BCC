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

    int grau_vertice(grafo* g, int v){
        int grau = 0;
        for(int i = 0; i < g->numVertices; i++)
            grau += (g->adj[v][i] == ARESTA_VAZIA) ? 0 : 1;
        return grau;

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
 * Algoritmos ligados à Caminho Euleriano
 * */
    int caminho[GRAFO_MAXSIZE*4];
    int euleriano_rec(grafo* g, int ini, int atual, int c);
    
    
    int possuiCicloEuleriano(grafo *g, int* erro){
        if(g == NULL){
            *erro = 1;
            return 0;
        }

        for(int i = 0; i < g->numVertices; i++){
            int grau = 0;
            for(int j = 0; j < g->numVertices; j++){
                if(i == j) continue;
                if(g->adj[i][j] == ARESTA_VAZIA) continue;
                grau++;
            }

            // Caso haja algum vertice de grau impar
            if(grau % 2 != 0) return 0; // Não ha caminho
        }

        return 1;
    }

    int percorrerCaminhoEuleriano(grafo* g, int *erro){
        if(g == NULL){
            *erro = 1;
            return 0;
        }

        if(!possuiCicloEuleriano(g, erro)){
            printf("Não é possivel haver um caminho euleriano no grafo!\n");
            return 0;
        }

        int tam = euleriano_rec(g, 0, 0, 0);
        if(!tam){
            printf("O algoritmo nao detectou um ciclo euleriano\n");
            return 0;
        }

        for(int i = 0; i < tam; i++)
            printf("%d -> ", caminho[i]);

        printf("%d\n", caminho[tam]);
        return 1;
    }

    // Retorno: 1 - Encontrou caminho, 0 - Não encontrou caminho
    int euleriano_rec(grafo* g, int ini, int atual, int c){

        // Fazendo o track da recursao
        printf("Posicao %d: Vertice: %d\n", c, atual);

        // Marcando no caminho que passou por aqui.
        caminho[c] = atual;
        int erro   = 0;

        // Caso de parada ideal: Chegou no fim do caminho
        if(ini == atual && grau_vertice(g, atual) == 0){
            // Verifica se todas as arestas ja foram percorridas
            for(int i = 0; i < g->numVertices; i++)
                if(grau_vertice(g, i) != 0) return 0; 


            return c;
        }

        // Percorrendo as ligada ao vertice atual
        for(int i = 0; i < g->numVertices; i++){
            if(i == atual)                       continue;
            if(g->adj[atual][i] == ARESTA_VAZIA) continue;

            remover_aresta(g, atual, i, &erro);
            
            // Verifica se não removeu uma ponte usando Kosaraju
            if(!eh_fortemente_conectado(g,ini, &erro) ){
                inserir_aresta(g, atual, i, 1, &erro);
                continue;    
            }

            int result = euleriano_rec(g, ini, i, c+1);
            if( result > 0 ) return result;

            inserir_aresta(g, atual, i, 1, &erro);
        }

        // Caso de parada: Não possui mais arestas para visitar
        return 0;
    }

/**
 * Algoritmos de Conectividade
 */ 
    void dfs(grafo* g, cor* vis, int v){
        
        // printf("Grafo v: %d\n", v);
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
            if(grau_vertice(g, i) != 0 && visitadosG[i] != preto) // @ajuste para usar no Caminho Euleriano
                return 0;
        
        // Fazendo o DFS no grafo transposto
        dfs(t, visitadosT, vInicial);

        // Caso algum não tenha sido visitado, nao eh SCC
        for(int i = vInicial; i < g->numVertices; i++)
            if(grau_vertice(g, i) != 0 && visitadosT[i] != preto)
                return 0;

        destruir_grafo(t, erro);

        return 1;
    }



















