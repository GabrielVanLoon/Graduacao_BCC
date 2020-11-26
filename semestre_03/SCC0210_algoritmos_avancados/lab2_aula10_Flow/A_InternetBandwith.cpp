/**
 * Exercicio 1 Internet Bandwidth
 * UVA 820 
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

    int         grafo[QTD_VERTICES][QTD_VERTICES];
    int         parent[QTD_VERTICES];
    bool        visitado[QTD_VERTICES];
    int         qtdVertices, qtdArestas;
    int         s, t; // Source and Target

    // Primeira iteração: não sabemos se u->v ou v->u será utilizado e precisamos
    // permitir que ambos possam ser escolhidos. 
    // Logo, enquanto nao_utilizado[u][v] == [v][u] significa que a soma de banda 
    // maxima ainda nao esta sendo respeitada.
    bool        nao_utilizado[QTD_VERTICES][QTD_VERTICES];


/**
 * BFS COM AJUSTES
 * Realiza a BFS e retorna true se o Target @t foi alcançado
 */
bool bfs(){

    // Limpando vetor de visitados e parents
    memset(visitado, false, sizeof(visitado));
    memset(parent, -1, sizeof(parent));
    
    queue<int> q;
    visitado[s] = true;
    parent[s]   = -1;
    q.push(s);

    while(!q.empty()){
        
        int u = q.front();
        q.pop();

        for(int v = 0; v < qtdVertices; v++){

            if(!visitado[v] && grafo[u][v] > 0){
                visitado[v] = true;
                parent[v]   = u;
                q.push(v);
            }

            // Chegou no target => nao precisa gastar mais processamento
            if(visitado[t])
                break;
        }
    }

    return (visitado[t] == true);
}

/**
 * FORDFULKERSON
 */
int fordFulkerson(){

    int fluxoMaximo = 0;

    while(bfs()){
        int fluxoCaminho = INFINITO;

        // Verificando qual foi o fluxo maximo que passou 
        // pelo caminho que a bfs gerou.
        for(int v = t; v != s; v = parent[v]){
            int u   = parent[v];
            fluxoCaminho = min(fluxoCaminho, grafo[u][v]);
        }

        // Subtrai o valor do fluxoCaminho de todas as arestas utilizadas
        // Além disso, soma o valor na aresta de retorno (backwards)
        for(int v = t; v != s; v = parent[v]){
            int u   = parent[v];

            // Primeira vez utilizando a aresta?
            if(nao_utilizado[u][v] || nao_utilizado[v][u]){
                nao_utilizado[u][v] = nao_utilizado[v][u] = false;
                grafo[v][u] = 0;
            } 

            // utilizando o algoritmo padrao
            grafo[u][v] -= fluxoCaminho; // fowards
            grafo[v][u] += fluxoCaminho; // backwards
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
    
    int qtdCasos = 1;

    cin >> qtdVertices;
    while(qtdVertices > 0){

        // Resetando o Grafo e as arestas
        memset(nao_utilizado, 1, sizeof(nao_utilizado));
        memset(grafo, 0, sizeof(grafo));

        // Lendo as entradas
        cin >> s >> t >> qtdArestas;
        
        // Ajusta 1-based >> 0-based
        s -= 1;
        t -= 1;

        for(int i = 0; i < qtdArestas; i++){
            int u, v, capacity;
            cin >> u >> v >> capacity;

            // Atenção no problema: pode haver mais de 2 arestas dentre os mesmos
            // 2 nós, logo temos que ir somando a capacidade total e não apenas
            // atribuir.
            grafo[u-1][v-1] += capacity;
            grafo[v-1][u-1] += capacity;
        }

        printf("Network %d\n", qtdCasos++);
        printf("The bandwidth is %d.\n\n", fordFulkerson());

        // Reseta o grafo
        cin >> qtdVertices;
    }

    return 0;
}

