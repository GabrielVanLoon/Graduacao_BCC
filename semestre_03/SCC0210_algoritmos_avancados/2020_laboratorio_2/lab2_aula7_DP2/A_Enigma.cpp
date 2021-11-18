#include <iostream>
#include <string.h>

using namespace std;

char    S[1001];
int     size, N;
short   memo[1001][1001], prox[1001][1001], dig[1001][1001];

bool resta_zero(int i, int r){
    // Caso de parada: i == size
    // -> Se r == 0 achou um divisor de N
    if(i == size)
        return (r == 0); 

    // Caso já visitou esse teste
    if(memo[i][r] != -1)
        return memo[i][r];

    // Se eu conheço o digito
    if(S[i] != '?'){
        int digito = S[i] - '0';
        memo[i][r] = resta_zero(i+1, (r*10 + digito) % N);
        dig[i][r]  = digito;
        prox[i][r] = (r*10 + digito) % N;
    }

    // Se não conheço vou testando de forma crescente
    else {
        memo[i][r] = 0;

        // Se o primeiro caracter for '?' não testar 0
        int digito = (i == 0) ? 1 : 0;

        for( ; digito < 10; digito++){
            if(resta_zero(i+1, (r*10 + digito) % N)){
                memo[i][r] = 1;
                dig[i][r]  = digito;
                prox[i][r] = (r*10 + digito) % N;
                break;
            }
        }
    }

    return memo[i][r];
}


int main(void){
    memset(memo, -1, sizeof(memo));

    // Lendo as entradas
    scanf("%s %d", S, &N);
    size = strlen(S);

    if(!resta_zero(0,0)){
        printf("*");
    } else {
        int r = 0;
        for(int i = 0; i < size; i++){
            printf("%d", dig[i][r]);
            r = prox[i][r];
        }
    }
    printf("\n");

}