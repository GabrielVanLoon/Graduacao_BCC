#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

long long memo[30001][4];


/**
 * O valor c garante que não haverá combinações repetidas ao permitir
 * que apenas as moedas menores ou iguais à que foi utilizada à chegar
 * no estado atual sejam visiveis:
 * 
 * Ex: 10 = 10 OU 5 + 5 OU 5 + 1 + 1 ....
 * Impossível de acontecer: 10 = 1 + 1 + 1 + 1 + 5 (seria uma repetição do terceiro caso anterior) 
 */
long long calculate_ways(int value, int c, int* coins){
    // Condições de Parada:
    // - O restante do valor só pode ser pago com moedas de 1
    // - O conjunto de moedas permitida agora é apenas o 1
    if(value < 0) return 0;
    if(value < 5) return 1;
    if(c == 4) return 1;

    // Verificando o memo
    if(memo[value][c] == -1) {
        memo[value][c] = 0;
        for(int i = c; i < 5; i++){
            memo[value][c] += calculate_ways(value-coins[i], i, coins);
        }
    }

    return memo[value][c];
}



int main(void){

    int coins[6] = {50, 25, 10, 5, 1};
    int number;
    long long  ways;

    // iniciando a memoria
    memset(memo, -1, sizeof(memo));

    // for(int i = 0; i <= 30000; i++){
    //     calculate_ways(i, 0, coins);
    // }

    // Loop até o EOF
    while(scanf("%d",&number) != EOF){
        ways = calculate_ways(number, 0, coins);

        if(ways != 1)
            printf("There are %lld ways to produce %d cents change.\n", ways, number);
        else
            printf("There is only 1 way to produce %d cents change.\n", number);
    }

}