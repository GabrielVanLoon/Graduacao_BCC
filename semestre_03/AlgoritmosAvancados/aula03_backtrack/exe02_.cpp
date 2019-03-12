/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Mar/2018
 * Aula 03	Back Tracking I
 */

/** 
 * Exercicio 02
 */
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void backtracking(int* tab, int n, int col);
bool validPos(int* tab, int n, int col, int row);
void printTab(int* tab, int n);

int main(){

    int n;
    while(cin >> n){

        // Associa a posição de cada rainha da forma: tabuleiro[coluna] = linha.
        // Se (linha == 0) então não há rainhas naquela coluna ainda.
        // Obs.: Vetor One-Based.
        int tabuleiro[n+1] = {0};
        int row, col;

        // Posição obrigatória para uma das N rainhas
        cin >> row >> col;
        tabuleiro[col] = row;

        // Realizando o backtracking
        cout << "Solution" << endl;
        backtracking(tabuleiro, n, 1);

    }
    return 0;
}

void backtracking(int* tab, int n, int col){
    
    // Caso de parada: Completou todo o tabuleiro
    if(col == n+1){
        printTab(tab, n);
        return;
    }

    // Caso a coluna seja a de preenchimento obrigatorio
    if(tab[col] != 0){
        backtracking(tab, n, col+1);

    // Recursao: Acha uma posicao na coluna e desce a rec.
    } else {
        for(int r = 1; r <= n; r++){
            if(validPos(tab, n, col, r)){
                tab[col] = r;
                backtracking(tab, n, col+1);
                tab[col] = 0;
            }
        }
    }
}

bool validPos(int* tab, int n, int col, int row){
    for(int c = 1; c <= n; c++){
        if(c == col || tab[c] == 0) continue;

        // Estão na mesma linha
        if(tab[c] == row) return false;
        
        // Estao na mesma diagonal
        int diffCol = abs(col - c);
        int diffRow = abs(row - tab[c]);
        if(diffCol == diffRow) return false;
    }
    return true;
}

void printTab(int* tab, int n){
    for(int i = 1; i <= n; i++)
        cout << tab[i] << " ";
    cout << endl;
}