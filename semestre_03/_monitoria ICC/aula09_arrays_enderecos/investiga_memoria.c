#include <stdio.h>

int main (void) {

	char a = 'M';

	char* end = &a;

	for (int byte = 0; byte < 7000; byte++) {
		printf("%c ", *(end+byte));
	}
	printf("\n");
	

	return 0;
}
