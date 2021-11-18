#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int  N, M, K, i, j;
int  idade_h[1000001];
int  idade_m[1000001];

int  diff_h[1000001];   // pattern
int  pattern[1000001];

int  diff_m[2*1000001];   // "string buscada"


int main(void){

    scanf("%d %d %d", &N, &M, &K);

    // idade das mulheres
    for(i = 0; i < N; i++){
        scanf("%d", &idade_m[i]);
        idade_m[i] = idade_m[i]%M;
    }
        
    // idade homis
    for(i = 0; i < N; i++){
        scanf("%d", &idade_h[i]);
        idade_h[i] = idade_h[i]%M;
    }
       
    // Calculando a diferença das idades dif(h[i]->h[i+1])
    for(i = 0; i < N; i++){
        diff_h[i] = (-1)*(idade_h[i]-idade_h[(i+1)%N]); // O homem atua como pattern -> *-1
        diff_m[i] = idade_m[i]-idade_m[(i+1)%N];
    }
    // Calculando a diff de idade das mulheres
    for(i = N; i < 2*N-1; i++){
        diff_m[i] = diff_m[i%N];
    }

    for(i = 0; i < N; i++) printf("%d ", diff_h[i]);
    printf("\n");
    for(i = 0; i < 2*N-1; i++) printf("%d ", diff_m[i]);
    printf("\n\n");

    // Dança valida -> Equivalente à fazer uma busca de padrão no array de diferenças
    // Adaptação do KMP para um vetor numérico

    // 1ª Etapa - Pattern Finding
    i = 0, j = 1;
    pattern[0]   = 0;
    int pattern_size = 1;

    while(j < N){
        if(diff_h[i] == diff_h[j]){
            i += 1;
            j += 1;
            pattern[pattern_size++] = i;
        } else if(i != 0){
            i = pattern[i-1];
        } else {
            j += 1;
            pattern[pattern_size++] = 0;
        }
    }

    // 2ª Etapa - Buscando todas as repetições do pattern 
    i = 0, j = 0;
    int founds = 0;
    bool init_equal_end = false;
    while(i < 2*N-1){

        if(diff_m[i] == diff_h[j]){
            i += 1;
            j += 1;

            if(j == N){
                
                if(i == N)
                    init_equal_end = true;

                founds += 1;
                j = pattern[j-1];
            }
        } else if(j != 0) {
            j = pattern[j-1];
        } else {
            i += 1;
        }
    }

    //O KMP vai dizer quantas configurações finais é possível de ocorrer.
    printf("%d\n", founds);


    long long cmod = 1000000000+7;
    long long possibilidades = founds;
    long long n_restantes = N-2; // >> inicial e final fixas

    for(i=0; i < K-1; i++){
        possibilidades = (possibilidades * n_restantes)%cmod;
        n_restantes   -= 1;
    }

    printf("%lld\n", possibilidades);


    return 0;
}