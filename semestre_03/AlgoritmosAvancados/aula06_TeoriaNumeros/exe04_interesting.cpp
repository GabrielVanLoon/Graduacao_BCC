/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    mar/2018
 * Aula 06	Teoria dos Numeros
 */

/** 
 * Exercicio 02 - Factorial
 * UVA 10139 - Factovisors
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

int gcd(long a, long b){
    return (b == 0) ? a : gcd(b, a % b);
}


long getQtdDivisores(){
    long divisores = 1;
           
    // Encontra os fatores de cada i-ésimo numero no range.
    primeFactors(i);

    set<int>::iterator it;
    for(it = fatores.begin(); it != fatores.end(); it++){
        divisores *= (fatCount.count(*it) + 1);
    }

    return divisores;
}

int main(void){

    int qtdCasos;
    cin >> qtdCasos;

    while(qtdCasos--){
        // Lendo os numeros limitantes
        long lower, upper;
        cin >> lower >> upper;
        
        primeFactors(lower);
        long maisInteressante = lower;
        long qtdDivisores     = getQtdDivisores();

        for(long i = lower + 1; i <= upper; i++){
            cout << "gcd de " << i << " e " << maisInteressante << " eh " << gcd(i, maisInteressante) << endl;
        }

        /**for(long i = lower; i <= upper; i++){
          

            if(qtdDivisores == -1 || divisores > qtdDivisores){
                maisInteressante  = i;
                qtdDivisores      = divisores;
            }
        }**/

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