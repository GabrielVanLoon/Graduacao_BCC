#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Implementação dos seguintes algoritmos em uma estrutura de grafos 
 * com matriz de adjacencias.
 */
    #define MAX_VERTICES 100
    #define INFINITO     999999999
    
    #define ARESTA_VAZIA    0
    #define ARESTA_COMUM    1 

    #define ARESTA_ARVORE       1
    #define ARESTA_AVANCO       2
    #define ARESTA_RETORNO      3
    #define ARESTA_CRUZAMENTO   4

    #define V_BRANCO       0
    #define V_CINZA        1
    #define V_PRETO        2

    typedef struct _vertice{
        int visitado;
        int descoberta;
        int tempoFinal;
        
        int distancia; // Usado nos algoritmos de caminho
        int low;       // Usado no tarjan
    } Vertice;

    typedef struct _aresta{
        int peso;
        int tipo;
    } Aresta;

    typedef struct _grafo{
        Aresta    adj[MAX_VERTICES][MAX_VERTICES];
        Vertice   vertice[MAX_VERTICES];
        int     parent[MAX_VERTICES];
        int     qtdVertices;

        int     valAux, vetAux[MAX_VERTICES]; // Vetor auxiliar 
    } Grafo;

/**
 * Protótipos de algoritmos
 */
    void exibirVertices(Grafo *g);
    void exibirArestas(Grafo *g);

    int ehVerticePai(Grafo* g, int pai, int filho);

    int mstPrim(Grafo* g, int s);

/**
 * Main()
 */
int main(void){
    
    // Iniciando as variáveis
    Grafo g;
    memset(&g, 0, sizeof(Grafo));
    memset(&(g.parent), -1, sizeof(int) * MAX_VERTICES);

    /**
     * O código abaixo gera uma árvore geradora mínima utilizando o alg. de Prim.
     * 
     * A complexidade é O(A*log(V)), pois o maior custo está na ordenação dos vértices.
     * 
     * Obs.: Slide 22/39 do PowerPoint 10 - Árvore Geradora Mínima 
     */
    g.qtdVertices   = 6;

    g.adj[0][1].peso     = 6;
    g.adj[0][2].peso     = 1;
    g.adj[0][3].peso     = 5;

    g.adj[1][0].peso     = 6;
    g.adj[1][2].peso     = 2;
    g.adj[1][4].peso     = 5;

    g.adj[2][0].peso     = 1;
    g.adj[2][1].peso     = 2;
    g.adj[2][3].peso     = 2;
    g.adj[2][4].peso     = 6;
    g.adj[2][5].peso     = 4;

    g.adj[3][0].peso     = 5;
    g.adj[3][2].peso     = 2;
    g.adj[3][5].peso     = 4;

    g.adj[4][1].peso     = 5;
    g.adj[4][2].peso     = 6;
    g.adj[4][5].peso     = 3;

    g.adj[5][2].peso     = 4;
    g.adj[5][3].peso     = 4;
    g.adj[5][4].peso     = 3;

    mstPrim(&g, 0);

    exibirVertices(&g);

    return 0;
}

/**
 * Implementação das funções
 */ 
    void exibirVertices(Grafo *g){
        for(int i = 0; i < g->qtdVertices; i++){
            printf("\tv[%d] distancia[%d] parent[%d]\n", i, g->vertice[i].distancia, g->parent[i]);
        }
    }

    void exibirArestas(Grafo *g){ 
        for(int i = 0; i < g->qtdVertices; i++){
            printf("\tv[%d] -> {\n", i);
            for(int j = 0; j < g->qtdVertices; j++){
                if(g->adj[i][j].peso != ARESTA_VAZIA){
                    if(g->adj[i][j].tipo == ARESTA_ARVORE)
                        printf("\t   (v[%d] w[%d] t[arv])\n", j, g->adj[i][j].peso);
                    else if(g->adj[i][j].tipo == ARESTA_AVANCO)
                        printf("\t   (v[%d] w[%d] t[avanco])\n", j, g->adj[i][j].peso);
                    else if(g->adj[i][j].tipo == ARESTA_RETORNO)
                        printf("\t   (v[%d] w[%d] t[ret])\n", j, g->adj[i][j].peso);
                    else
                        printf("\t   (v[%d] w[%d] t[cruz])\n", j, g->adj[i][j].peso);
                }
            }
            printf("\t}\n");
        }

    }

    void exibirOrdTopologica(Grafo *g){
        printf("\t");
        for(int i = g->qtdVertices-1; i >= 0; i--)
            printf("V[%d] -> ", g->vetAux[i]);
        printf("\n");
    }

    int ehVerticePai(Grafo* g, int pai, int filho){
        while(g->parent[filho] != -1){
            if(g->parent[filho] == pai)
                return 1;
            filho = g->parent[filho];
        }
        return 0;
    }

    int mstPrim(Grafo* g, int s){

        /**
         * 1º Ajusta todas as variáveis que serão utilizadas:
         * - todos os vértices começam com distância infinita, com exceção da origem.
         * - vamos utilizar o visitado para indicar se a aresta já foi ou não incluida na árvore.
         * 
         * Obs: a distância não é a distância do vértice à origem, mas sim a menor aresta que conecta 
         *      o vertice U com a árvore já montada. (não confundir.... é sério)
         */
        for(int i = 0; i < g->qtdVertices; i++){
            g->vertice[i].distancia = INFINITO;
            g->vertice[i].visitado  = 0;
        }
        g->vertice[s].distancia = 0;

        /**
         * 2º Agora basta adicinar os N vertices existentes nos grafos 1 a 1. Para isso seguimos o
         * algoritmo:
         * - Escolho o vértice com menos distancia que ainda não está na árvore.
         * - Adiciono esse vértice na árvore.
         * - Relaxo, se possível, os vizinhos desse vértice (atualizando seu parent caso positivo).
         */
        for(int i = 0; i < g->qtdVertices; i++){

            // Procurando o vertice com menor distancia de com custo O(V), 
            // porém se fosse uma min_heap o custo seria O(1) nessa etapa.
            int v, minDist = INFINITO;
            for(int j = 0; j < g->qtdVertices; j++ ){
                if(g->vertice[j].visitado == 0 && g->vertice[j].distancia < minDist){
                    v       = j;
                    minDist = g->vertice[j].distancia;
                }
            }

            // Adicionando o vértice na árvore
            g->vertice[v].visitado = 1;
            
            // Relaxa a aresta
            for(int u = 0; u < g->qtdVertices; u++){
                if( g->adj[v][u].peso != ARESTA_VAZIA 
                    && (g->adj[v][u].peso) < g->vertice[u].distancia){
                    
                    g->vertice[u].distancia = (g->adj[v][u].peso);
                    g->parent[u]            = v;
                }
            }

            // Para ver as iterações acontecendo...
            // exibirVertices(g);
            // getchar();
            // system("clear");

        } // fim iteração

    }