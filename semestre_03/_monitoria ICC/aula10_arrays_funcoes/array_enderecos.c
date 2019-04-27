#include <stdio.h>

int main (void) {


	char A[6] = {'M', 'o', 'a', 'c', 'i', 'r'};

	// A       - char*
	// A[0]    - char    'M'
	// *A	   - char    'M'

	// A[3]    - char    'c'
	// (A+3)   - char*   endereco de A deslocado em 3 bytes
	//*(A+3)   - char    'c'

	for (int i = 0; i < 6; i++) {
		printf("%p\n", (A+i)); // char*
	}

	for (int i = 0; i < 6; i++) {
		printf("%c\n", *(A+i)); // char
	}


	for (int i = 0; i < 6; i++) {
		scanf("%c", &A[i]);
		//scanf("%c", A+i);
	}

	for (int i = 0; i < 6; i++) {
		printf("%c\n", *(A+i)); // char
	}


	return 0;
}
