#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

/**
 * Dado a <= b:
 * 
 * - Se (a mod b == 0): 
 *      0 resultados 
 * - Se (a mod b != 0):
 *      Padrão repetidos de (a*b) em (a*b)
 * 
 */

void print_pattern(int a, int b, int l, int r){


    int parcial[1000];

    for(int i = l; i <= r; i++ ) printf("%2d ", i);
    printf("\n");
    for(int i = l; i <= r; i++ ) printf("%2d ", (i%a)%b);
    printf("\n");
    for(int i = l; i <= r; i++ ) printf("%2d ", (i%b)%a);
    printf("\n");

    parcial[0] = 0;
    for(int i = 1; i <= r; i++ ){
        parcial[i] = parcial[i-1];
        if((i%a)%b != (i%b)%a) parcial[i] += 1;
    }

    for(int i = l; i <= r; i++ ) printf("%2d ", parcial[i]);
    printf("\n");
}

int main(void){
    
    // Study the cases
    // print_pattern(3,5,1,30); return 0;
    
    int t, a, b, q, temp;
    long long int l, r, m, parcial[202*202], resultado;

    scanf("%d", &t);

    for(int test = 0; test < t; test++){
        scanf("%d %d %d", &a, &b, &q);

        // // Garante a <= b
        // if(a > b) { temp = a; a = b; b = temp; }
        
        // Pegando o tamanho do bloco
        m = a * b;

        // Dentro de 1 pattert de tamanho (a*b) verifica quantos positivos ocorrem
        memset(parcial, 0, sizeof(parcial));
        
        for(int i = 1; i <= m; i++){
            parcial[i] =  parcial[i-1];
            if( (i%a)%b != (i%b)%a )
                parcial[i] += 1;
        }

        // Calcula a resposta baseada na quantidade de patterns há entre [l,r]
        // obs: o parcial é necessário pq pode haver patterns quebrados no inicio (head)
        // e final (tail) da sequencia de numeros
        for(int i = 0; i < q; i++){ 
            scanf("%lld %lld", &l, &r);
            
            long long acc_l = parcial[m] * ((l-1)/m) + parcial[(l-1)%m];
            long long acc_r = parcial[m] * ((r)/m)   + parcial[(r)%m];
            // printf("%lld = %lld \t %lld = %lld \n", l-1, acc_l, r, acc_r);
            cout << (acc_r - acc_l) << " ";
        }
        printf("\n");
    }

    return 0;
}