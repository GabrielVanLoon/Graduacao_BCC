/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 09  Grafos I
 */

/**
 * Exercicio 4 
 * UVA 10305
 */
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

/**
 * Grafo com Lista de Adjacencias
 */ 
    #define BRANCO   0
    #define PRETO    1
    
    int             vertice[1000];
    vector<int>      aresta[1000];
    stack<int>      ordTopologica;


void dfs(int v){
    vertice[v] = PRETO;

    for(int i = 0; i < (int) aresta[v].size(); i++){
        int viz = aresta[v][i];
        if(vertice[viz] == BRANCO)
            dfs(viz);
    }

    ordTopologica.push(v);
}

int main(){

    int n, m, u, v; // qtdVertices e qtdArestas

    cin >> n >> m;
    while(n > 0 || m > 0){
        
        // Limpando o grafo
        for(int i = 1; i <= n; i++){
            vertice[i] = BRANCO;
            aresta[i].clear();
        }

        for(int i = 0; i < m; i++){
            cin >> u >> v;
            aresta[u].push_back(v);
        }

        for(int i = 1; i <= n; i++){
            if(vertice[i] == BRANCO)
                dfs(i);
        }

        while(!ordTopologica.empty()){
            cout << ordTopologica.top();
            ordTopologica.pop();
            
            if(ordTopologica.empty())
                cout << endl;
            else 
                cout << " ";
        }

        cin >> n >> m;
    }
    
    return 0;
}