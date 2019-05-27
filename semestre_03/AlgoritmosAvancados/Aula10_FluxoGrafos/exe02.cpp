/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 11  Fluxo em Grafos
 */

/**
 * Exercicio 2 
 * UVA 10480
 */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

/**
 * Estrutura de um Grafo
 */

    #define QTD_VERTICES 100
    #define INFINITO     2147483647

    typedef pair<int,int> ii;

    int         grafo[QTD_VERTICES][QTD_VERTICES];
    int         parent[QTD_VERTICES];
    bool        visitado[QTD_VERTICES];
    int         qtdVertices, qtdArestas;
    int         s, t; // Source and Target

    bool        cortes[QTD_VERTICES][QTD_VERTICES];

/**
 * BFS COM AJUSTES
 * Realiza a BFS e retorna true se o Target @t foi alcançado
 */
bool bfs(bool exibeCortes){

    // Limpando vetor de visitados
    memset(visitado, false, sizeof(visitado));
    
    queue<int> q;
    visitado[s] = true;
    parent[s]   = -1;
    q.push(s);

    while(!q.empty()){
        
        int u = q.front();
        q.pop();

        for(int v = 0; v < qtdVertices; v++){
            
            // Lógica utilizada no ford fulkerson
            if(exibeCortes == false){
                if(!visitado[v] && grafo[u][v] > 0){
                    visitado[v] = true;
                    parent[v]   = u;
                    q.push(v);
                }

                // Chegou no target => nao precisa gastar mais processamento
                if(visitado[t])
                    break;

            // Lógica para exibir quais arestas foram cortadas
            } else {

                if(!visitado[v] && grafo[u][v] > 0 && !cortes[u][v]){
                    visitado[v] = true;
                    parent[v]   = u;
                    q.push(v);
                } else if(cortes[u][v]){
                     printf("%d %d\n", u+1, v+1);
                }
               
            }
            
        }
    }

    return (visitado[t] == true);
}

/**
 * FORDFULKERSON
 * Ajustado para realizar os cortes
 */
int fordFulkerson(){

    int fluxoMaximo = 0;

    while(bfs(false)){

        int fluxoCaminho = INFINITO;
        int x, y;

        // Verificando qual foi o fluxo maximo que passou 
        // pelo caminho que a bfs gerou.
        for(int v = t; v != s; v = parent[v]){
            int u   = parent[v];
            // fluxoCaminho = min(fluxoCaminho, grafo[u][v]);
            if(grafo[u][v] <= fluxoCaminho){
                x = u;
                y = v;
                fluxoCaminho = grafo[u][v];
            }
        }

        // Aresta de maior restrição >> Corte
        cortes[x][y] = cortes[y][x] = 1;
        

        // Subtrai o valor do fluxoCaminho de todas as arestas utilizadas
        // Além disso, soma o valor na aresta de retorno (backwards)
        for(int v = t; v != s; v = parent[v]){
            int u   = parent[v];
            grafo[u][v] -= fluxoCaminho; // fowards
            grafo[v][u] -= fluxoCaminho; // fowards
            // grafo[v][u] += fluxoCaminho; // backwards
        }

        // Adiciona o fluxo do caminho atual no fluxo total
        fluxoMaximo += fluxoCaminho;

        // Imprime o caminho e o fluxo
        //for(int v = t; v != -1; v = parent[v]){
        //    printf("%d <- ", v+1);
        //}    
        // printf("Fluxo: %d\n", fluxoCaminho);
    }

    return fluxoMaximo;
}


int main(void){
    
    cin >> qtdVertices >> qtdArestas;
    while(qtdVertices || qtdArestas){
           
        s = 0;
        t = 1;

        for(int i = 0; i < qtdArestas; i++){
            int u, v, capacity;
            cin >> u >> v >> capacity;
            grafo[u-1][v-1] = capacity;
            grafo[v-1][u-1] = capacity;
        }

        fordFulkerson();

        // Realiza os cortes
        // for(int u = 0; u < qtdVertices; u++){
        //     for(int v = u+1; v < qtdVertices; v++){
        //         if(cortes[u][v])
        //             printf("%d %d\n", u+1, v+1);   
        //     }      
        // }
       

        bfs(true);
        printf("\n");

        // Reseta o grafo e o vector de cortes
        memset(grafo, 0, sizeof(grafo));
        memset(cortes, 0, sizeof(cortes));

        cin >> qtdVertices >> qtdArestas;
    }

    return 0;
}

