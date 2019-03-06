/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 02	Usando Estruturas de Dados II
 * 
 * Pdf da aula: http://www.lcad.icmc.usp.br/~jbatista/scc210/Aula3-STL2.pdf
 */

/** 
 * Exercicio 01
 * You have an array 'a' consisting of 'n' integers. Each integer from 1 to 'n' 
 * appears exactly once in this array.
 * 
 * For some indices 'i' (1 ≤ i ≤ n ­ 1) it is possible to swap i-th element with (i + 1)-th, 
 * for other indices it is not possible. You may perform any number of swapping operations 
 * any order. There is no limit on the number of times you swap i-th element with (i + 1)-th 
 * (if the position is not forbidden).
 * 
 * Can you make this array sorted in ascending order performing some sequence of swapping operations?
 * 
 * Ref.:https://codeforces.com/problemset/problem/920/C
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <vector>

using namespace std;

int main(){

    vector<int>     numeros;    // Max. 2*10⁴
    bitset<20000>   swaps;      // 1 - can swap | 0 - can't swap
    string          seq;        // Sequencia de 0's e 1's
    int n;                      // Tam. do array
    int aux;

    // Lê o tamanho do array.
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> aux;
        numeros.push_back(aux);
    }

    // Lendo indices que podem fazer swap
    cin >> seq;
    for(int i = 0; i < n-1; i++)
        swaps[i] = (seq[i] == '1') ? true : false;
    swaps[n-1] = false;

    /**
     * Veja que a sequencia 110101110 pode ser quebrada em seq. menores 110, 10, 1110.
     * Pois à direita de um zero não é possivel fazer mais nenhuma troca.
     * Basta então ordenar essas sequencias e verificar
     * se o menor valor do conj. Ai é maior do que o maior valor do conj. Ai-1
     */
    int iniConj          = 0;
    int qtd              = 1;
    int anterior         = -1;
    bool podeSerOrdenado = true;
    
    for(int i = 0; i < n; i++){
        if(swaps.test(i) == true){
            qtd++;
        } else {
            // Ordena o conjunto 111...10
            sort(numeros.begin()+iniConj, numeros.begin()+iniConj+qtd);

            if(numeros[iniConj] < anterior){
                podeSerOrdenado = false;
                break;
            }

            // Resetando o teste para o prox conjunto
            iniConj  = i+1;
            qtd      = 1;
            anterior = numeros[i];
        }
    }

    if(podeSerOrdenado) cout << "YES" << endl;
    else cout << "NO" << endl;
}
