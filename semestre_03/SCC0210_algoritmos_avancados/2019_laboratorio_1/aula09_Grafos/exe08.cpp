/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 10  Grafos II
 */

/**
 * Exercicio 8 dijkstra
 * UVA 820
 */
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

typedef pair<int,int> ii;

// Implementado grafo com vertices ponderados
vector<ii>              grafo[205];
int                     visitado[205];
int                     dist[205];
int                     n, m, s, t; // Vertices, Arestas, Origem, Destino    

#define INFINITO 0x8000000

void dijkstra(){

    for(int i = 0; i < n; i++){
        dist[i]     = INFINITO;
    }
    
    priority_queue<ii, vector<ii>, greater<ii>>   PQ; 

    // Insere o primeiro elemento
    PQ.push(make_pair(0, s));
    dist[s] = 0;

    while(!PQ.empty()){

        ii u = PQ.top();  PQ.pop();

        // Se a distancia que chegou é maior do que a anterior
        if(u.first > dist[u.second])
            continue;
        
        for(unsigned i = 0; i < grafo[u.second].size(); i++){
            ii v = grafo[u.second][i];
            
            if(u.first + v.first < dist[v.second]){
                dist[v.second] = u.first + v.first;
                PQ.push(make_pair(u.first + v.first, v.second));
            }
        }

    }
    
}

int main(void){

    int networkCont = 1;
    
    cin >> n;
    while(n){
        cin >> s >> t >> m;

        s -= 1; // Transformando em 0-based
        t -= 1;


        // Carregando os vertices
        for(int i = 0; i < m; i++){
            int u, v, w;
            cin >> u >> v >> w;

            u -= 1; // transformando em 0-based
            v -= 1;

            grafo[u].push_back(make_pair(w,v));
            grafo[v].push_back(make_pair(w,u));
        }  

        dijkstra();

        printf("Network %d\n", networkCont++);
        printf("The bandwidth is %d.\n\n", dist[t]);
        
        //for(int i = 0; i < n; i++)
        //    printf("%d -> %d\n", i+1, dist[i]);

        // Resetando visitados e grafo
        for(int i = 0; i < n; i++){
            // arestas[i]    = priority_queue<ii, vector<ii>, greater<ii>>();
            grafo[i].clear();
            visitado[i] = 0;
        }
        
        cin >> n;
    }

    return 0;
}