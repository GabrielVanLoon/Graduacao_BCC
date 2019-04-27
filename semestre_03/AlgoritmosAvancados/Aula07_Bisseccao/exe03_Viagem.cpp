/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Abril/2019
 * Aula 07  Busca Binária e Método da Bissecção
 */

/**
 * Exercicio 03 - Viagem
 * UVA 907
 */
#include <iostream>
#include <string>

using namespace std;

// Retorna em quantas K noites consegue fazer a viagem
// andando no maximo dist por dia
int solve(int *camps, int n, int dist);

int main(void){

    // Lendo qtd de Campos e qtd de Noites
    int qtdCampos, qtdNoites;
    while(cin >> qtdCampos >> qtdNoites){

        // Lendo as distancias dos campos
        int dists[qtdCampos+1], distTotal = 0;
        for(int i = 0; i <= qtdCampos; i++){
            int aux;
            cin >> aux;
            dists[i]   = aux;
            distTotal += aux; 
        }

        // Testa a distancia mínima que consegue percorrer em K noites
        // cout << "Distancia total: " << distTotal << endl;

        // Caso trivial >> Nenhuma noite sem dormir então vai percorrer todo caminho
        if(qtdNoites == 0){
            cout << distTotal << endl;
            continue;
        }

        int d, min = 0, max = distTotal, distMin = -1;

        while(min <= max) {
            d = (min + max) / 2;
            int noites = solve(dists, qtdCampos+1, d);


            if(noites == -1){ // Nao alcançou o final, incrementa distancia 
                min = d+1;
            } else if(noites > qtdNoites){
                min = d+1; // Dormiu + vezes doq deveria, então a distancia nao foi suficiente
            } else {
                if(noites == qtdNoites)
                    distMin = d;
                max     = d-1; // Dormiu <= vezes que deveria, a distancia esta muito grande.
            }

            // printf("Distancia atual: (%d,%d): %d.\t\t Dist minima: %d e Noites: %d \n", min, max, d, distMin, noites);
        }

        // DistMin será igual a 1 quando houver mais noites doq acampamentos.
        if(distMin == -1){
            cout << d << endl;
        } else {
            cout << distMin << endl;
        }
        

    }

    return 0;
}

// Retorna em quantas K noites consegue fazer a viagem
// andando no maximo dist por dia. Retorna -1 caso seja impossivel chegar no final.
int solve(int* distProx, int n, int dist){
    int noites = 0, distDia = 0;

    for(int i = 0; i < n; i++){
        if(distProx[i] > dist){
            return -1; // Impossivel...
        }

        if(distDia + distProx[i] > dist){ // Não chega no proximo acampamento.
            noites  += 1;
            distDia  = distProx[i];
        } else { // Chega no proximo acampamento
            distDia  += distProx[i];
        }
    }

    return noites;
}