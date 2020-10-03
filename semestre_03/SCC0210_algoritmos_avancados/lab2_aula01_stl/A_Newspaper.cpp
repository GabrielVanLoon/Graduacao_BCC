#include <iostream>
#include <map>

using namespace std;

int main(void){

    int N; // qtd testes
    scanf(" %d", &N);

    for(int i = 0; i < N; i++){
        map<char, int> valor;     // map letra -> valor
        int  K, M, v;           // Letras no map, linhas no artigo
        char c;
        long t = 0;

        // Lendo letras -> valores
        scanf(" %d", &K);
        for(int j = 0; j < K; j++){
            scanf(" %c %d", &c, &v);
            valor[c] = v;
        }
        
        // Lendo o artigo
        scanf(" %d%*c", &M);
        for(int j = 0; j < M; j++){
            do{
                scanf("%c", &c);
                t += valor[c];
            }while(c != '\n');
        }

        printf("%01ld.%02ld$\n", t/100, t%100);
    }

    return 0;
}