/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Maio/2019
 * Aula 12  Programação Dinâmica
 */

/**
 * Exercicio 1 Wedding Shopping
 * UVA 11450 >> Passou
 */
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int qtdTestes;
int money, qtdRoupas, k, aux;
vector<int> precos[20];
int maxCost[20][205]; // gastoMaximo[Peça atual][Dinheiro Restante]

int solve(int peca, int somaTotal, int dinheiroRestante);

int main(){

    cin >> qtdTestes;
    for(int t = 0; t < qtdTestes; t++){
        
        // Resetando as variáveis
        for(int i = 0; i < 20; i++) precos[i].clear();
        memset(&maxCost, -1, sizeof(maxCost));
        
        // Lendo os custos
        cin >> money >> qtdRoupas;
        for(int i = 0; i < qtdRoupas; i++){
            cin >> k;
            for(int j = 0; j < k; j++){
                cin >> aux;
                precos[i].push_back(aux);
            } 
        }

        int resultado = solve(0, 0, money);
        if(resultado < 0)
            cout << "no solution" << endl; 
        else 
            cout << resultado << endl;
    }

    return 0;
}

int solve(int peca, int somaTotal, int dinheiroRestante){

    // Caso de parada ideal: Comprou todas as roupas e sobrou dinheiro
    if(peca >= (qtdRoupas) && dinheiroRestante >= 0)
        return somaTotal;

    // Caso de parada ruim: Acabou o dinheiro sem comprar todas as roupas
    if(dinheiroRestante <= 0)
        return -1;
    
    // Caso já haja a resposta para a maxCoast[peca][dinheiroRestante]
    if(maxCost[peca][dinheiroRestante] != -1)
        return maxCost[peca][dinheiroRestante];
    
    // Calculando o melhor resultado
    for(int i = 0; i < (int) precos[peca].size(); i++){
        maxCost[peca][dinheiroRestante] = max(maxCost[peca][dinheiroRestante], 
                solve(peca+1, somaTotal + precos[peca][i], dinheiroRestante - precos[peca][i]));
    }

    return maxCost[peca][dinheiroRestante];
}