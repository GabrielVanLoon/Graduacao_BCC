// OBS: NÃO FUNCIONA PARA O EIGHT PUZZLE >> COMPLEXIDADE MUITO ALTA
// RESULUÇÃO CORRETA UTILIZA "IDA"
#include <stdlib.h>
#include <queue>
#include <set>
#include <string>
#include <string.h>
#include <map>

using namespace std;

struct node {
    int     id;
    int     f;      // f(x) >> distancia da origem
    int     h;      // h(x) >> heuristica otimista
    bool operator<(const struct node &a) const {
		return (h+f) > (a.h+a.f);
	}	
};

struct tabuleiro {
    char    v[3][3];
    int     f;      // f(x) >> distancia da origem
    int     h;      // h(x) >> heuristica otimista
    char    track[60];
    int     posX, posY;

    bool operator<(const struct tabuleiro &a) const {
		return (h+f) > (a.h+a.f);
	}	
};
// 9! combinações >> Temos no máximo 362880 possibilidades

char moves[4][2] = {
    -1, 0, 
    +1, 0, 
     0,-1, 
     0,+1, 
};

char posicao_correta[9][2] = {
    2,2,
    0,0,
    0,1,
    0,2,
    1,0,
    1,1,
    1,2,
    2,0,
    2,1,
};

char move_letter[4] = {'u', 'd', 'l', 'r'};

map<int,tabuleiro> visitados;
int         kases, k;
tabuleiro   inicio, objetivo;

int get_combinacao(tabuleiro c){
    return (c.v[0][0]*100000000) + (c.v[0][1]*10000000) + (c.v[0][2]*1000000)
            + (c.v[1][0]*100000) + (c.v[1][1]*10000) + (c.v[1][2]*1000)
            + (c.v[2][0]*100) + (c.v[2][1]*10) + (c.v[2][2]);
}

int get_hx(tabuleiro c){
    int dist = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            dist += abs(i - posicao_correta[c.v[i][j]][0]);
            dist += abs(j - posicao_correta[c.v[i][j]][1]);
        }
    }
    return dist;
}

int get_hx_fraco(tabuleiro c){
    int dist = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            dist += (c.v[i][j] != objetivo.v[i][j]) ? 1 : 0;
        }
    }
    return dist;
}

bool eh_target(tabuleiro c){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(c.v[i][j] != objetivo.v[i][j])
                return false;
        }
    }
    return true;
}

int print_tabuleiro(tabuleiro c){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
           printf("%d ", c.v[i][j]);
        } printf("\n");
    }
    printf("\n");
}

int busca_A_estrela(){

    // Preparando a fila de prioridade e o primeiro elemento
    priority_queue<node> pq;
    node no_inicio;
    no_inicio.id = get_combinacao(inicio);
    no_inicio.f  = 0;
    pq.push(no_inicio);

    visitados[no_inicio.id] = inicio;

    // Enquanto a fila não estiver vazia
    while(!pq.empty()){
        
        // Remove o topo e marca como visitado
        node no_atual = pq.top();
        pq.pop();
        tabuleiro atual = visitados[no_atual.id];


        // Se for a configuração target para e retorna a distancia em passos
        if(eh_target(atual)){
            printf("%s\n", atual.track);
            // cout << atual.track << endl;
            return atual.f;
        }

        // Senão coloca os vizinhos na fila
        for(int i = 0; i < 4; i++){
            
            tabuleiro viz = atual;
            viz.posX = atual.posX + moves[i][0];
            viz.posY = atual.posY + moves[i][1];

            // Se a posição não for factível apenas cancela
            if(viz.posX < 0 || viz.posX >= 3) continue;
            if(viz.posY < 0 || viz.posY >= 3) continue;

            // atualiza a posição movida no tabuleiro
            viz.v[atual.posX][atual.posY] = viz.v[viz.posX][viz.posY];
            viz.v[viz.posX][viz.posY]     = 0;

            // Vizinho proibido ou já visitado
            if(visitados.count(get_combinacao(viz))){
                continue;
            }

            // Calculando a distancia mais heuristica e colocando na fila
            viz.f = atual.f + 1;
            viz.h = get_hx(viz);
            viz.track[atual.f] = move_letter[i];

            node no_viz;
            no_viz.id = get_combinacao(viz);
            no_viz.f  = viz.f;
            no_viz.h  = viz.h;
            visitados[no_viz.id] = viz; 

            pq.push(no_viz);
        }
    }

    // -1 >> não possui caminho possível
    printf("unsolvable\n");
    return -1;
}

int main(void){

    // Definindo como deve ser o target
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            objetivo.v[i][j] = i*3 + j + 1;
    objetivo.v[2][2] = 0;

    // Lendo quantidade de casos
    scanf(" %d", &kases);
    for(k = 0; k < kases; k++){
        
        if(k != 0)
            printf("\n");

        // Reiniciando a variável de visitados
        visitados.clear();
        // inicio.track = "";
        memset(inicio.track, 0, sizeof(inicio.track));

        // Lendo as variáveis
        char temp;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                scanf(" %c", &temp);
                inicio.v[i][j] = (temp == 'x') ? 0 : temp - '0';
                if(temp == 'x'){
                    inicio.posX = i;
                    inicio.posY = j;
                }
            }
        }
        
        busca_A_estrela();
    }
}
