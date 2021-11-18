#include <iostream>
#include <string.h>
#include <vector>

using namespace std;


int main(void){

    int  casos = 1;
    int  temp, *memo, max_seq = -1;
    vector<int> misseis;

    // loop de casos de teste
    while(true){
        // Reiniciando as variaveis
        misseis.clear();
        max_seq = temp = 1;
        
        // Lendo as entradas
        while(temp != -1){
            scanf("%d", &temp);
            misseis.push_back(temp);
        } 

        // Remove o -1 adicional
        misseis.pop_back();

        // Caso de parada
        if(misseis.size() == 0) break;
        
        // Alocando espaço pra dp
        memo = (int*) malloc( misseis.size() * sizeof(int) );

        // Computa uma espécie de LIS decrescente não crescente
        for(int i = 0; i < misseis.size(); i++){
            memo[i] = 1;
            for(int j = 0; j < i; j++){
                if(misseis[j] >= misseis[i] && memo[j]+1 > memo[i])
                    memo[i] = memo[j] + 1;
            }

            if(memo[i] > max_seq)
                max_seq = memo[i];
        }

        // desaloca a DP
        free(memo);

        // Exibe o resultado
        if(casos > 1) printf("\n");
        printf("Test #%d:\n", casos++);
        printf("  maximum possible interceptions: %d\n", max_seq);

    }


    return 0;
}


