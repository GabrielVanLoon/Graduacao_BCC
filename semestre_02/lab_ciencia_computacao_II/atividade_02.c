/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex02 	Operacoes Basicas com Super Numeros
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * Linguagens de programação normalmente possuem um limite nos valores que suas
 * variáveis numéricas podem assumir. Porém em pesquisas e usos comerciais é comum
 * a necessidade de utilizar grandes números que ultrapassam esses limites.
 *
 * O código abaixo implementa um novo tipo de dado que permita realizar as 4
 * operações básicas com números grandes.
 *
 * Para cumprir seu objetivo, a implementãção quebra um grande número em blocos
 * de 10^4, sendo esse valor ajustável.
 *
 * Obs.: O código está implementado em arquivo único, mas pode facilmente ser
 *       portado para um arquivo .h e .c
 */
 
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define TAMANHO_BLOCO 4

int _ehNumero(char a){
	if(a >= 48 && a <= 57)
		return 1;
	return 0;
}

int potencia(int a, int b){
	int p = 1;
	for(int i = 1; i <= b; i++)
		p = p * a;
	return p;
}

typedef struct _superInt{
	int* blocos;
	int qtdBlocos;
	char isPositivo;
}SuperInt;

SuperInt iniciarSuperInt(){
	SuperInt s;

	s.blocos = NULL;
	s.qtdBlocos = 0;
	s.isPositivo = 's';

	return s;
}

void destruirSuperInt(SuperInt* s){
	if(s->blocos != NULL)
		free(s->blocos);
}

void _adicionarBloco(SuperInt* s, int valor){

	s->qtdBlocos += 1;
	s->blocos = (int*) realloc(s->blocos, s->qtdBlocos * sizeof(int) );
	s->blocos[s->qtdBlocos-1] = valor;
}

void _limparBlocos(SuperInt* s){

	int i = s->qtdBlocos - 1;
	while(i >= 0 && s->blocos[i] == 0){
		s->qtdBlocos -= 1;
		s->blocos = (int*) realloc(s->blocos, s->qtdBlocos * sizeof(int));
		i--;
	}
}

void mostrarSuperInt(SuperInt s){
	if(s.isPositivo == 'n')
		printf("-");

	for(int i = s.qtdBlocos-1; i >= 0; i--){
		if( i == s.qtdBlocos-1)
			printf("%d", s.blocos[i]);
		else
			printf("%04d", s.blocos[i]); // 0 - TAMANHO_BLOCO
	}
	printf("\n");
}

int _maiorSuperInt(SuperInt a, SuperInt b){

	if(a.isPositivo == 's' && b.isPositivo == 'n') return 1;
	else if(a.isPositivo == 'n' && b.isPositivo == 's') return -1;

	if(a.qtdBlocos == b.qtdBlocos ){

		int valor_a = a.blocos[a.qtdBlocos-1];
		int valor_b = b.blocos[b.qtdBlocos-1];

		if( valor_a == valor_b ) return 0;
		else if( valor_a > valor_b) return 1;
		else return -1;

	} else if( a.qtdBlocos > b.qtdBlocos ){
		return 1;
	} else {
		return -1;
	}
}

void lerSuperInt(SuperInt* s){
	
	char* entrada;
	size_t max = 100;
	size_t lidos;
	int qtdBlocos;

	// Alocando um array de char temporario para salvar o numero.
	entrada = (char*) malloc(max * sizeof(char));

	// lidos retorna quantos caracteres foram inseridos na string
	lidos = getline(&entrada, &max, stdin);
	// lidos = lidos-1; // Ignorando o \0
	lidos = lidos-2; // Fix: Run-codes esta adicionando algo alem do \0 e \n

	// Definindo a quantidade de blocos
	qtdBlocos = (lidos) / TAMANHO_BLOCO;
	if( (lidos % TAMANHO_BLOCO) > 0 )
		qtdBlocos += 1;

	// Dividindo os numeros em blocos de TAMANHO_BLOCO
	int k = lidos - 1; // printf("  %d >> %c \n", k, entrada[k]);
	for(int i = 0; i < qtdBlocos; i++){

		int valor = 0;
		for(int j = 0; j < TAMANHO_BLOCO; j++)
			if(k >= 0){
				char c = entrada[k--];
				valor += atoi(&c) * potencia(10, j);
			}   
		
		_adicionarBloco(s, valor);
	}

	free(entrada);
}

SuperInt somarSuperInt(SuperInt a, SuperInt b){

	SuperInt maior, menor;
	SuperInt resultado = iniciarSuperInt();

	if(_maiorSuperInt(a,b) == 1){
		maior = a; menor = b;
	} else {
		maior = b; menor = a;
	}

	// Inserindo os valores do menor numero no maior
	int i = 0, carry = 0, soma;
	for(i = 0; i < menor.qtdBlocos; i++){

		soma  = (menor.blocos[i] + maior.blocos[i] + carry) % potencia(10, TAMANHO_BLOCO);
		carry = (menor.blocos[i] + maior.blocos[i] + carry) / potencia(10, TAMANHO_BLOCO);

		_adicionarBloco(&resultado, soma);
	}

	// Adicionaod os blocos restantes do numero maior
	for( ; i < maior.qtdBlocos; i++){
		soma  = (maior.blocos[i] + carry) % potencia(10, TAMANHO_BLOCO);
		carry = (maior.blocos[i] + carry) / potencia(10, TAMANHO_BLOCO);

		_adicionarBloco(&resultado, soma);
	}
	return resultado;
}

SuperInt subtrairSuperInt(SuperInt a, SuperInt b){

	SuperInt maior, menor;
	SuperInt resultado = iniciarSuperInt();

	if(_maiorSuperInt(a,b) == 1){
		maior = a; menor = b;
	} else {
		maior = b; menor = a;
		resultado.isPositivo = 'n';
	}

	// Inserindo os valores do menor numero no maior
	int i = 0, carry = 0, subtr;
	for(i = 0; i < menor.qtdBlocos; i++){		

		// O numero que vai ser subtraido eh menor, entao faz o carry
		if(maior.blocos[i] < menor.blocos[i]){
			subtr = (maior.blocos[i] + potencia(10, TAMANHO_BLOCO) - menor.blocos[i] - carry) % potencia(10, TAMANHO_BLOCO);
			carry = 1;
		}
		else {
			subtr = (maior.blocos[i] - menor.blocos[i] - carry) % potencia(10, TAMANHO_BLOCO);
			carry = 0;
		}

		_adicionarBloco(&resultado, subtr);
	}

	// Adicionaod os blocos restantes do numero maior
	for( ; i < maior.qtdBlocos; i++){
		
		// O numero que vai ser subtraido eh menor, entao faz o carry
		if( maior.blocos[i] - carry < 0 ){
			subtr = (maior.blocos[i] + potencia(10, TAMANHO_BLOCO) - carry) % potencia(10, TAMANHO_BLOCO);
			carry = 1;
		}
		else {
			subtr = (maior.blocos[i] - carry) % potencia(10, TAMANHO_BLOCO);
			carry = 0;
		}

		_adicionarBloco(&resultado, subtr);
	}
	return resultado;
}

int dividirSuperInt(SuperInt a, SuperInt b){

	int resultado = 0;

	while(_maiorSuperInt(a,b) == 1) {
		a = subtrairSuperInt(a,b);
		_limparBlocos(&a);
		resultado++;
	}

	return resultado;
}

SuperInt multiplicarSuperInt(SuperInt a, SuperInt b){

	SuperInt resultado = iniciarSuperInt();
	int colunas = a.qtdBlocos; //   a
 	int linhas =  b.qtdBlocos; // x b

	long int matriz_soma[linhas][colunas];

	// Multiplicando cada elemento de A pelos N elementos de B e gerando
	// a matriz das somas. Pior caso: 99.999x99.999 = 9.999.800.001
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			matriz_soma[i][j] = (long int) b.blocos[i] * a.blocos[j];
		}
	}

	//Mostrar a matriz
	/*for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			printf("%ld ", matriz_soma[i][j]);
		}
		printf("\n");
	}*/

	// Somar a matriz em diagonais
	int l = 0, c = 0;
	long int carry = 0;
	while(l < linhas && c < colunas){
		
		int i = l, j = c;
		long int soma = matriz_soma[i++][j--];

		while( i < linhas && j >= 0 ){
			soma += matriz_soma[i++][j--];
		}

		soma  += carry;
		carry = soma / potencia(10, TAMANHO_BLOCO);

		_adicionarBloco(&resultado, soma % potencia(10, TAMANHO_BLOCO));

		if( (c+1) < colunas )
			c++;
		else
			l++;
	}

	if(carry > 0)
		_adicionarBloco(&resultado, carry);

	return resultado;
}

int main(void){

	SuperInt x, y, r;
	int div;
	char operacao[20];

	x = iniciarSuperInt();
	y = iniciarSuperInt();
	r = iniciarSuperInt();

	scanf("%[^\n]", operacao); getchar();
	lerSuperInt(&x);
	lerSuperInt(&y);

	if(operacao[0] == 'S' && operacao[1] == 'O' && operacao[2] == 'M'){
		r = somarSuperInt(x, y);
		mostrarSuperInt(r);
	
	} else if(operacao[0] == 'S' && operacao[1] == 'U' && operacao[2] == 'B'){
		r = subtrairSuperInt(x, y);
		mostrarSuperInt(r);
	
	} else if(operacao[0] == 'M' && operacao[1] == 'U' && operacao[2] == 'L'){
		r = multiplicarSuperInt(x, y);
		mostrarSuperInt(r);

	} else if(operacao[0] == 'D' && operacao[1] == 'I' && operacao[2] == 'V'){
		div = dividirSuperInt(x, y);
		printf("%d\n", div);
	}

	destruirSuperInt(&x);
	destruirSuperInt(&y);
	destruirSuperInt(&r);

	return 0;
}
