/*
vector<int> vetPrimos;
int primos[100005]; // 0 -> eh primo | 1 -> nao eh primo
int crivo(){
    int max = sqrt(100000);
    
    for(int i = 0; i < 100005; i++)
        primos[i] = 1;

    for(int i = 2; i < max; i++){
        if(!primos[i]) continue; // Nao eh primo
        vetPrimos.push_back(i);

        // Marca os não primos
        for(int j = i+i; j < max; j += i){
            primos[j] = 0;
        }
    }
}
*/

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;



int qtdNumeros = 0, expResults[1001];
int solve(int x, int n, int v, int soma){
    // printf("Soma atual: %d...\n", soma);
    // Caso de parada, soma deu maior que 
    if(soma == x){
        return 1;
    } else if(soma > x || v > qtdNumeros ){
        return 0;
    } else {
            
        int pega    = solve(x, n, v+1, soma+expResults[v]);
        int naopega = solve(x, n, v+1, soma);

        return pega + naopega;
    }
}

int main(void){

    int x, n;
    cin >> x >> n;
    
    for(int i = 1; i < 1001; i++){
        int e = 1;
        for(int j = 0; j < n; j++)
            e *= i;
        expResults[i] = e;

        // printf("%d^%d = %d\n", i , n , e);
        if(e > x) 
            break;
        else 
            qtdNumeros++;
    }

    // cout << qtdNumeros << endl;

    int maneiras = solve(x, n, 1, 0);
    cout << maneiras << endl;

    return 0;
}