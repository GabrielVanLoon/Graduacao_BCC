/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex04. 	Cálculo de Derivada e Reta Tangente
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * O programa recebe uma coordenada (X,Y) chamada P e, em seguida, os termos
 * de uma função polinomial f(x). Com esses ados ele retorna qual é a função
 * derivada f'(x) e a reta tangente à f no ponto f(P).
 * 
 * Obs.: Para essa atividade era obrigatório o uso de Pilhas na resolução.
 */
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

/**
 * Typedef Boolean
 * - Abstracao do tipo de dados Booleano
 */
typedef char Boolean;
# define TRUE 1
# define FALSE 0

/**
 * Typedef Termo
 * - Abstracao dos termos de um polinomio
 */
typedef struct {
	long long coef;
	long long expo;
}Termo;

/**
 * Typedef Pilha
 * - Implementacao de uma estrutura de dados do tipo Pilha
 */
typedef struct {
	int qtdElementos;
	Termo* pilha;
}Pilha;

// Funcoes estruturais da TAD Pilha
	void criarPilha(Pilha* p){
		p->qtdElementos = 0;
		p->pilha = NULL;
	}
	
	void destruirPilha(Pilha* p){
		if(p->pilha != NULL) free(p->pilha);
		p->qtdElementos = 0;
		p->pilha = NULL;
	}
	
	void inserirElemento(Pilha* p, Termo t){
		p->qtdElementos++;
		p->pilha = (Termo*) realloc(p->pilha, p->qtdElementos*sizeof(Termo));
		p->pilha[p->qtdElementos-1] = t;
	}
	
	Termo retirarElemento(Pilha* p){
		Termo t = p->pilha[p->qtdElementos-1];
		p->qtdElementos--;
		p->pilha = (Termo*) realloc(p->pilha, p->qtdElementos*sizeof(Termo));
		return t;
	}
	
	Boolean estaVazia(Pilha* p){
		return (p->qtdElementos > 0) ? FALSE : TRUE;
	}

// Funcoes estruturais da TAD Termo
	void mostrarFuncao(Pilha* p, char prefix[5]){
		int aux = 0;
		
		printf("%s(x) =", prefix);
		
		while(!estaVazia(p)){
			
			Termo term = retirarElemento(p);
			
			// Caso coeficiente seja nulo ignore
			if(term.coef == 0) continue;
			
			// Sinal 
			if( aux++ == 0 && term.coef >= 0){
				printf(" ");
			} else {
				if(term.coef < 0) printf(" - ");
				else printf(" + ");
			}
			
			// Coeficiente
			if(term.expo > 0) printf("%lldx", llabs(term.coef));
			else printf("%lld", llabs(term.coef));
			
			// Expoente
			if(term.expo > 1) printf("^%lld", term.expo);
		}
	}
	
	long long calcularTermo(Termo t, long long x){
		return t.coef * pow(x, t.expo);
	}
	
int main(void){
	
	/**
	 * Variáveis:
	 * @f:				Funcao f(x)
	 * @df:				Funcao f'(x)
	 * @g:				Funcao g(x) tangente a f(x) em (pto, f(pto))
	 * @pto: 			Ponto de tangencia entre f(x) e g(x)
	 * @coefAngular:	Coenficiente angular de f(x) quando x = pto
	 * @term:			Variavel auxiliar para leitura de entradas
	 */
	int pto;
	long long fpto = 0, coefAngular = 0; 
	Termo term; 
	Pilha f, df, g;
	
	criarPilha(&f);
	criarPilha(&df);
	criarPilha(&g);
	
	// Lendo o ponto de tangencia e os termos de f(x)
	scanf("%d", &pto);
	while(scanf("%lld", &term.coef) != EOF){
		scanf("%lld", &term.expo);
		inserirElemento(&f, term);
	}
	
	// Remove os termos de f(x), calculando sua derivada e inserindo em f'(x)
	// Alem disso, calcula o valor do coef. Angular e tambem de f(pto)
	while(!estaVazia(&f)){
		
		term = retirarElemento(&f);
		
		// Calculando um termpo de f(pto)
		fpto += calcularTermo(term, pto);
		
		if(term.expo > 0){
			term.coef  = term.coef * term.expo;
			term.expo -= 1;
			
			// Calculando o valor do coef ou f'(pto)
			coefAngular += calcularTermo(term, pto);
			
			inserirElemento(&df, term);
		}
	
	}
	
	// Definindo a funcao g(x) da relacao abaixo:
	// 	 (Y-Y0) = Mi(X-X0) => Y = g(x) = Mx -M*X0 +Y0
	Termo a, b;
	a.coef = coefAngular;
	a.expo = 1;
	
	b.coef = (-1*coefAngular*pto) + fpto;
	b.expo = 0;
	
	inserirElemento(&g, b);
	inserirElemento(&g, a);
	
	// Exibindo a funcao f'(x)
	mostrarFuncao(&df, "f'\0");
	printf("\n");
	
	// Exibindo a funcao g(x)
	mostrarFuncao(&g, "g\0");
	printf("\n");
	
	destruirPilha(&f);
	destruirPilha(&df);
	destruirPilha(&g);
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
