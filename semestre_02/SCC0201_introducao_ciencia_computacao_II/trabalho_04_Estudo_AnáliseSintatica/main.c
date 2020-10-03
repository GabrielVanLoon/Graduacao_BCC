/**
 * Título: Estudo de um Algoritmo de Derivação Top-Down "LL"
 * Autor:  Gabriel Van Loon
 *
 * MOTIVAÇÃO DO PROJETO
 * O trabalho 4 do projeto de ICC 2 demandava a criaçao do seguinte projeto: 
 *
 * "Implemente um programa que, dado uma sequˆencia de prioridades de operadores 
 * e uma lista de expressões aritméticas, verifique se estas são expressões 
 * válidas e imprima todos os resultados na tela caso positivo, montando uma
 * árvore de resolução das operações."
 *
 * O projeto podia ser solucionado utilizando uma Árvore binária e uma pilha,
 * porém eu havia recentemente lido o livro "Conceitos de Linguage de Programação"
 * e decidi colocar em práticas meu conhecimento recém adquirido de Análise
 * Sintáticas e implementação de BNF Extendida (Formas de Backus-Naur).
 * 
 * Portanto, a pasta "trabalho_04_Expressoes..." possui esse mesmo projeto
 * já modificado para atender às neceddidades do trabalho, enquanto neste projeto
 * está implementado um leitor de expressões matemáticas que respeita a ordem
 * de interpretação que normalmente se utiliza no dia à dia.
 *
 * Para ver as regras de BNF Extendida gerada, vá no arquivo mathparser.h e leia
 * a sua documentação escrita nos comentários.
 */
#include <stdlib.h>
#include <stdio.h>
#include "mathparser.h"

int main(void){

	Sequencia seq;
	char stmt[100] = "log{2**(5+21/7)}+exp[3]";
	int erro;
	float result;

	if(!analiseLexica(stmt, &seq))
		printSequencia(&seq);
	else
		printf("Ocorreu algum erro na análise Léxica\n");


	result = analiseSintatica(&seq, &erro);

	if(erro == 0)
		printf("\n\nResultado: %.03f\n", result);
	else
		printf("\n\nOcorreu um erro!\n");



	return 0;
}