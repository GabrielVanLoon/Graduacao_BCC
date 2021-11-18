/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    mar/2018
 * Aula 06	Teoria dos Numeros
 */

/** 
 * Exercicio 01 - Usando Crivo de Eratóstenes (Sieve of Eratosthenes)
 * UVA 10235 - Simply Emirp
 */
#include <iostream>
#include <stack>
#include <bitset>

using namespace std;

bitset<10000000> ehPrimo; // Faz o crivo para ehPrimo de ordem até 10^6

void crivo(){
    // Marca todos os primos como verdadeiro e percorre 
    // de {2....sqrt(n)} marcando os não primos.
    // Se i já foi marcado como não primo então não precisa
    // fazer o segundo loop.
    ehPrimo.set(); 
    ehPrimo.set(0, false);
    ehPrimo.set(1, false);
    for(int i = 2; (i*i) < (int) ehPrimo.size(); i++){ // Percorre 
        if(!ehPrimo[i]) continue;
        for(int j = (i*i); j < (int) ehPrimo.size(); j += i){
            ehPrimo.reset(j);
        }
    }
}

int inverteNumero(int x){
    int y = 0;

    while(x >= 10){
        y += x % 10;
        y *= 10;
        x /= 10;
    }
    y += x % 10;
    return y;
}

int main(void){
    crivo();
    
    //for(int i = 1000000; i < 10000000; i++)
    //    cout << i << " eh primo: " << ehPrimo[i] << endl;
    
    int num, mun;
    while(cin >> num){
        mun = inverteNumero(num);
        if(!ehPrimo[num]){
            cout << num << " is not prime." << endl;
        } else if(mun == num || !ehPrimo[mun]){
            cout << num << " is prime." << endl;
        } else {
             cout << num << " is emirp." << endl;
        }

    }

    return 0;
}


