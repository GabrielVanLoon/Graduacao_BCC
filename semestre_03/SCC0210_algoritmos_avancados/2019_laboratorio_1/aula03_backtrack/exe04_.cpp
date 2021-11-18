/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Mar/2018
 * Aula 03	Back Tracking I
 */

/** 
 * Exercicio 04
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void backtracking(int* v, int pos, int soma);
void printSum();

vector<int> eq;
bool        hasSolution; 
int         t, n; // Soma total e Tamanho do  teste

int main(){
    cin >> t >> n;
    while(t && n){
        
        int vet[n], aux;
        hasSolution = false;
        
        for(int i = 0; i < n; i++){
            cin >> aux;
            vet[i] = aux;
        }

        cout << "Sums of " << t << ":" << endl;
        backtracking(vet, 0, 0);

        if(!hasSolution)
            cout << "NONE" << endl;

        // Soma e tamanho do prox. teste
        cin >> t >> n;
    }
    return 0;
}

void backtracking(int* v, int pos, int soma){
    // Parada: Alcançou ou ultrapassou a soma. 
    if(soma >= t || pos >= n){
        if(soma == t) printSum();
        return;
    }
    
    // Somando o valor atual
    eq.push_back(v[pos]);
    backtracking(v, pos+1, soma+v[pos]);
    eq.pop_back();

    // Não somando o valor atual e indo para o próximo valor.
    // Obs.: Para impedir repetições, a gente busca o próximo numero
    // diferente do atual.
    int prox = pos+1;
    while(prox < n && v[pos] == v[prox]) prox++;
    backtracking(v, prox, soma);
}

void printSum(){
    hasSolution = true;

    cout << eq.front();
    for(vector<int>::iterator it = eq.begin()+1; it != eq.end(); it++)
        cout << "+" << *it;
    cout << endl;
}