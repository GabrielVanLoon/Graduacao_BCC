/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 09  Grafos I
 */

/**
 * Exercicio 1 - Traveling Knight Problem (Problema do Cavalo)
 * UVA 439
 */
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

#define VISITADO         1
#define NAO_VISITADO    -1

int tabuleiro[9][9];
int moves[8][2] = { -2, +1,
                    -2, -1,
                    +2, +1,
                    +2, -1,
                    +1, -2,
                    -1, -2,
                    +1, +2,
                    -1, +2 };

int getCol(char col){
    return (col - 'a') + 1;
}

int getRow(char row){
    return (row - '0');
}

void bfs(int row, int col){
    // Preparando elemento inicial da bfs
    pair<int,int> ini (row, col);
    tabuleiro[ini.first][ini.second] = 0; 
    
    // Preparando a fila da bfs
    queue<pair<int,int>> q;
    q.push(ini);

    // Percorre bfs marcando distancias
    while(!q.empty()){
        pair<int,int> v (q.front());
        q.pop();

        // cout << "Posicao: " << v.first << " " << v.second << endl;

        for(int i = 0; i < 8; i++){
            pair<int,int> viz (v.first + moves[i][0], v.second + moves[i][1]);
            
    
            if(viz.first < 1 || viz.first > 8 || viz.second < 1 || viz.second > 8)
                continue;

            if(tabuleiro[viz.first][viz.second] != NAO_VISITADO)
                continue;
            
            tabuleiro[viz.first][viz.second] = tabuleiro[v.first][v.second] + 1;
            q.push(viz);
        }
    }
}

int main(){
    char posIni[3], posFim[3];
    
    while(scanf(" %2s %2s", posIni, posFim) != EOF){
        
        for(int i = 1; i <= 8; i++)
            for(int j = 1; j <= 8; j++)
                tabuleiro[i][j] = NAO_VISITADO;

        bfs(getRow(posIni[1]), getCol(posIni[0]));

        int qtdMoves = tabuleiro[getRow(posFim[1])][getCol(posFim[0])];
        printf("To get from %s to %s takes %d knight moves.\n", posIni, posFim, qtdMoves);
    }

    return 0;
}


