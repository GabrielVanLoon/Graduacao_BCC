/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    mar/2018
 * Aula 06	Teoria dos Numeros
 */

/** 
 * Exercicio 04 - Factorial
 * UVA 10139 - Factovisors
 * Obs.: Solução boa porém não ótima, pois roda em 10s para casos muito longos...
 */
#include <iostream>
#include <set>
#include <bitset>
#include <math.h>

using namespace std;

set<int>        fatores;  // Salva os fatores
multiset<int>   fatCount; // Salva a potencia dos fatores
void primeFactors(long n) { 
    fatores.clear();
    fatCount.clear();

    while (n%2 == 0){ 
        fatores.insert(2);
        fatCount.insert(2);
        n = n/2; 
    } 
  
    for (long i = 3; i <= sqrt(n); i = i+2) { 
        while (n%i == 0) { 
            fatores.insert(i);
            fatCount.insert(i);
            n = n/i; 
        } 
    } 
  
    if (n > 2){
        fatores.insert(n);
        fatCount.insert(n);
    }
} 

int main(void){

    int qtdCasos;
    cin >> qtdCasos;

    while(qtdCasos--){
        long maisInteressante = -1, qtdDivisores = -1;
        long lower, upper;

        // Lendo os numeros limitantes
        cin >> lower >> upper;

        for(long i = lower; i <= upper; i++){
           int divisores = 1;
           
            // Encontra os fatores de cada i-ésimo numero no range.
            primeFactors(i);

            set<int>::iterator it;
            for(it = fatores.begin(); it != fatores.end(); it++){
                divisores *= (fatCount.count(*it) + 1);
                //cout << *it << "^" << fatCount.count(*it) << " x ";
            }

            if(qtdDivisores == -1 || divisores > qtdDivisores){
                maisInteressante  = i;
                qtdDivisores      = divisores;
            }
        }

        cout << "Between " << lower << " and " << upper << ", " << maisInteressante << 
                " has a maximum of " << qtdDivisores << " divisors." << endl;
    }
    
    return 0;
}

// Código para testar a exibição dos fatores
//primeFactors(100000);
//set<int>::iterator it;
//for(it = fatores.begin(); it != fatores.end(); it++){
//    cout << *it << "^" << fatCount.count(*it) << " x ";
//}