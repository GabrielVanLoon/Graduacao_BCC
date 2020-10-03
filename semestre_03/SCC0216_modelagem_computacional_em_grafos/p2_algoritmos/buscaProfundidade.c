#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Implementação dos seguintes algoritmos em uma estrutura de grafos 
 * com matriz de adjacencias.
 */
    #define MAX_VERTICES 100
    
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

        int low; // Usado no tarjan
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
    void exibirOrdTopologica(Grafo *g);

    int dfsComOrdenacao(Grafo* g, int v, int tempo);
    int dfsComTarjan(Grafo* g, int v, int tempo);
    int ehVerticePai(Grafo* g, int pai, int filho);

/**
 * Main()
 */
int main(void){
    
    // Iniciando as variáveis
    Grafo g;
    memset(&g, 0, sizeof(Grafo));
    memset(&(g.parent), -1, sizeof(int) * MAX_VERTICES);

    /**
     * O código abaixo faz 3 operações:
     * - DFS do grafo com marcação de tempo e geração de árvore DFS.
     * - Exibe a Ordenação topológica do grafo.
     * - Classifica as arestas do grafo.
     * 
     * Todas as operações acima possuem custo O(V+A) pois consomem apenas 1 DFS.
     * 
     * Obs.: Slide 34/47 do PowerPoint 8 - Busca em Profundidade 
     */
        // g.qtdVertices    = 6;
        // g.adj[0][1].peso = ARESTA_COMUM;
        // g.adj[0][4].peso = ARESTA_COMUM;
        // g.adj[1][2].peso = ARESTA_COMUM;
        // g.adj[1][4].peso = ARESTA_COMUM;
        // g.adj[2][3].peso = ARESTA_COMUM;
        // g.adj[3][1].peso = ARESTA_COMUM;
        // g.adj[4][3].peso = ARESTA_COMUM;
        // g.adj[5][4].peso = ARESTA_COMUM;
        // g.adj[5][0].peso = ARESTA_COMUM;

        // int tempo = 1;
        // for(int i = 0; i < g.qtdVertices; i++){
        //     if(g.vertice[i].visitado == V_BRANCO)
        //         tempo = dfsComOrdenacao(&g, i, tempo);
        // }
        
        // exibirVertices(&g);
        // printf("\n");
        // exibirArestas(&g);
        // printf("\n");
        // exibirOrdTopologica(&g);

    /**
     * O código abaixo implementa as 3 operações:
     * - DFS do grafo com marcação de tempo e geração de árvore DFS.
     * - Classifica as arestas do grafo.
     * - Exibe os componentes fortemente conexos utilizando o algoritmo de Tarjan.
     * 
     * Todas as operações acima possuem custo O(V+A) pois consomem apenas 1 DFS.
     * 
     * Obs.: Slide 26/50 do PowerPoint 9 - Busca em Profundidade 
     */

        g.qtdVertices = 9;
        g.adj[1][2].peso = ARESTA_COMUM;
        g.adj[2][3].peso = ARESTA_COMUM;
        g.adj[2][5].peso = ARESTA_COMUM;
        g.adj[3][4].peso = ARESTA_COMUM;
        g.adj[4][3].peso = ARESTA_COMUM;
        g.adj[4][8].peso = ARESTA_COMUM;
        g.adj[5][1].peso = ARESTA_COMUM;
        g.adj[5][6].peso = ARESTA_COMUM;
        g.adj[6][7].peso = ARESTA_COMUM;
        g.adj[7][6].peso = ARESTA_COMUM;
        g.adj[8][4].peso = ARESTA_COMUM;
        g.adj[8][7].peso = ARESTA_COMUM;

        int tempo = 1;
        for(int i = 0; i < g.qtdVertices; i++){
            if(g.vertice[i].visitado == V_BRANCO)
                tempo = dfsComTarjan(&g, i, tempo);
        }


    return 0;
}

/**
 * Implementação das funções
 */ 
    void exibirVertices(Grafo *g){
        for(int i = 0; i < g->qtdVertices; i++){
            printf("\tv[%d] dfs[%d/%d] parent[%d]\n", i, g->vertice[i].descoberta, g->vertice[i].tempoFinal, g->parent[i]);
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

    int dfsComOrdenacao(Grafo* g, int v, int tempo){

        // 1º - Marcando o vértice como descoberto
        g->vertice[v].descoberta = tempo;
        g->vertice[v].visitado = V_CINZA;
        tempo += 1;

        // 2º - Percorre os vizinhos, também classifica as arestas
        for(int i = 0; i < g->qtdVertices; i++){
            
            if(g->vertice[i].visitado == V_BRANCO && g->adj[v][i].peso != ARESTA_VAZIA){
                g->parent[i]      = v; // Delega o pai
                g->adj[v][i].tipo = ARESTA_ARVORE;
                tempo = dfsComOrdenacao(g, i, tempo);
                        
            } else if(g->adj[v][i].peso != ARESTA_VAZIA) {

                if(ehVerticePai(g, v, i))               // v é pai de i
                    g->adj[v][i].tipo = ARESTA_AVANCO;
                else if(ehVerticePai(g, i, v))          // i é pai de v
                    g->adj[v][i].tipo = ARESTA_RETORNO;
                else
                    g->adj[v][i].tipo = ARESTA_CRUZAMENTO;

            }

        }

        // 3º - marca o vértice como finalizado
        g->vertice[v].tempoFinal = tempo;
        g->vertice[v].visitado   = V_PRETO;
        
        // Ordenação topologica: Insiro o vertice no vet aux
        g->vetAux[g->valAux] = v;
        g->valAux           += 1;

        return tempo+1;
    }

    int dfsComTarjan(Grafo* g, int v, int tempo){

        // 1º - Marcando o vértice como descoberto
        g->vertice[v].descoberta = tempo;
        g->vertice[v].visitado = V_CINZA;
        tempo += 1;

        /**
         * Tarjan
         * insiro o vértice atual na pilha de visitados
         */
        g->vetAux[g->valAux] = v;
        g->valAux           += 1;


        // 2º - Percorre os vizinhos, também classifica as arestas
        for(int i = 0; i < g->qtdVertices; i++){
            
            if(g->vertice[i].visitado == V_BRANCO && g->adj[v][i].peso != ARESTA_VAZIA){
               
                g->parent[i]      = v; // Delega o pai
                g->adj[v][i].tipo = ARESTA_ARVORE;
                tempo = dfsComTarjan(g, i, tempo);
                        
            } else if(g->adj[v][i].peso != ARESTA_VAZIA) {
                
                if(ehVerticePai(g, v, i))               // v é pai de i
                    g->adj[v][i].tipo = ARESTA_AVANCO;
                else if(ehVerticePai(g, i, v))          // i é pai de v
                    g->adj[v][i].tipo = ARESTA_RETORNO;
                else
                    g->adj[v][i].tipo = ARESTA_CRUZAMENTO;
            }
        }

        // 3º - marca o vértice como finalizado
        g->vertice[v].tempoFinal = tempo;
        g->vertice[v].visitado   = V_PRETO;
        
        /**
         * Tarjan
         * Define o low do vértice atual que será o mínimo entre:
         * - d(V)  (Tempo de descoberta de V)
         * - low(U arvore) (valor do Low(u) apenas para aresta de árvore)
         * - d(U !arvore) (valor de descoberta para arestas que não são de arvore)
         */
        int lowValue = g->vertice[v].descoberta;
        
        for(int u = 0; u < g->qtdVertices; u++){
            if(g->adj[v][u].peso != ARESTA_VAZIA){
                if(g->adj[v][u].tipo == ARESTA_ARVORE && g->vertice[u].low < lowValue)
                    lowValue = g->vertice[u].low;
                else if(g->adj[v][u].tipo != ARESTA_ARVORE && g->vertice[u].descoberta < lowValue)
                    lowValue = g->vertice[u].descoberta;
            }
        }
        g->vertice[v].low = lowValue;

        /**
         * Tarjan.
         * Por fim, se low(V) == descoberta(V) então terminou de achar o
         * componente conectado atual e portanto pode desesmpilhar todos os vértices
         * até encontra o V.
         */

        if(g->vertice[v].low == g->vertice[v].descoberta){
            int topo;
            printf("\t SCC:  ");
            do {
                topo = g->vetAux[g->valAux-1];
                g->valAux -= 1;
                
                printf("v[%d] ", topo);
            } while(topo != v);
            printf("\n\n");
        }
        
        return tempo+1;
    }