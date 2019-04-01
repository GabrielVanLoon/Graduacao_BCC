#include <iostream>
#include <string>
#include <queue>
#include <string.h>

using namespace std;

typedef struct _arranjo{
	int vet[3][3]; 	// 1 2 3
					// 4 5 6
					// 7 8 x
	string track;
	int posX, posY;
	int f;			// Profundidade da bfs: f(n)
	int h;			// Heuristica: Distancia a Manhattan h(n)

	bool operator<(const struct _arranjo &a) const {
		return (h+f) > (a.h+a.f);
	}	
}Arranjo;

// Prototipos
	bool busca_Astar(Arranjo inicial);
	int h1(Arranjo a);
	void marcarVisitado(Arranjo a);
	bool foiVisitado(Arranjo a);
	
int main(void){
	int qtdCasos;
	cin >> qtdCasos;
	
	for(int c = 0; c < qtdCasos; c++){
		Arranjo a;
		
		// Lendo a configuração do 8 puzzle
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				char num; 
				cin >> num;
				if(num == 'x'){ 
					a.posX = i; 
					a.posY = j;
					a.vet[i][j] = 0;
				} else {
					a.vet[i][j] = (int) (num-'0');
				}
			}
		}
		
		a.track = "";

		// Realiza a busca a estrela 
		if(!busca_Astar(a)){
			cout << "unsolvable" << endl << endl;
		}

		if(c < (qtdCasos-1))
			cout << endl;
	}
}

// bool visitados[9][9][9][9][9][9][9][9][9]; // Custo memoria 10^9
int  moves[4][2] = { 1,  0,	  // down
					-1,  0,	  // up
					 0, -1,	  // left
					 0,  1 }; // right
bool busca_Astar(Arranjo inicial) { 
	
	// Resetando o visitados
	// memset(visitados, 0, sizeof(visitados));
	
	// Cria a fila de prioridade e insere o Arranjo inicial na PQ
	priority_queue<Arranjo> pq;
	
	inicial.f = 0;			 // f(n)
	inicial.h = h1(inicial); // h(n)
	pq.push(inicial);		 // Insere na fila de prioridade
	
	// Executando o bfs
	while(!pq.empty()){
		
		Arranjo a = pq.top();
		pq.pop();
		marcarVisitado(a);
		
		// Mostra as variações no Puzzle
		/*for(int i = 0; i < 3; i++)  for(int j = 0; j < 3; j++) cout << a.vet[i][j] << " ";
		cout << "(" << a.posX << "," << a.posY << ")";
		cout << endl;*/

		// Se a distancia da heuristica for igual a 0 entao chegou no objetivo
		if(a.h == 0) {
			cout << a.track << endl;
			return true;
		}

		// Empilhando os vizinhos
		for(int i = 0; i < 4; i++){
			int novoX = a.posX + moves[i][0];
			int novoY = a.posY + moves[i][1];

			// Movimentações inválidas
			if(novoX < 0 || novoX >= 3) continue;
			if(novoY < 0 || novoY >= 3) continue;
		
			Arranjo viz             = a; // Cria uma copia do arranjo atual
			viz.vet[novoX][novoY]   = a.vet[a.posX][a.posY];
			viz.vet[a.posX][a.posY] = a.vet[novoX][novoY];
			viz.posX = novoX;
			viz.posY = novoY;
			
			switch(i){
				case 0: viz.track += "d"; break;
				case 1: viz.track += "u"; break;
				case 2: viz.track += "l"; break;
				case 3: viz.track += "r"; break;
			}

			// Se ainda nao foi visitado reinsere na fila
			if(!foiVisitado(viz)){
				viz.f = a.f + 1; // Atualiza f(n) e h(n)
				viz.h = h1(viz);
				pq.push(viz);
			}
		}
		
	}
	
	return false;
}

// Calcula a heuristica h(n) para o arranjo
// Soma a distancia de Manhattan para cada bloco ate sua posicao devida
// d = |x1-x2| + |y1-y2|
int posicaoCorreta[9][2] = {0, 0,
							0, 0,
							0, 1,
							0, 2,
							1, 0,
							1, 1,
							1, 2,
							2, 0,
							2, 1 };
int h1(Arranjo a){	
	int dist = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(a.vet[i][j] == 0) continue;
			dist += abs(i - posicaoCorreta[a.vet[i][j]][0]); // Distancia linha
			dist += abs(j - posicaoCorreta[a.vet[i][j]][1]); // Distancia coluna
		}
	}
	return dist;
}

void marcarVisitado(Arranjo a){
	// visitados[a.vet[0][0]][a.vet[0][1]][a.vet[0][2]][a.vet[1][0]][a.vet[1][1]][a.vet[1][2]][a.vet[2][0]][a.vet[2][1]][a.vet[2][2]] = true;
}

bool foiVisitado(Arranjo a){
	//return visitados[a.vet[0][0]][a.vet[0][1]][a.vet[0][2]][a.vet[1][0]][a.vet[1][1]][a.vet[1][2]][a.vet[2][0]][a.vet[2][1]][a.vet[2][2]];
	return false;
}

