/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Mar/2018
 * Aula 03	Back Tracking I
 */

/** 
 * Exercicio 01
 */
#include <iostream>
#include <string>

using namespace std;

int  primeRing[16];
bool isPrime[40] =  { true };
bool visited[16] =  { false };

void loadPrimes();
void backtracking(int n, int pos);
void printPrimeRing(int n);

int main(){
    loadPrimes();
    
    int  n, count = 1;
    bool firstCase = true;

    // Entrando com o tamanho do anel no caso de teste
    while(cin >> n){
        if(!firstCase) cout << endl;
        cout << "Case " << count++ << ":" << endl;

        // Preparando o anel para o backtracking
        visited[1]   = true;
        primeRing[0] = 1;
        
        backtracking(n, 0);
        firstCase = false;
    }
    return 0;
}

void backtracking(int n, int pos){
    // Parada: Último número no anel, se for primo com o primeiro, imprime o anel
    if(pos == n-1){
        int soma = primeRing[pos] + 1;
        if(isPrime[soma]) 
        printPrimeRing(n);
        return;

    // Recursao: Verifica os adjacentes possiveis e desce a rec.
    } else {
        
        for(int i = 2; i <= n; i++){
            // Caso o num. ja tenha sido usado
            if(visited[i]) continue;
            
            int somaAdj = primeRing[pos] + i;
            if(isPrime[somaAdj]){
                primeRing[pos+1] = i; 
                visited[i] = true;
                backtracking(n, pos+1);
                visited[i] = false;
            }
        }
    }
}

void printPrimeRing(int n){
    for(int i = 0; i < n; i++) 
        cout << primeRing[i] << " ";
    cout << endl;
}

void loadPrimes(){
    isPrime[0] = isPrime[1] = false;
    // Set todos para true
    for(int i = 2; i < 40; i++) 
        isPrime[i] = true;

    for(int i = 2; i < 40; i++){
        if(!isPrime[i]) continue;
        for(int j = 2*i; j < 40; j += i)
            isPrime[j] = false;
    }
}