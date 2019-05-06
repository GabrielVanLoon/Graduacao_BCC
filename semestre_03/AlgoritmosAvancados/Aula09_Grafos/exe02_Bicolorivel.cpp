/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 09  Grafos I
 */

/**
 * Exercicio 2 - Bicolorivel
 * UVA 10004
 */
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

/**
 * Grafo com Lista de Adjacencias
 */ 
    #define BRANCO   -1
    #define PRETO     0
    #define VERMELHO  1
    
    int             vertice[100000];
    vector<int>      aresta[100000];

bool dfs_bicolorivel(int v, int cor){
    // Caso de parada, vertice já visitado.
    if(vertice[v] != BRANCO && vertice[v] != cor)
        return false;
    
    vertice[v] = cor;

    for(int i = 0; i < (int) aresta[v].size(); i++){
        int viz = aresta[v][i];

        if(vertice[viz] == cor){
            return false;
        
        } else if(vertice[viz] == !cor){
            continue;
        
        } else {
            bool r = dfs_bicolorivel(viz, !cor);
            if(r == false) 
                return false;
        }
    }

    return true;
}

int main(){

    int n, e;
    
    cin >> n;
    while(n){
        cin >> e;

        // Limpando o grafo
        for(int i = 0; i < n; i++){
            vertice[i] = BRANCO;
            aresta[i].clear();
        }

        for(int i = 0; i < e; i++){
            int u,v;
            cin >> u >> v;
            aresta[u].push_back(v);
            aresta[v].push_back(u);
        }

        if(dfs_bicolorivel(0,1))
            cout << "BICOLORABLE." << endl;
        else 
            cout << "NOT BICOLORABLE." << endl;

        cin >> n;
    }
    return 0;
}