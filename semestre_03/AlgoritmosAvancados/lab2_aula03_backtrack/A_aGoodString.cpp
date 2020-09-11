#include <iostream>

using namespace std;

int  kases,n;
char str[131073];

int min_moves(char c, int i, int j){
    // Caso 1: string de tamanho 1
    if(i == j){
        return (str[i] == c) ? 0 : 1;
    }

    int m =  i + ((j-i)/2);
    int caso1 = 0, caso2 = 0;

    // Caso 2: esquerda full 'c' e direita 'c+1'
    for(int it = i; it <= m; it++){
        caso1 += (str[it] != c) ? 1 : 0;
    }
    caso1 += min_moves(c+1, m+1, j);

    // Caso 3: direita full 'c' e esquerda 'c+1'
    for(int it = m+1; it <= j; it++){
        caso2 += (str[it] != c) ? 1 : 0;
    }
    caso2 += min_moves(c+1, i, m);

    return min(caso1, caso2);
}


int main(void){

    scanf("%d", &kases);
    for(int k = 0; k < kases; k++){
        
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            scanf(" %c", &str[i]);
        }

        printf("%d\n", min_moves('a', 0, n-1));
    }
}