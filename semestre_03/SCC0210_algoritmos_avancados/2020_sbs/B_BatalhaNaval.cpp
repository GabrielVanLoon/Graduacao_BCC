#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int N, D, L, R, C;
char tabuleiro[10][10];

int main(void){

    memset(tabuleiro,0,sizeof(tabuleiro));
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d %d %d %d", &D, &L, &R, &C);

        R -= 1;
        C -= 1;

        //vertical
        if(D == 1){
            for(int j = 0; j < L; j++){
                if(R+j >= 10 || tabuleiro[R+j][C]){
                    printf("N\n");
                    return 0;
                }
                tabuleiro[R+j][C] = 1;
            }
        } else {
            for(int j = 0; j < L; j++){
                if(C+j >= 10 || tabuleiro[R][C+j]){
                    printf("N\n");
                    return 0;
                }
                tabuleiro[R][C+j] = 1;
            }


        }
    }
    printf("Y\n");
    return 0;
}
