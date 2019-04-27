#include <stdio.h>

int main (void) {

	int A[3] = {0, 1, 3};

	//  A   =   endereco (excecao - nao consegue retornar um valor)
	// &A   =   mesmo
	// &A[0]=   mesmo

	int* endA = A; // aqui armazena o endereco de A, por ser um array

	// endA = endereco (int *)
	//*endA = pega endereco e retorna o valor dentro dele
	// 	  nesse caso seria o valor 0, o primeiro do array

	printf("Endereco\t Valor\n");
	for (int i = 0; i < 3; i++) {
		printf("%p\t %d\n", &A[i], A[i]);
	}
	printf("\n");

	printf("Endereco da variavel endA: %p\n", &endA);
	printf("Valor da variavel endA: %p\n", endA);
	printf("Somando...\n");
	printf("+0 %p\n", endA+0);
	printf("+1 %p\n", endA+1);
	printf("+2 %p\n", endA+2);
	printf("+3 %p\n", endA+3);

	printf("Valores (inteiros) nos enderecos...\n");
	printf("*(+0) %d\n", *(endA+0)); // 0
	printf("*(+1) %d\n", *(endA+1)); // 1
	printf("*(+2) %d\n", *(endA+2)); // 3
	printf("*(+3) %d\n", *(endA+3)); // o que acontece aqui?

	// operadores & e * sao 'duais'
	printf("Operadores & e * sao duais: \n");
	printf(" *(&(*(+2))) %d\n",   *(&(*(endA+2))));

	printf("\n");

	return 0;
}
