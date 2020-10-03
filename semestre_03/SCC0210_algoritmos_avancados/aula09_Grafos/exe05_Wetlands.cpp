/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 10  Grafos II
 */


/**
 * Exercicio 5
 * UVA 469 - Wetlands on Florida
 */
#include <string.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

// Implementando o grafo como matriz de adjacencias
char        mapa[100][100];
int         visitado[100][100];
vector<int> resultados;

int moves[8][2] = {  1,  0,
                     1,  1,
                     0,  1,
                    -1,  1,
                    -1,  0,
                    -1, -1,
                     0, -1,
                     1, -1 };


void bfs(int l, int c, int x, int y){
    
    queue<pair<int,int>>    q;
    int                     visitado[l][c];
    int                     cont = 0;

    memset(visitado, 0, sizeof(visitado));
    
    // Inserindo o primeiro na fila e fazendo o bfs
    q.push(make_pair(x,y));
    visitado[x][y] = 1;

    while(!q.empty()){
        pair<int, int> v = q.front();
        q.pop();
        cont += 1;

        // Inserindo os vizinhos na fila
        for(int i = 0; i < 8; i++){
            
            int xViz = v.first  + moves[i][0];
            int yViz = v.second + moves[i][1];

            if(xViz < 0 || xViz >= l)   continue;
            if(yViz < 0 || yViz >= c)   continue;
            if(mapa[xViz][yViz] != 'W' || visitado[xViz][yViz]) continue;

            visitado[xViz][yViz] = 1;
            q.push(make_pair(xViz, yViz));
        }
    }

    cout << cont << endl; 

}

int main(void){

    int     qtdCasos;
    char    str[105];

    scanf(" %d", &qtdCasos);
    for(int i = 0; i < qtdCasos; i++){
        
        // cout << endl << "Resultados do teste nº " << i+1 << endl;
        int qtdLinhas = 0, qtdColunas = -1, x, y;

        // Carregando o mapa do grafo
        while(true){
            scanf(" %101[LW]",     str);
            // printf("%s''' %lu\n",  str, strlen(str));

            if(strlen(str) == 0) 
                break;

            if(qtdColunas == -1)
                qtdColunas = strlen(str);

            for(int i = 0; i < qtdColunas; i++)
                mapa[qtdLinhas][i] = str[i];
            
            qtdLinhas++;
            str[0] = '\0';
        }
        
        // Carregando as buscas
        while(true){
            
            if(scanf(" %101[0-9 ]", str) == EOF || strlen(str) == 0)
                break;

            sscanf(str, "%d %d", &x, &y);
            // printf("Valores %d %d\n", x, y);

            bfs(qtdLinhas, qtdColunas, x-1, y-1);

            str[0] = '\0';
        }


        /**cout << "Grafo lido..." << qtdLinhas << "x" << qtdColunas << endl;
        for(int i = 0; i < qtdLinhas; i++){
            for(int j = 0; j < qtdColunas; j++){
                cout << mapa[i][j];
            }
            cout << endl;
        }**/
        
        if(i+1 < qtdCasos)
            cout << endl;
    } 

    return 0;
}




















