/**
 * Trabalho de Introdução a Ciencia da Computacao II
 * Título: T4 - Calculadora de Expressoes Aritmeticas
 * Autor:  Gabriel Van Loon
 * Prof.:  Moacir Ponti
 * Data:   Outubro/2018
 *
 * RESUMO
 * Implemente um programa que, dado uma sequˆencia de prioridades de operadores 
 * e uma lista de expressões aritméticas, verifique se estas são expressões 
 * válidas e imprima todos os resultados na tela caso positivo, montando uma
 * árvore de resolução das operações.

 * DESCRIÇÃO
 * - Nas primeiras cinco linhas, o programa recebera a ordem de prioridade dos
 *   5 seguintes sinais aritméticos: {+, -, *, /, **}

 * - Em seguida, uma sequência de expressões matemáticas para serem resolvidas 
 *   pelo programa no seguinte formato: 
 *		<expr1>, 
 *		<expr2>,
 *		... 
 *		<exprN>;

 * - Para cada <expr>, irá imprimir o resultado ou retornar erro caso haja algum
 *   erro léxico, sińtático ou mais expecífico como raíz/log de número negativo.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mathparser.h"

int main(void){

	Sequencia seq;
	char stmt[1064], endl = ',';
	float result;
	int erro;

	// Lendo a Ordem dos Operadores
	ordenarOperadores(&seq);

	do{
		scanf("%1060[^,;]", stmt);
		scanf("%c",         &endl);

		// Ajustando os lexemas
		if(analiseLexica(stmt, &seq)){
			printf("Expressao incorreta.\n");
			continue;
		}

		// Monta a ParseTree e retorna o valor da expressão
		result = analiseSintatica(&seq, &erro);

		// Como queremos uma precisao de apenas dois digitos...
		result = (fabs(result) >= 0.01) ? result : 0;

		if(erro == 0)
			printf("%.02f\n", result);
		else
			printf("Expressao incorreta.\n");

		// Liberando variavel para o proximo loop
		liberarSequencia(&seq);

	} while(endl == ',');


	return 0;
}