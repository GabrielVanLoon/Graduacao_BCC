/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 01	Usando Estruturas de Dados
 */

/** 
 * Exercicio 01 
 * A sequence of brackets is called balanced if one 
 * can turn it into a valid math expression by adding characters«+» and «1». 
 * For example, sequences «(())()», «()» and «(()(()))» are balanced, while 
 * «)(», «(()»and «(()))(» are not.
 * 
 * You are given a string which consists of opening and closing round brackets. 
 * Check whether it is a balancedbracket sequence.
 */
#include <iostream>
#include <stack>

using namespace std;

int main(){
	
	stack<char> open;
	string      expr;
	
	cin >> expr;
	
	for(int i = 0; i < (int) expr.size(); i++){
		// Caso 1: Abrindo novo Bracket
		if(expr[i] == '(') open.push('(');
		// Caso 2: fechando um bracket
		else if(expr[i] == ')' && !open.empty()) open.pop();
		// Caso 3: Fechando bracket que não foi aberto >> Erro.
		else if(expr[i] == ')' && open.empty()) {
			cout << "NO" << endl;
			return 0;
		}
	}
	
	if(open.empty()) cout << "YES" << endl; // Os parenteres estão balancedaos
	else cout << "NO" << endl;
	
	return 0;
}
