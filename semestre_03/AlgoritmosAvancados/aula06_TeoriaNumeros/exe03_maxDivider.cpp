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

    // Código para testar a exibição dos fatores
    primeFactors(179);
    set<int>::iterator it;
    for(it = fatores.begin(); it != fatores.end(); it++){
        cout << *it << "^" << fatCount.count(*it) << " ";
    } cout << endl;

    primeFactors(1059);
    for(it = fatores.begin(); it != fatores.end(); it++){
        cout << *it << "^" << fatCount.count(*it) << " ";
    } cout << endl;

     primeFactors(1417);
    for(it = fatores.begin(); it != fatores.end(); it++){
        cout << *it << "^" << fatCount.count(*it) << " ";
    } cout << endl;

    primeFactors(2312);
    for(it = fatores.begin(); it != fatores.end(); it++){
        cout << *it << "^" << fatCount.count(*it) << " ";
    } cout << endl;

    return 0;
}







// Código para testar a exibição dos fatores
//primeFactors(100000);
//set<int>::iterator it;
//for(it = fatores.begin(); it != fatores.end(); it++){
//    cout << *it << "^" << fatCount.count(*it) << " x ";
//}