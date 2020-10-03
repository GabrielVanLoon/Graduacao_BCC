#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX = 1000000000;

struct coord{
    int x,y;
};

struct reta{
    int Ax,Ay,Bx,By;
};

struct poligono{
    vector<coord> arestas;
};


int N, M, x1,x2,y1,y2;
coord               compinhos[500];
reta                segs[500];
vector<poligono>    areas;


int main(void){
    // Quadrado inicial
    poligono inicial;
    inicial.arestas.push_back(coord {0,0});
    inicial.arestas.push_back(coord {MAX,0});
    inicial.arestas.push_back(coord {MAX,MAX});
    inicial.arestas.push_back(coord {0,MAX});

    areas.push_back(inicial);


    // Lendo as entradas
    scanf("%d %d", &N, &M);

    // 
    for(int i = 0; i < N; i++)
        scanf("%d %d %d %d", &segs[i].Ax, &segs[i].Ay, &segs[i].Bx, &segs[i].By);
    for(int i = 0; i < M; i++)
        scanf("%d %d", &compinhos[i].x, &compinhos[i].y);




}

