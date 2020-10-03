/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    mar/2018
 * Aula 06	Teoria dos Numeros
 */

/** 
 * Exercicio 05 - Divisivel por 131071
 * UVA 10176
 * Recebe um numero binário gigante por linha e diz se ele é multiplo de 131.071
 */
#include <iostream>
#include <set>

using namespace std;

void calcularBit(int* num, char bit, int mod){
    if(bit == '0')
        *num = ((*num) * 2) % mod;
    else if(bit == '1')
        *num = ( ((*num) * 2) + 1) % mod;
}

int main(){
    int  primo = 131071;
    int  numero;
    char bit;

    while(cin >> bit){
        numero = 0;

        do{
            calcularBit(&numero, bit, primo);
            cin >> bit;
        } while(bit != '#');

        if(numero == 0) // Eh divisivel por @primo
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

    }

    return 0;
}