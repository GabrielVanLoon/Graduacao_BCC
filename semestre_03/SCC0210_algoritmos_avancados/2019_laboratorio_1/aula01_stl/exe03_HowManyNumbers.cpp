/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 01	Usando Estruturas de Dados
 */

/** 
 * Exercicio 03 
 * You are given an array A of n positive integers A​i, 1 ≤ i ≤ n,  1 ≤ A​i​ ≤ 10​9​.
 * Find outhow many different integers A contains. For example 
 * A = {1, 3, 2, 4, 1, 1, 3, 2} has 4 different integers in it (1, 2, 3 and 4).
 */
#include <iostream>
#include <unordered_set>

using namespace std;

int main(){
	
	int 				n, aux;
	unordered_set<int> 	nums;

	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> aux;
		nums.insert(aux);
	}

	cout << nums.size() << endl;
	
	return 0;
}
