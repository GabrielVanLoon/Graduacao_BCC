#include <stdio.h>

int main (void) {

	int x = 259;
	// em binario esse numero e' organizado em 32 bits
	// em blocos de 8 em 8 bits (byte a byte) ficaria:
	// 00000000 00000000 00000001 00000011

	printf("Endereco e valor da variavel inteira:\n");
	printf("%p, %d\n", &x, x);

	// como estamos em um sistema little endian,
	// na memoria temos do menos para o mais significativo
	// 00000011 - primeiro bloco (menos significativo)
	// 00000001 - segundo bloco
	// 00000000 - terceiro
	// 00000000 - quarto

	char* end_x = (char*) &x;

	printf("Acessando byte a byte (primeiro enderecos, depois valores):\n");
	// acessando um inteiro, byte a byte (via char*)
	printf("%p\n", (end_x));
	printf("%p\n", (end_x+1));
	printf("%p\n", (end_x+2));
	printf("%p\n", (end_x+3));

	// acessando um inteiro, byte a byte (via char*)
	printf("%d\n", *(end_x));
	printf("%d\n", *(end_x+1));
	printf("%d\n", *(end_x+2));
	printf("%d\n\n", *(end_x+3));


	printf("Agora acessando um double de 4 em 4 bytes (via int*):\n");
	double y = 6510231023.11;
	
	printf("Endereco e valor do double: %p, %lf\n", &y, y);
	int* end_y = (int*) &y;
	for (int s = 0; s < 2; s++) {
		printf("%p %d\n", (end_y+s), *(end_y+s));
	}

	
	printf("\n\n");
	printf("Agora acessando um long int de 4 em 4 bytes (via int*):\n");
	long int z = 61510231023;
	
	printf("Endereco e valor do long int: %p, %ld\n", &z, z);
	int* end_z = (int*) &z;
	for (int s = 0; s < 2; s++) {
		printf("%p %d\n", (end_z+s), *(end_z+s));
	}




	return 0;
}
