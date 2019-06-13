/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 12  Programação Dinâmica
 */

/**
 * Exercicio 3 - The Catcher
 * UVA 231
 */
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#define INFINITO 0x3F3F3F3F

int             aux, qtdMisseis, parent[1000], ans[1000], maxQtd;
vector<int>     alturas;

int main(void){

    int testCount = 0;

    cin >> aux;
    while(aux != -1){
        memset(ans,    0, sizeof(ans));
        memset(parent, 0, sizeof(parent));
        alturas.clear();
        maxQtd = 0;

        alturas.push_back(-INFINITO);
        while(aux != -1){
            alturas.push_back(aux);
            cin >> aux;
        }

        for(int i = alturas.size()-1; i >= 0; i--){
            for(int j = i-1; j >= 0; j--){
                if(alturas[j] >= alturas[i]){
                    parent[i] = j;
                    break;
                }
            }
        }

        ans[0] = 0;
        for(int i = 1; i < (int) alturas.size(); i++){
            ans[i] = 1 + ans[parent[i]];
            maxQtd = max(maxQtd, ans[i]);
            // printf("[%d] = %d   ||   Parent[%d] = %d   || ans = %d\n",i, alturas[i],  i, parent[i], ans[i]);
        }


        if(testCount != 0) printf("\n");
        printf("Test #%d:\n", ++testCount);
        printf("  maximum possible interceptions: %d\n", maxQtd);

        cin >> aux;
    }


    return 0;
}










