/**
 * Trabalho de Introdução a Ciencia da Computacao II
 * Título: T2 - k-Vizinhos mais Proximos (KNN)
 * Autor:  Gabriel Van Loon
 * Prof.:  Moacir Ponti
 * Data:   setembro/2018
 * 
 * DESCRIÇÃO
 * O programa implementa o algoritmo de Aprendizado de Máquina, K-Vizinhos 
 * Mais Proximos, para classificar dentre 3 espécies da flor Íris.
 * 
 * Para isso, ele avalia 4 aspectos das plantas desse gênero:
 * - Comprimento e Largura das Sépalas
 * - Comprimento e Largura das Pétalas
 * 
 * ENTRADA:
 * - Arquivo .csv p/ treino do algoritmo;
 * - Arquivo .csv p/ avaliar taxa de acerto;
 * - Quantidade K de vizinhos avaliados pelo algoritmo. 
 * 
 * RETORNO:
 * - Para cada espécime no arquivo de teste, retorna a espécie encontrada e 
 *   a espécie verdadeira
 * - Taxa de acerto do algoritmo
 */
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

/**
 * @typedef Especime
 *    
 *    Struct que agrupa as informacoes de um indivíduo
 * do gênero ìris. Para otimização de memória, as espécies
 * são atribuidas por numeros de identificação estabelecidos
 * via # define.
 */
# define SETOSA 1
# define VIRGINICA 2
# define VERSICOLOR 3

typedef struct {
	double comprimentoSepala;
	double larguraSepala;
	double comprimentoPetala;
	double larguraPetala;
	int   especie;
} Especime;

/**
 * @typedef Similaridade
 *    
 *   Struct que auxilia no algoritmo de kNN ao
 * agrupar as seguintes informacoes:
 *   -Distância de um indivíduo até o vizinho;
 *   -Espécie do vizinho. 
 */
typedef struct {
	double dist;
	int   especie;
} Similaridade;

/**
 * @popularEspecimes(Especime** v, FILE* csv)
 *    
 * Descrição:
 *    A funcao popula o vetor de espécimes v a partir
 * dos dados contidos em um arquivo CSV.
 *    Os dados devem respeitar o padrao proposto pelo
 * seguinte padrao:
 *    
 *   "Sepal.Length","Sepal.Width","Petal.Length","Petal.Width","Species"
 *	 (double),(doble),(double),(double),"(string: setosa/virginica/versicolor)"
 * 
 * Entrada:
 *   Especime** v:  Endereço do array que será populado;
 *   FILE* csv:     Ponteiro para o arquivo CSV que irá popular os dados.
 * 
 * Retorno:
 *	int:   Quantidade de espécimes inseridos no array. 
 */
int popularEspecimes(Especime** v, FILE* csv);

/**
 * @ordenarSimilaridades(Similaridade** s, int n)
 *    
 * Descrição:
 *    O algoritmo utiliza o método de ordenadação Insertion
 * Sort para ordenar um vetor de similaridades do mais próximo
 * para o mais distante de um determinado indivíduo.
 * 
 * Entrada:
 *   Similaridades** s:  Endereço do array que será ordenado;
 *   int n:              Tamanho do array s.
 */
void ordenarSimilaridades(Similaridade** s, int n);

/**
 * @printEspecie(int esp)
 *    
 * Descrição:
 *    Funcao auxiliar que recebe o código da espécie e 
 * realiza o printf da sua string correspondente.
 * 
 * Entrada:
 *   int esp: valor definido para a espécie.
 */
void printEspecie(int esp);

int main(void){

	/**
	 * Variáveis:
	 * int k:               Qtd. de vizinhos avaliados pelo algoritmo;
	 * int n:               Qtd. de espécimes no array de vizinhos;
	 * int m:               Qtd. de espécimes no array de testes;
	 * int acertos:         Contador de vezes que o algoritmo acertou a espécie
	 * char nomeTreino:     Nome do arquivo CSV para treino do algoritmo;
	 * char nomeTeste:      Nome do arquivo CSV com os espécimes de teste;
	 * FILE* fTreino:       Ponteiro para o CSV de treino;
     * FILE* fTeste:        Ponteiro para o CSV de teste;
     * Espécimo* vizinhos:  Array de espécimes do CSV de treino;
     * Espécime* testes:    Array com espécimes do CSV de teste.
	 */

	int k, n, m, acertos = 0;
	double taxaAcerto;
	char nomeTreino[20], nomeTeste[20];
	FILE* fTreino = NULL; 
	FILE* fTeste = NULL;
	Especime* vizinhos = NULL; 
	Especime* testes = NULL;

	// Lendo e abrindo os CSV de treino e teste
	scanf("%s", nomeTreino);
	scanf("%s", nomeTeste);
	scanf("%d", &k);

	fTreino = fopen(nomeTreino, "r");
	fTeste  = fopen(nomeTeste,  "r");

	// Populando os vizinhos com o arquivo de treino
	n = popularEspecimes(&vizinhos, fTreino);

	// Verificando se existem vizinhos suficientes
	if(k > n) {
		printf("k is invalid\n");
		return 0;
	}

	// Populando os testes de teste
	m = popularEspecimes(&testes, fTeste);

	// Para cada um dos casos de teste, executa o kNN e exibe 
	// a classe encontrada, com a classe verdadeira em seguida
	for(int i = 0; i < m; i++){
		
		Similaridade* matrix = (Similaridade*) malloc(n * sizeof(Similaridade));
		int freq[4] = {0, 0, 0, 0}; // Contador de frequencia de cada especie
		int result; // Resultado do algoritmo para o individuo i

		// Calculando as Distancias Euclidianas
		for(int j = 0; j < n; j++){
			matrix[j].especie = vizinhos[j].especie;
			matrix[j].dist  = (vizinhos[j].comprimentoSepala - testes[i].comprimentoSepala) * (vizinhos[j].comprimentoSepala - testes[i].comprimentoSepala);
			matrix[j].dist += (vizinhos[j].larguraSepala - testes[i].larguraSepala)         * (vizinhos[j].larguraSepala - testes[i].larguraSepala);
			matrix[j].dist += (vizinhos[j].comprimentoPetala - testes[i].comprimentoPetala) * (vizinhos[j].comprimentoPetala - testes[i].comprimentoPetala);
			matrix[j].dist += (vizinhos[j].larguraPetala - testes[i].larguraPetala)         * (vizinhos[j].larguraPetala - testes[i].larguraPetala);
			matrix[j].dist  = sqrt(matrix[j].dist);
		}

		// Ordenando os resultados das distancias
		ordenarSimilaridades(&matrix, n);

		// Caso queira exibir os k-vizinhos mais proximos
		// for(int j = 0; j < k; j++ ) printf("%dº Dist: %lf Especie: %d\n", j, matrix[j].dist, matrix[j].especie);

		// Contando a freq das especies que mais aparecem nos vizinhos
		for(int j = 0; j < k; j++ ) 
			freq[ matrix[j].especie ]++;

		// Qual especie aparece mais, em caso de empate pega o do vizinho mais prox
		if     ( freq[SETOSA] > freq[VIRGINICA] && freq[SETOSA] > freq[VERSICOLOR] ) result = SETOSA;
		else if( freq[VIRGINICA] > freq[SETOSA] && freq[VIRGINICA] > freq[VERSICOLOR] ) result = VIRGINICA;
		else if( freq[VERSICOLOR] > freq[SETOSA] && freq[VERSICOLOR] > freq[VIRGINICA] ) result = VERSICOLOR;
		else result = matrix[0].especie;

		// Verificando se houve erro ou acerto
		if(result == testes[i].especie ) acertos++;

		// Exibindo: "Especie Encontrada" e "Especie Verdadeira" do espécime 
		printEspecie(result); printf(" "); printEspecie(testes[i].especie); printf("\n");

		free(matrix);
	}
	
	// 	Exibindo a eficácia de acertos do kNN
	printf("%.04lf\n", acertos/((double) m));

	// Desalocando a memória utilizada
	if(fTreino != NULL) fclose(fTreino);
	if(fTeste  != NULL) fclose(fTeste);
	if(vizinhos != NULL) free(vizinhos);
	if(testes != NULL) free(testes);

	return 0;
}

int popularEspecimes(Especime** v, FILE* csv){

	int qtdVizinhos = 0;
	char* linha;
	size_t tamanhoMax = 120;
	 
	linha = (char*) malloc(tamanhoMax*sizeof(char));

	// Ignorando a primeira linha do csv
	if( getline(&linha, &tamanhoMax, csv) == -1) return 0;

	// Lendo as linhas do CSV
	while(getline(&linha, &tamanhoMax, csv) != -1){

		if( strlen(linha) < 10 ) continue;

		Especime temp;
		char nomeEspecie[20];

		sscanf(linha, "%lf,%lf,%lf,%lf,\"%[^\"]s", &temp.comprimentoSepala, &temp.larguraSepala, &temp.comprimentoPetala, &temp.larguraPetala, nomeEspecie);

		// printf("Especime %f %f %f %f %s\n", temp.comprimentoSepala, temp.larguraSepala, temp.comprimentoPetala, temp.larguraPetala, nomeEspecie);
		// continue;

		if(strcmp(nomeEspecie, "setosa") == 0) temp.especie = SETOSA;
		else if(strcmp(nomeEspecie, "virginica") == 0) temp.especie = VIRGINICA;
		else temp.especie = VERSICOLOR;

		// Inserindo especime no vetor de vizinhos
		*v = (Especime*) realloc(*v, ++qtdVizinhos * sizeof(Especime));
		(*v)[qtdVizinhos-1] = temp;

	}	

	free(linha);

	return qtdVizinhos;
}

void ordenarSimilaridades(Similaridade** s, int n){
	/* Metodo de Ordenacao: Insertion Sort O(n²) */
	for(int i = 0; i < n; i++){
		
		Similaridade temp = (*s)[i];
		
		int j = i-1;
		
		while(j >= 0){

			if( temp.dist > (*s)[j].dist )
				break;

			(*s)[j+1] = (*s)[j];
			j--;
		}

		(*s)[j+1] = temp;
	}
}

void printEspecie(int esp){
	switch(esp){
		case SETOSA:     printf("setosa"); break;
		case VIRGINICA:  printf("virginica"); break;
		case VERSICOLOR: printf("versicolor"); break;
	}
}