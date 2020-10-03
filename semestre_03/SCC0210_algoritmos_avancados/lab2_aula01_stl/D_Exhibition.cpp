#include <iostream>
#include <vector>
#include <array>
#include <set>

using namespace std;

int main(void){

    int kasos;
    scanf("%d", &kasos);
    for(int k = 1; k <= kasos; k++){

        int N, M, temp;
        double total_unicas = 0.0;
        set<int>     figurinhas[10001];
        int             qtd_unicas[51];

        // Limpando array de a 50
        for(int i = 0; i < N; i++){
            qtd_unicas[i] = 0;
        }

        // Lendo as figurinhas
        scanf("%d", &N);
        for(int i = 0; i < N; i++){
            scanf("%d", &M);
            for(int j = 0; j < M; j++){
                scanf("%d", &temp);
                figurinhas[temp].insert(i);
            }
        }

        // Percorrendo as figurinhas e verificando quais sao unicas
        for(int j = 0; j < 10001; j++){
            if(figurinhas[j].size() == 1){
                total_unicas += 1.0;
                set<int>::iterator it = figurinhas[j].begin();
                qtd_unicas[*it] += 1;
            }
        }

        // Corner Case: todo mundo tem todas as figurinhas
        if(total_unicas == 0) total_unicas = 1;
            
        
        printf("Case %d:", k);
        for(int i = 0; i < N; i++){
            printf(" %.6lf%%", 100.0 * (qtd_unicas[i]/total_unicas));
        }
        printf("\n");

    }

    return 0;
}