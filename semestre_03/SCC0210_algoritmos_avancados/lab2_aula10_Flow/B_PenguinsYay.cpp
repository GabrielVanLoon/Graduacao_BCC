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

    #define QTD_VERTICES 204
    #define INFINITO     2147483647

    // Max Flow Variables
    int         grafo[QTD_VERTICES][QTD_VERTICES];
    int         parent[QTD_VERTICES];
    bool        visitado[QTD_VERTICES];
    int         qtdVertices, qtdArestas;
    int         s, t; // Source and Target

    // Adaptação para a coordenada dos penguins
    struct gelo {
        int x,y,p,limit;
    };

    double      D;
    gelo        coords[QTD_VERTICES];
    int         N, total_penguins, grafoModelagem[QTD_VERTICES][QTD_VERTICES];
    vector<int> solutions;


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

            // utilizando o algoritmo padrao
            grafo[u][v] -= fluxoCaminho; // fowards
            grafo[v][u] += fluxoCaminho; // backwards
        }

        // Adiciona o fluxo do caminho atual no fluxo total
        fluxoMaximo += fluxoCaminho;

        // Imprime o caminho e o fluxo
        // for(int v = t; v != -1; v = parent[v]){
        //    printf("%d <- ", v+1);
        // }    
        // printf("Fluxo: %d\n", fluxoCaminho);
    }

    return fluxoMaximo;
}

/**
 * EUCLIDS DISTANCE
 */
bool reach(gelo a, gelo b){
    return D*D >= (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}


int main(void){
    
    int qtdCasos = 0;
    cin >> qtdCasos;

    for(int k = 0; k < qtdCasos; k++){

        // Resetando o Grafo e as arestas
        memset(grafoModelagem, 0, sizeof(grafoModelagem));
        solutions.clear();
        total_penguins = 0;

        // Lendo as entradas e  contando o total de penguins
        cin >> N >> D;
        for(int i = 1; i <= N; i++){
            cin >> coords[i].x >> coords[i].y >> coords[i].p >> coords[i].limit;
            total_penguins +=  coords[i].p;
        }

        // Modela um Max flow variando o indice final dentre todos os nós
        // O indice 0 é ficcional e possui limite maximo para todos os nos igual
        // a coord.p (imagina uma ilha gigante com infinitos penguis, e a gente distribui
        // eles dentre as N ilhas de acordo com a quantidade p de cada uma)
        
        s = 0;
        for(int i = 1; i <= N; i++){
            grafoModelagem[s][2*i-1] = coords[i].p;
        }

        // Cada bloco é representado por 2 nós, sendo um de entrada e outro de saída
        // O limite de saltos é representado como um aresta dente eles.
        qtdVertices = 1 + 2*N;

        for(int i = 1; i <= N; i++){
            grafoModelagem[2*i-1][2*i] = coords[i].limit;
        }

        for(int i = 1; i <= N; i++){
            for(int j = i+1; j <= N; j++){
                if( reach(coords[i], coords[j]) ){
                    grafoModelagem[2*i][2*j-1] = INFINITO;
                    grafoModelagem[2*j][2*i-1] = INFINITO;
                }
            }
        }
        
        // // Imprime a modelagem do sistema
        // for(int i = 0; i < qtdVertices; i++){
        //     for(int j = 0; j < qtdVertices; j++){
        //         if(grafoModelagem[i][j] == INFINITO)
        //             cout << "i" << " ";
        //         else 
        //             cout << grafoModelagem[i][j] << " ";
        //     } cout << endl;
        // }

        for(int dest = 1; dest <= N; dest++){
            // Define o novo destino
            t = 2*dest-1;

            // Remove a capacidade do 0 para o t
            grafoModelagem[s][t] = 0;

            // Copia a modelagem do problema para o grafo
            // em que o max flow será executado
            memcpy(grafo, grafoModelagem, sizeof(grafoModelagem));

            // Verifica se é possível mover todos os penguins para 
            // o bloco coord[t] contando com os que já se encontram nele.
            int flow = fordFulkerson();
            if(flow + coords[dest].p >= total_penguins)
                solutions.push_back(dest-1);
            
            // printf("Dest[%d], Flow[%d], Total[%d]\n", dest, flow + coords[dest].p, total_penguins);

            // Recupera a capacidade do 0 para o t
            grafoModelagem[s][t] = coords[dest].p;
        }


        if(solutions.size() == 0){
            cout << -1 << "\n";
        }  else {
            cout << solutions[0];
            for(int i = 1; i < solutions.size(); i++)
                cout << " " << solutions[i];
            cout << "\n";
        }
    }


    return 0;
}

