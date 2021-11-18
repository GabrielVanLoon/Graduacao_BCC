/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Mar/2018
 * Aula 04	Usando Busca à Estrela (A* Search)
 * 
 */

/** Exercicio 1 - Four Wheels
 */
#include <iostream>
#include <string>
#include <queue>
#include <string.h>

using namespace std;

#define CONFIG_PROIBIDA -1
#define CONFIG_VISITADA  1

typedef struct _config{
    int n[4];
    int  distancia;
    bool operator<(const _config &c) const{
		return distancia > c.distancia;
	}
} Config;

// Variaveis
int qtdTestes, qtdProibidas;

int ini[4]; // Configuracao inicial
int fim[4]; // Configuracao final
int visitados[10][10][10][10];

int moves[8][4] = { -1,  0,  0,  0,
                     +1,  0,  0,  0,
                      0, -1,  0,  0,
                      0, +1,  0,  0,
                      0,  0, -1,  0,
                      0,  0, +1,  0,
                      0,  0,  0, -1,
                      0,  0,  0, +1 };

// Protótipos
int distancia(int* configAtual);
int bfs();

int main(){
    
    cin >> qtdTestes;
    for(int i = 0; i < qtdTestes; i++){
        
        // Lendo a configuracao inicial e final
        cin >> ini[0] >> ini[1] >> ini[2] >> ini[3];
        cin >> fim[0] >> fim[1] >> fim[2] >> fim[3];
        
        // Lendo as configuracoes proibidas
        cin >> qtdProibidas;
        for(int j = 0; j < qtdProibidas; j++){
            int n0, n1, n2, n3;
            cin >> n0 >> n1 >> n2 >> n3;
            visitados[n0][n1][n2][n3] = CONFIG_PROIBIDA;
        }

        // Executando o bfs para achar o resultado
        cout << bfs() << endl;

        // Limpando o visitados
        memset(visitados, 0, sizeof(visitados));

    }

    return 0;
}

int bfs(){

    int peso;
    priority_queue<pair<int, Config>> pq;
    Config  c;
    
    c.distancia = 0;
    c.n[0] = ini[0];
    c.n[1] = ini[1];
    c.n[2] = ini[2];
    c.n[3] = ini[3];

    // f(n) = g(n) + h(n).
    // g(n): Distancia em profundidade
    // h(n): Heuristica utilizada no A*
    peso = c.distancia + distancia(c.n);
    pq.push(pair<int, Config>(-peso,c));

    while(!pq.empty()){
        pair<int, Config> aux = pq.top();
        c = aux.second;
        pq.pop();

        // Caso essa seja a config buscada
        if(c.n[0] == fim[0] && c.n[1] == fim[1] && c.n[2] == fim[2] && c.n[3] == fim[3]){
            return c.distancia;
        }

        // cout << "Configuracao " << (int)c.n[0] <<  " " << (int)c.n[1] <<  " " << (int)c.n[2] <<  " " << (int)c.n[3] << endl; 
        // cout << "Peso: " << distancia(c.n) << endl;
        // getchar();
        
        // Colocando os vizinhos na fila caso nao sejam proibidos ou visitados
        for(int i = 0; i < 8; i++){
            Config viz;
            viz.distancia = c.distancia + 1;
            
            for(int j = 0; j < 4; j++){
                viz.n[j] = c.n[j] + moves[i][j];
                if(viz.n[j] < 0) viz.n[j] = 9;
                if(viz.n[j] > 9) viz.n[j] = 0;
            }

            int n0 = viz.n[0];
            int n1 = viz.n[1];
            int n2 = viz.n[2];
            int n3 = viz.n[3];

            // Caso ja tenha sido visitada ou seja proibida
            if(visitados[n0][n1][n2][n3] == CONFIG_VISITADA) continue; 
            if(visitados[n0][n1][n2][n3] == CONFIG_PROIBIDA) continue;
               
            visitados[n0][n1][n2][n3] = CONFIG_VISITADA;
            peso = viz.distancia  + distancia(viz.n);

            pq.push(pair<int, Config>(-peso, viz));
        }
    }

    return -1;
}

int distancia(int* configAtual){
    int dist = 0;
    for(int i = 0; i < 4; i++){
        int diff = abs(fim[i] - configAtual[i]);
        dist += (diff <= 5) ? diff : (10 - diff); 
    }
    return dist;
}