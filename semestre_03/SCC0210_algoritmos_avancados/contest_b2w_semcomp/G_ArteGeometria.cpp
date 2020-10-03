#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX = 1000000000;

struct coord{
    long long x,y;
    bool contado;
};

struct triangulo{
    long long x1,x2,x3;
    long long y1,y2,y3; 
};

long long         N, M, T; // N pontos, M triangulos, T pontos dentro de 1+ triangulo
coord       pontos[5*100001];
triangulo   triang[5*10001];


double area_triangulo(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
    double a = abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
    return a;
}

bool esta_dentro(coord* ponto, triangulo* triang) { 
   double original = area_triangulo(triang->x1, triang->y1, triang->x2, triang->y2, triang->x3, triang->y3);   
   double area_t1 = area_triangulo(ponto->x, ponto->y, triang->x2, triang->y2, triang->x3, triang->y3); 
   double area_t2 = area_triangulo(triang->x1, triang->y1, ponto->x, ponto->y, triang->x3, triang->y3); 
   double area_t3 = area_triangulo(triang->x1, triang->y1, triang->x2, triang->y2, ponto->x, ponto->y); 

   return (original == (area_t1 + area_t2 + area_t3)); 
} 


int main(void){
    T = 0;

    // lendo os valores
    scanf("%d %d", &N, &M);

    // lendo os pontos
    for(int i = 0; i < N; i++){
        scanf("%d %d", &pontos[i].x, &pontos[i].y);
        pontos[i].contado = false;
    }
        

    // lendo os triangulos
    for(int i = 0; i < M; i++)
        scanf("%d %d %d %d %d %d", &triang[i].x1, &triang[i].y1, &triang[i].x2, &triang[i].y2, &triang[i].x3, &triang[i].y3);


    for(int j = 0; j < M; j++){ // 10^5
        for(int i = 0; i < N; i++){ // 10 ^ 4 
            if(pontos[i].contado == false && esta_dentro(&pontos[i], &triang[j])){
                pontos[i].contado = true;
                T +=1;
            }
        }
    }

    // Verificando o tipo
    if(T == N)
        printf("4");
    else if(T*4 >= 3*N)
        printf("3");
    else if(T*4 >= 2*N)
        printf("2");
    else if(T*4 >= 1*N)
        printf("1");
    else // T == 0
        printf("0");

    return 0;
}