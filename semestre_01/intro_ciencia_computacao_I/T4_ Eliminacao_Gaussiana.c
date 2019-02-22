/**
 * Trabalho de Introdução a Ciencia da Computacao
 * Título: Verificar colisao de objetos no espaço vetorial
 * Autor:  Gabriel Van Loon
 * Prof.:  Moacir Ponti
 * Data:   junho/2018
 * 
 * Descricao:
 *    Dada a equacao de dois objetos no espaco (plano ou reta), verifica
 * se ocorre a colisao entre eles.
 *    O plano eh representado por meio de sua equacao geral, e a reta eh
 * representada como a interseccao da eq. geral de dois planos.
 *    Para isso, o sistema realiza o processo recursivo de escolanamento
 * (eliminacao gaussiana) em busca de absurdos* nas equacoes.
 *    
 *    *Absurdo: ocorre quando todos os coeficientes sao nulos, menos o ultimo.
 * 
 * Entradas:
 * 		@qtd_eq: 	Quantidade de equacoes do sistema.
 * 		@qtd_coef: 	Quant. de coeficientes das equacoes gerais dos planos.
 * 		@sistema:	Matriz com 1 eq. geral por linha.
 * 
 * Saida:
 * 		@colisao:	'sim' ou 'nao' ha colisao.
		@sistema:   Matriz escalonada com 1 eq. geral por linha
 */
# include <stdio.h>
# include <stdlib.h>

typedef struct _racional{
	int a; // Numerador  
	int b; // Denominador
} Racional;

 /**
  * Funcao: alocarSistema
  * 
  *   A funcao aloca dinamicamente uma matriz de numeros racionais na
  * memoria Heap.
  * 
  * Variaveis:
  * 	@l: Quantidade de linhas da matriz
  * 	@c: Quantidade de colunas da matriz
  * 
  * Retorno
  * 	@ptrMatrix: Endereco da matriz na memoria Heap.
  */
 
Racional** alocarSistema(int l, int c){

	// Array que ira referenciar cada uma das linhas
	Racional** ptrMatrix = (Racional**) malloc(l * sizeof(Racional*));

	// Alocando as linhas
	for(int j = 0; j < l; j++)
		ptrMatrix[j] = (Racional*) malloc(c * sizeof(Racional));
		
	return ptrMatrix;
}

 /**
  * Funcao: desalocarSistema
  * 
  *   A funcao desaloca a matriz gerada pela funcao alocarSistema().
  * 
  * Variaveis:
  * 	@ptrMatrix: Endereco da matriz na memoria Heap.
  * 	@l: Quantidade de linhas da matriz
  * 	@c: Quantidade de colunas da matriz	
  */
  
void desalocarSistema(int l, int c, Racional** ptrMatrix){
	
	// Desalocando as linhas
	for(int j = 0; j < l; j++)
		free(ptrMatrix[j]);
	
	free(ptrMatrix);
}

 /**
  * Funcao: preencherEquacao
  * 
  *    Preenche um array cujas posicoes representam os valores dos coef.
  * de uma equacao geral. Ex:
  * 
  * 	p: Ax + By + Cz + D = 0
  * 	p = {A, B, C, D}, 4 coeficientes.
  * 
  * Variaveis:
  * 	@qtd_coef:	Quantidade de coeficientes na equacao
  * 	@r: 		Endereco do array que ira armazenar os valores
  */
  
void preencherEquacao(int qtd_coef, Racional* r){

	for(int j = 0; j < qtd_coef; j++){
		scanf("%d", &r[j].a);
		scanf("%d", &r[j].b);
	}

}

 /**
  * Funcao: calcularMMC()
  * 
  *    Dado dois inteiros, encontra o menor numero multiplo de ambos
  * 
  * Variaveis:
  * 	@num1:	Primeiro numero
  * 	@num2: 	Segundo numero
  * 
  * Retorno:
  * 	@mmc
  */
  
int calcularMMC(int num1, int num2){
	
	int maior_num = (num1 > num2) ? num1 : num2;
	int mmc = maior_num;

	while( (mmc % num1 != 0) || (mmc % num2 != 0) ){
		mmc += maior_num;
	}
	
	return mmc;
}

 /**
  * Funcao: simplificarRacional()
  * 
  *    Verifica se o numerador eh multiplo do denominador, se sim executa
  * a simplificacao tornando o denominador em 1.
  * 	Ex: 4/2 (Nao simplificado), se torna 2/1 (Simplificado)
  * 
  * Variaveis:
  * 	@num: Racional nao simplificado
  * 
  * Retorno:
  * 	@num: Racional simplificado
  */
  
  
Racional simplificarRacional(Racional num){

	if(num.a % num.b == 0){
		num.a = num.a / num.b;
		num.b = 1;
	}
	
	return num;
}


 /**
  * Funcao: escolonarMatriz
  * 
  *    Dado uma matriz Sistema[qtd_eq][qtd_coef], realiza o processo de
  * eliminacao gausiana recursivamente, diminuindo a matriz em 1 linha e
  * 1 coluna em cada chamada.
  *    A funcao para quando a matriz se torna uma Matriz Linha, ou quando
  * a coluna inicial se torna o penultimo item (qtd_coef-2).
  * 
  * 
  * Variaveis:
  * 	@sistema:	Matriz de racionais que representa as equacoes.
  * 	@qtd_eq:	Quantidade de linhas/equacoes
  * 	@qtd_coef:	Quantidade de colunas/coeficientes
  * 	@l_ini:		Linha inicial dos loops nessa execucao
  * 	@c_ini:		Coluna inicial dos loops nessa execucao
  */
  
int escalonarMatriz(Racional **sistema, int qtd_eq, int qtd_coef, int l_ini, int c_ini){
	
	// Casos de parada
	// - Matriz linha: (l_ini+1) == qtd_eq
	// - Coluna inicial eh o penultimo coef.: (c_ini+2) == qtd_coef
	if( (l_ini+1) == qtd_eq || (c_ini+2) == qtd_coef)
		return 1;
	
	// Ajustando para que o Pivo nao seja nulo
	if(sistema[l_ini][c_ini].a == 0){	
		for(int i = l_ini+1; i < qtd_eq; i++){
			
			if(sistema[i][c_ini].a != 0){
				// Swap das equacoes
				Racional* ptrSwap = sistema[l_ini];
				sistema[l_ini] = sistema[i];
				sistema[i] = ptrSwap;
				break;
			}
			
		}
	}
	
	// Se o pivo nao for nulo, subtrai todas as linhas pela primeira 
	// multiplicadas por um fator f tal que: f = (1ª coluna da linha atual / Pivo)
	if(sistema[l_ini][c_ini].a != 0){
		
		for(int i = l_ini+1; i < qtd_eq; i++){
			
			Racional fator;
			// Af/Bf = (Ai/Bi) / (Ap/Bp) >> Divisao de racionais >> (Ai*Bp)/(Bi*Ap) 
			fator.a = sistema[i][c_ini].a * sistema[l_ini][c_ini].b;
			fator.b = sistema[i][c_ini].b * sistema[l_ini][c_ini].a;
			fator = simplificarRacional(fator);
			
			
			for(int j = c_ini; j < qtd_coef; j++){
				
				Racional sub; // Numero da primeira linha multiplicado pelo fator
				sub.a = sistema[l_ini][j].a * fator.a;
				sub.b = sistema[l_ini][j].b * fator.b;
				sub   = simplificarRacional(sub);
				
				
				// Fazendo a subtracao e gerando o novo racional
				int mmc         = calcularMMC(sistema[i][j].b, sub.b);
				
				sistema[i][j].a = (sistema[i][j].a * (mmc/sistema[i][j].b)) - (sub.a * (mmc/sub.b)); 
				sistema[i][j].b = mmc;
				sistema[i][j]   = simplificarRacional(sistema[i][j]);
				
				// sistema[i][j].a = (sistema[i][j].a * sistema[l_ini][j].b * fator.b) - (sistema[l_ini][j].a * fator.a * sistema[i][j].b);
				// sistema[i][j].b = sistema[i][j].b * sistema[l_ini][j].b * fator.b; 
				
			}
		}
		
	}
	
	return escalonarMatriz(sistema, qtd_eq, qtd_coef, (l_ini + 1), (c_ini + 1));
}

int main(void){
	
	Racional** sistema;
	int qtd_eq, qtd_coef;
	
	scanf("%d", &qtd_eq);
	scanf("%d", &qtd_coef);
	sistema = alocarSistema(qtd_eq, qtd_coef);
	
	// Cadastrando as equacoes do sistema.
	for(int i = 0; i < qtd_eq; i++){
		
		char obj;
		scanf(" %c", &obj);
		
		if(obj == 'p'){
			preencherEquacao(qtd_coef, sistema[i]);
		} else {
			preencherEquacao(qtd_coef, sistema[i++]);
			preencherEquacao(qtd_coef, sistema[i]);
		}

	}
	
	escalonarMatriz(sistema, qtd_eq, qtd_coef, 0, 0);
	
	// Verificando por absurdos
	char possui_absurdo = 'n';
	
	for(int i = 0; i < qtd_eq; i++){
		
		// A eq. possui todos coeficientes nulos: 's'/'n'
		char coef_nulos = 's';
		for(int j = 0; j < qtd_coef-1; j++){
			if(sistema[i][j].a != 0)
				coef_nulos = 'n';
		}
		
		// O ultimo coef. nao eh nulo
		if(sistema[i][qtd_coef-1].a != 0 && coef_nulos == 's')
			possui_absurdo = 's';
	}
	
	
	if(possui_absurdo == 's')
		printf("nao\n"); // eles nao colidem
	else
		printf("sim\n"); // eles colidem
	
	
	// Visualizar a matriz de structs 
	for(int i = 0; i < qtd_eq; i++){
		for(int j = 0; j < qtd_coef; j++){
			
			sistema[i][j] = simplificarRacional(sistema[i][j]);
				
			if(sistema[i][j].b == 1)
				printf("%d", sistema[i][j].a);
			else
				printf("%d/%d", sistema[i][j].a, sistema[i][j].b);
			
			if(j < qtd_coef-1)
				printf("\t");
		}
			
		printf("\n");
	}
	
	desalocarSistema(qtd_eq, qtd_coef, sistema);
	
	return 0;
}
