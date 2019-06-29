#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Implementação dos seguintes algoritmos em uma estrutura de grafos 
 * com matriz de adjacencias.
 */
    #define MAX_VERTICES 100
    #define INFINITO     99999999
    
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

        int     valAux, vetAux[MAX_VERTICES][MAX_VERTICES]; // Vetor auxiliar p caminho entre pares 
    } Grafo;

/**
 * Protótipos de algoritmos
 */
    void exibirVertices(Grafo *g);
    void exibirArestas(Grafo *g);

    int ehVerticePai(Grafo* g, int pai, int filho);

    int dijkstra(Grafo* g, int s);
    int bellmanFord(Grafo* g, int s);
    int floydWarshall(Grafo* g);

/**
 * Main()
 */
int main(void){
    
    // Iniciando as variáveis
    Grafo g;
    memset(&g, 0, sizeof(Grafo));
    memset(&(g.parent), -1, sizeof(int) * MAX_VERTICES);

    /**
     * O código abaixo gera o menor caminho do source até todos os outros vértices.
     * Interessante notar que o código é identico ao mst de Prim, mudando apenas o if e o signifacdo
     * da distancia que dexa de ser a distância do vértice à MST e passa a ser a distancia do vértice
     * à origem.
     * 
     * A complexidade é O(A*log(V)), pois o maior custo está na ordenação dos vértices.
     * 
     * Obs.: Slide 22/39 do PowerPoint 10 - Árvore Geradora Mínima (utilizei o mesmo grafo do prim)
     */
            // g.qtdVertices   = 6;

            // g.adj[0][1].peso     = 6;
            // g.adj[0][2].peso     = 1;
            // g.adj[0][3].peso     = 5;

            // g.adj[1][0].peso     = 6;
            // g.adj[1][2].peso     = 2;
            // g.adj[1][4].peso     = 5;

            // g.adj[2][0].peso     = 1;
            // g.adj[2][1].peso     = 2;
            // g.adj[2][3].peso     = 2;
            // g.adj[2][4].peso     = 6;
            // g.adj[2][5].peso     = 4;

            // g.adj[3][0].peso     = 5;
            // g.adj[3][2].peso     = 2;
            // g.adj[3][5].peso     = 4;

            // g.adj[4][1].peso     = 5;
            // g.adj[4][2].peso     = 6;
            // g.adj[4][5].peso     = 3;

            // g.adj[5][2].peso     = 4;
            // g.adj[5][3].peso     = 4;
            // g.adj[5][4].peso     = 3;

            // dijkstra(&g, 0);
            // exibirVertices(&g);

    /**
     * O código de Bellman-Ford, ao contrário do Dijkstra, consegue identificar ciclos
     * negativos e lidar com pesos negativos. Seu custo, porém, fica na ordem de O(V*A).
     * 
     * Obs.: Slide 19/64 do PowerPoint 12 - Caminhos mínimos
     */
            // g.qtdVertices = 5;

            // g.adj[0][1].peso    = 3;
            // g.adj[0][2].peso    = 5;
            // g.adj[1][2].peso    = -2; // Comente essa linha para remover o ciclo negativo
            // g.adj[1][3].peso    = 6;
            // g.adj[2][1].peso    = 1;
            // g.adj[2][4].peso    = 6;
            // g.adj[2][3].peso    = 4;
            // g.adj[3][4].peso    = 2;
            // g.adj[4][0].peso    = -2;
            // g.adj[4][3].peso    = 7;

            // bellmanFord(&g, 0);
    /**
     * TODO
     */
        g.qtdVertices = 4;

        g.adj[0][2].peso    = -2;
        g.adj[1][0].peso    =  4;
        g.adj[1][2].peso    =  3;
        g.adj[2][3].peso    =  2;
        g.adj[3][1].peso    = -1;

        floydWarshall(&g);


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
            // printf("V[%d] -> ", g->vetAux[i]);
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

    int dijkstra(Grafo* g, int s){

        /**
         * 1º Ajusta todas as variáveis que serão utilizadas:
         * - todos os vértices começam com distância infinita, com exceção da origem.
         * - vamos utilizar o visitado para indicar se a aresta já foi ou não utilizada no algoritmo.
         * 
         * Obs: a distância é a distância total do caminho da origem até o vertice v.
         */
        for(int i = 0; i < g->qtdVertices; i++){
            g->vertice[i].distancia = INFINITO;
            g->vertice[i].visitado  = 0;
        }
        g->vertice[s].distancia = 0;

        /**
         * 2º Agora basta adicinar os N vertices existentes nos grafos 1 a 1. Para isso seguimos o
         * algoritmo:
         * - Escolho o vértice com menos distancia à S que ainda não foi visitado
         * - Marco o vértice como visitado.
         * - Relaxo, se possível, os vizinhos desse vértice (atualizando seu parent caso positivo).
         */
        for(int i = 0; i < g->qtdVertices; i++){

            // Procurando o vertice com menor distancia de com custo O(V), 
            // porém se fosse uma min_heap o custo seria O(log(V)) nessa etapa.
            int v, minDist = INFINITO;
            for(int j = 0; j < g->qtdVertices; j++ ){
                if(g->vertice[j].visitado == 0 && g->vertice[j].distancia < minDist){
                    v       = j;
                    minDist = g->vertice[j].distancia;
                }
            }

            // Adicionando o vértice na árvore
            g->vertice[v].visitado = 1;
            
            // Relaxa a aresta: Aqui está todo o custo do algortimo pois, se fosse uma maxheap:
            // A * log(v) >> percorrer as arestas e reordenar a heap em cada relaxamento.
            for(int u = 0; u < g->qtdVertices; u++){
                if( g->adj[v][u].peso != ARESTA_VAZIA 
                    && (g->vertice[v].distancia + g->adj[v][u].peso) < g->vertice[u].distancia){
                    
                    g->vertice[u].distancia = (g->vertice[v].distancia + g->adj[v][u].peso);
                    g->parent[u]            = v;
                }
            }

            // Para ver as iterações acontecendo...
            // exibirVertices(g);
            // getchar();
            // system("clear");

        } // fim iteração

    }

    int bellmanFord(Grafo* g, int s){

        /**
         * (similar ao dijkstra nessa parte...)
         * 1º Ajusta todas as variáveis que serão utilizadas:
         * - todos os vértices começam com distância infinita, com exceção da origem.
         * - vamos utilizar o visitado para indicar se a aresta já foi ou não utilizada no algoritmo.
         * 
         * Obs: a distância é a distância total do caminho da origem até o vertice v.
         */
        for(int i = 0; i < g->qtdVertices; i++){
            g->vertice[i].distancia = INFINITO;
        }
        g->vertice[s].distancia = 0;


        /**
         * 2ª Etapa - Relaxamentos
         * 
         * Seja |V| o nº de vértices do grafo, o loop irá percorrer |V|-1 vezes e irá passar por todas
         * as arestas do grafo. Sempre que for possível fazer o relaxamento faz e atualiza o parent.
         * 
         * Porém, ao acabar as |V|-1 iterações ainda for possível relaxar algum vértice então há ciclo
         * negativo no grafo.
         */
        int houveRelaxamento = 0, possuiCicloNegativo = 0;
        for(int i = 0; i <= g->qtdVertices; i++){
            houveRelaxamento = 0;
            
            for(int v = 0; v < g->qtdVertices; v++){
                for(int u = 0; u < g->qtdVertices; u++){
                    if( g->adj[v][u].peso != ARESTA_VAZIA 
                        && (g->adj[v][u].peso + g->vertice[v].distancia) < g->vertice[u].distancia){

                            g->parent[u]            = v;
                            g->vertice[u].distancia = (g->adj[v][u].peso + g->vertice[v].distancia);
                            houveRelaxamento        = 1;
                    }
                }
            }

            if(i == g->qtdVertices && houveRelaxamento)
                possuiCicloNegativo = 1;
            //else if(i < g->qtdVertices && !houveRelaxamento)
            //    break;
        }

        if(possuiCicloNegativo)
            printf("\tEsse grafo possui ciclo negativo!!\n\n");
        
        exibirVertices(g);

    }


    int floydWarshall(Grafo* g){

        /**
         * 1º Ajusta todas as variáveis que serão utilizadas:
         * Percorre a matriz de distancia de tal forma que:
         * - d(u,v) = infinito caso não haja conexão
         * - d(u,v) = w(u,v) caso haja conexão
         * - d(v,v) = 0
         */
        for(int v = 0; v < g->qtdVertices; v++){
            for(int u = 0; u < g->qtdVertices; u++){
                if(u == v)
                    g->vetAux[v][u] = 0;
                else if(g->adj[v][u].peso != ARESTA_VAZIA)
                    g->vetAux[v][u] = g->adj[v][u].peso;
                else
                    g->vetAux[v][u] = INFINITO;
            }
        }

        /**
         * 2ª Etapa - Relaxamentos
         * 
         * Seja |V| o nº de vértices do grafo, o loop irá percorrer |V| vezes o loop e para cada par
         * irá atualizar a distancia da seguinte forma:
         * 
         * d(u->v) = min( w(u->v) , w(u->k) + w(k->v) ) sendo o vértice da iteração atual...
         */

        for(int k = 0; k < g->qtdVertices; k++){
            
            for(int v = 0; v < g->qtdVertices; v++){
                for(int u = 0; u < g->qtdVertices; u++){
                    if(g->vetAux[v][u] > (g->vetAux[v][k] + g->vetAux[k][u])){
                        // printf("[%d]->[%d]->[%d] custo: %d + %d\n", u, v, k, g->vetAux[v][k], g->vetAux[k][u]);
                        g->vetAux[v][u] = (g->vetAux[v][k] + g->vetAux[k][u]);
                    }
                }
            }

        }

        // Exibe a matriz de distâncias
        for(int v = 0; v < g->qtdVertices; v++){
            printf("\t");
            for(int u = 0; u < g->qtdVertices; u++){
                printf("%d\t", g->vetAux[v][u]);
            }
            printf("\n\n");
        }

    }


    
    
















