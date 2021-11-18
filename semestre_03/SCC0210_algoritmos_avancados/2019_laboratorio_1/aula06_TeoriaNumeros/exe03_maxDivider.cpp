/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    mar/2018
 * Aula 06	Teoria dos Numeros
 */

/** 
 * Exercicio 03 - Mesmo resto
 */
#include <iostream>
#include <set>
#include <vector.h>

using namespace std;

int main(void){
    int aux;

    do{ 
        vector<int> v;

        // Inicio do caso de teste.
        cin >> aux;
        if(aux == 0) break;

        do{ // Lendo os valores do caso de teste.
            v.push_back(aux);
            cin >> aux;
        }while(aux != 0);

        int maxDivisor = abs(v[0] - v[1]);

    }



    return 0;
}
