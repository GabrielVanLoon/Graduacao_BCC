/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 09  Grafos I
 */

/**
 * Exercicio 1 - Traveling Knight Problem (Problema do Cavalo)
 * UVA 539 (Nao funciona, tem que usar UnionSet que ainda não sei)
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
    
    int             vertice[1000];
    vector<int>      aresta[1000];

void dfs(int v){
    if(vertice[v] != BRANCO)
        return;
    
    vertice[v] = PRETO;

    for(int i = 0; i < (int) aresta[v].size(); i++){
        int viz = aresta[v][i];
        if(vertice[viz] == BRANCO)
            dfs(viz);
    }
}

int main(){

    int qtdCasos;
    cin >> qtdCasos;

    for(int i = 1; i <= qtdCasos; i++){

        char largest[3], aux[4];
        scanf(" %1s%*c", largest);
        //printf("Lido: '%s'...\n", largest);

        // Limpando o  grafo
        for(int i = 'A'; i <= (int) 'Z'; i++){
            vertice[i] = BRANCO;
            aresta[i].clear();
        }

        // Lendo as arestas
        do{
            if( scanf("%c%c%*c", &aux[0], &aux[1]) == EOF)
                break;
            //printf("Lido: '%s'...\n", aux);
            if(aux[0] == '\n' || aux[0] == '\r' || aux[0] == ' ')
                break;
            
            int u = aux[0], v = aux[1];
            aresta[u].push_back(v);
            aresta[v].push_back(u);
        }while(true);

        // Percorrendo os componentes
        int qtdComponentes = 0;
        for(int i = 'A'; i <= (int) largest[0]; i++){
            if(vertice[i] == BRANCO){
                qtdComponentes++;
                dfs(i);
            }
        }
 
        if(i == qtdCasos)
            cout << qtdComponentes << endl;
        else 
            cout << qtdComponentes << endl << endl;
    }

    return 0;
}