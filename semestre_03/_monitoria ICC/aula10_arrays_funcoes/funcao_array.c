/* Programa controla um array de 5 elementos do tipo float
	e contem funcoes para:
	- fazer a entrada (via teclado) dos elementos
	- imprimir os elementos (saida)
	- calcular a soma dos elementos
*/
#include <stdio.h>

// variavel GLOBAL - escopo em todo o codigo fonte
// float lista[5];
// NAO USAR

// funcao que imprime na tela os 5 valores
// do array lista
void saida(float* l) {
	for (int a = 0; a < 5; a++) {
		printf("%.3f ", l[a]);
	}
	printf("\n");
}

// funcao que permite ao usuario digitar os 5 valores
// para o array lista
void entrada(float* l) {
	printf("Digite 5 numeros float:\n");
	for (int i = 0; i < 5; i++) {
		scanf("%f", &l[i]);
	}
}

// funcao que calcula a soma dos elementos
// do array lista
// retorna a soma como um valor float
float soma(float* l, int N) {
	float var_soma = 0.0;
	for (int y = 0; y < N; y = y + 1) {
		var_soma = var_soma + l[y];
	}
	return var_soma;
}


/* SEMPRE a funcao main sera a primeira a ser executada
	as outras devem ser chamadas explicitamente a partir
	da main
*/
int main (void) {

	float var_soma = 0;
	float lista[5];

	// lista e' um endereco, e portanto posso usar
	// o tipo float*

	entrada(lista);
	saida(lista);

	var_soma = soma(lista, 5);
	printf("Soma = %.3f\n", var_soma);

	return 0;
}
