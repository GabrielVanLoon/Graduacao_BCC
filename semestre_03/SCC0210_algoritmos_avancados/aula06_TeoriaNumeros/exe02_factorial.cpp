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
void primeFactors(int n) { 
    fatores.clear();
    fatCount.clear();

    while (n%2 == 0){ 
        fatores.insert(2);
        fatCount.insert(2);
        n = n/2; 
    } 
  
    for (int i = 3; i <= sqrt(n); i = i+2) { 
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

    int n, m;
    while(cin >> n >> m){
        
        bool divide = true;
        primeFactors(m);
        
        set<int>::iterator it;
        for(it = fatores.begin(); it != fatores.end(); it++){
            int maxPot = 0;
            for(long int i = *it; i <= n; i *= (*it) ){
                if(i > 2147483648) break; // Limitando o iterador para não dar Overflow acima de 2^31
                maxPot += (n/i);
            }

            if( (int) fatCount.count(*it) > maxPot){
                divide = false;
                break;
            }
        }
       
        if(divide)
            cout << m << " divides " << n << "!" << endl;
        else 
            cout << m << " does not divide " << n << "!" << endl;
    }

    return 0;
}







// Código para testar a exibição dos fatores
//primeFactors(100000);
//set<int>::iterator it;
//for(it = fatores.begin(); it != fatores.end(); it++){
//    cout << *it << "^" << fatCount.count(*it) << " x ";
//}