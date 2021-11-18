/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 10  Grafos II
 */

/**
 * Exercicio 6 MST
 * UVA 11631
 */
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

// Implementado grafo com vertices ponderados
vector<pair<int,int>>   grafo[200001];  // 2e5 >> não passa em N² precisa de Union Find
int                     visitado[200001];
int                     m, n, custoLuz; // Qtd. Vertices e Arestas       

int prim(){
    priority_queue<pair<int,int>> pq;
    int totalCost = 0, contador = 1;

    // Inserindo as arestas do vertice inicial
    visitado[0] = 1;
    for(unsigned i = 0; i < grafo[0].size(); i++){
        pq.push(grafo[0][i]);
    }

    // Inserindo vértice por vertice na árvore mst
    while(contador < m){
        pair<int,int> p;

        // Buscando menor vértice seguro
        while(!pq.empty()){
            p = pq.top();
            pq.pop();
            if(!visitado[p.second])
                break;
        }

        // Insere a aresta no custo e visita p
        // printf("Adicionou %d w:%d\t\tCusto Total: %d\n", p.second, p.first, totalCost);
        totalCost += -p.first;
        visitado[p.second] = 1;
        contador++;

        // Insere as arestas de p na PQ
        for(unsigned i = 0; i < grafo[p.second].size(); i++){
            pair<int,int> viz = grafo[p.second][i];
            if(visitado[viz.second]) 
                continue;
            pq.push(viz);
        }
    }

    return totalCost;
}


int main(){

    cin >> m >> n;
    while(m || n){

        // Carregando as arestas
        custoLuz = 0;
        for(int i = 0; i < n; i++){
            int u, v, w;
            cin >> u >> v >> w;

            custoLuz += w;
            grafo[u].push_back(make_pair(-w,v));
            grafo[v].push_back(make_pair(-w,u));
        }

        cout << (custoLuz - prim()) << endl;

        // Resetando os vertices e visitados
        for(int i = 0; i < n; i++){
            grafo[i].clear();
            visitado[i] = 0;
        }

        cin >> m >> n;
    }


    return 0;
}