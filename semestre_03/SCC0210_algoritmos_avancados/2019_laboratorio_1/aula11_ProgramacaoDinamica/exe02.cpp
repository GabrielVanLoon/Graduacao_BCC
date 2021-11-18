/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 12  Programação Dinâmica
 */

/**
 * Exercicio 2 - Jill Rides
 * UVA -- 507
 */
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#define INFINITO 0x3F3F3F3F

int  qtdRotas, qtdParadas, aux;
int  somaMax, iniM, fimM;
int  somaAtual, ini, fim; 
vector<int> parada;

int main(void){

    cin >> qtdRotas;
    for(int r = 1; r <= qtdRotas; r++){
        parada.clear();
        
        // Lendo as paradas
        cin >> qtdParadas;
        for(int i = 0; i < qtdParadas-1; i++){
            cin >> aux;
            parada.push_back(aux);
        }

        iniM = 1, fimM = parada.size(), somaMax = -INFINITO;
        ini  = 1, somaAtual = 0; 
        for(int i = 0; i < (int) parada.size(); i++){
            somaAtual += parada[i];

            // Achou um caminho melhor
            if(somaAtual > somaMax){
                iniM    = ini;
                fimM    = i+2;
                somaMax = somaAtual;
            }

            // Achou uma soma igual porem com caminho maior
            if(somaAtual == somaMax && (ini-i+2) > (iniM - fimM)){
                iniM    = ini;
                fimM    = i+2;
                somaMax = somaAtual;
            }

            // Soma zicou e ficou negativa então não compensa continuar nesse caminho
            if(somaAtual < 0){
                somaAtual = 0;
                ini = i+2;
            }

        }

        if(somaMax < 0)
            cout << "Route "<< r << " has no nice parts" << endl;
        else
            cout << "The nicest part of route " << r << " is between stops " << iniM << " and "<< fimM << endl;
    }

    return 0;
}

