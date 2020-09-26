#include <iostream>
#include <queue>
#include <set>

using namespace std;

struct combinacao{
    char    v[4];
    int     f;      // f(x) >> distancia da origem
    int     h;      // h(x) >> heuristica otimista

    bool operator<(const struct combinacao &a) const {
		return (h+f) > (a.h+a.f);
	}	
};

char moves[8][4] = {
    -1, 0, 0, 0,
    +1, 0, 0, 0,
     0,-1, 0, 0,
     0,+1, 0, 0,
     0, 0,-1, 0,
     0, 0,+1, 0,
     0, 0, 0,-1,
     0, 0, 0,+1
};

set<int>    visitados;
int         kases, k, forbidens, f;
combinacao  inicio, target, proibida;  


int get_combinacao(combinacao c){
    return (c.v[0]*1000) + (c.v[1]*100) + (c.v[2]*10) + c.v[3];
}

int get_hx(combinacao c){
    int dist = 0, parcial = 0;
    for(int i = 0; i < 4; i++){
       parcial = abs(target.v[i] - c.v[i]);
       parcial = (parcial > 5) ? 10 - parcial : parcial;
       dist   += parcial;
    }
    return dist;
}

bool eh_target(combinacao c){
    return c.v[0] == target.v[0] 
            && c.v[1] == target.v[1] 
            && c.v[2] == target.v[2] 
            && c.v[3] == target.v[3];
}

int busca_A_estrela(){

    // Preparando a fila de prioridade e o primeiro elemento
    priority_queue<combinacao> pq;
    inicio.f = 0;
    pq.push(inicio);

    // Enquanto a fila não estiver vazia
    while(!pq.empty()){
        
        // Remove o topo e marca como visitado
        combinacao atual = pq.top();
        pq.pop();
        visitados.insert(get_combinacao(atual));

        // Se for a configuração target para e retorna a distancia em passos
        if(eh_target(atual)){
            return atual.f;
        }

        // Senão coloca os vizinhos na fila
        for(int i = 0; i < 8; i++){
            combinacao viz;
            for(int j = 0; j < 4; j++){
                viz.v[j] = atual.v[j] + moves[i][j];
                viz.v[j] = (viz.v[j] == 10) ? 0 : viz.v[j];
                viz.v[j] = (viz.v[j] == -1) ? 9 : viz.v[j];
            }

            // Vizinho proibido ou já visitado
            if(visitados.count(get_combinacao(viz))){
                continue;
            }

            // Calculando a distancia mais heuristica e colocando na fila
            viz.f = atual.f + 1;
            viz.h = get_hx(viz);
            pq.push(viz);
        }
    }

    // -1 >> não possui caminho possível
    return -1;
}


int main(void){
    // Lendo quantidade de casos
    scanf(" %d", &kases);
    for(k = 0; k < kases; k++){
        
        // Reiniciando a variável de visitados
        visitados.clear();

        // Lendo as variáveis
        scanf(" %d %d %d %d", &inicio.v[0], &inicio.v[1], &inicio.v[2], &inicio.v[3]);
        scanf(" %d %d %d %d", &target.v[0], &target.v[1], &target.v[2], &target.v[3]);
        scanf(" %d", &forbidens);
        
        // Marcando os campos proibidos
        for(f = 0; f < forbidens; f++){
            scanf(" %d %d %d %d", &proibida.v[0], &proibida.v[1], &proibida.v[2], &proibida.v[3]);
            visitados.insert(get_combinacao(proibida));
        }

        printf("%d\n", busca_A_estrela());
    }
}








