/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex03. 	Busca e Ordenação de Strings
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * O programa lê um arquivo .txt e as ordena alfabéticamente utilizando um  
 * Insertion Sort(O²). O programa também conta a quantidade de ocorrências
 * para cada uma das palavras.
 *
 * Além disso, o programa lê N strings e verifica quantas vezes ela ocorre no
 * texto, exibindo as 3 palavras subsequentes na ordem alfabética.
 */
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>

# define TAMANHO_PALAVRAS 20

void _tratarPalavra(char* p){
	int j = 0;
	for(int i = 0; i < strlen(p); i++){
		char c = tolower(p[i]);
		
		// Verificando se o char eh alfabetico ou um traco '-' ou apostrofre "'"
		// if( c == 45 || c == 27 || (97 <= c && c <= 122) )
		p[j++] = c;
		
	}
	p[j] = '\0'; // printf("%s\n", p);
}

typedef struct _dicionario{
	char** lista;
	int qtdPalavras;
}Dicionario;

Dicionario iniciarDicionario(){
	Dicionario d;
	d.lista = NULL;
	d.qtdPalavras = 0;
	return d;
}

void destruirDicionario(Dicionario* d){
	
	for(int i = 0; i < d->qtdPalavras; i++)
		free(d->lista[i]);
	
	free(d->lista);
}

void listarDicionario(Dicionario* d){
	for(int i = 0; i < d->qtdPalavras; i++)
		printf("nº%05d - %s\n", i+1, d->lista[i]);
}

void ordenarDicionario(Dicionario* d){
	/* Metodo de Ordenacao: Insertion Sort O(n²) */
	for(int i = 0; i < d->qtdPalavras; i++){
		char* ptrString = d->lista[i];
		int j = i-1;
		
		while(j >= 0){
			if( strcmp(ptrString, d->lista[j]) > -1)
				break;
			d->lista[j+1] = d->lista[j];
			j--;
		}

		d->lista[j+1] = ptrString;
	}
}

int buscarPalavra(Dicionario* d, char* str){

	int l = 0;
	int r = d->qtdPalavras-1;
	int m = (l + r)/2;
	//int cont = 1;

	while(l < r){

		int comp = strcmp(str, d->lista[m]);
		//printf("Cont %d, M >> %d, [%d,%d], Compare = %d \n", cont++, m, l, r, comp);

		// Encontrou a string buscada
		if( comp == 0){

			// Ajuste para apontar sempre para a primeira ocorrencia
			while(m > 0 && strcmp(str, d->lista[m-1]) == 0) m--;

			return m;

		// A str esta na primeira metade
		} else if( comp < 0){
			r = m-1;
			m = (l + r)/2;

		// A str esta na segunda metade
		} else {
			l = m+1;
			m = (l + r)/2;
		}

	}

	return m;
}

void incluirPalavra(Dicionario* d, char* p){
	
	_tratarPalavra(p);
	if(strlen(p) <= 0) return;

	d->qtdPalavras++;
	// Array de ponteiros que apontam para strings
	d->lista = (char**) realloc(d->lista, sizeof(char*) * d->qtdPalavras);
	// String salva na memoria
	d->lista[d->qtdPalavras-1] = (char*) malloc(sizeof(char) * TAMANHO_PALAVRAS);
	// Copiando a string passada para o vetor
	strcpy(d->lista[d->qtdPalavras-1], p);
}

int main(void){

	int  qtdBuscas;
	char strBusca[60];
	char nomeArquivo[TAMANHO_PALAVRAS], palavra[TAMANHO_PALAVRAS];
	FILE* arquivo;
	Dicionario dic = iniciarDicionario();

	// Lendo o nome do arquivo e a qtd de palavras
	scanf("%s", nomeArquivo);
	scanf("%d", &qtdBuscas);	

	// Abrindo o arquivo
	arquivo = fopen(nomeArquivo, "r");
	if(arquivo == NULL) return 0;
	
	while(fscanf(arquivo, "%s", palavra) != EOF){
		incluirPalavra(&dic, palavra);
	}

	// Ordenando as palavras
	ordenarDicionario(&dic);
	// listarDicionario(&dic);

	// Fazendo as buscas
	for(int i = 0; i < qtdBuscas; i++ ){
		
		int id, qtdOcorrencias = 0, k = 0;

		// Lendo a palavra a ser buscada
		scanf("%s", strBusca);

		// Id da primeira ocorrencia da palavra
		id = buscarPalavra(&dic, strBusca);

		// Contando quantas repeticoes ocorreram
		while(id < dic.qtdPalavras && strcmp(strBusca, dic.lista[id]) == 0){
			qtdOcorrencias++; id++;
		}

		printf("%s %d", strBusca, qtdOcorrencias);

		// Fix para os casos de a str encontrada nao ter sido achada
		if(qtdOcorrencias == 0 && strcmp(strBusca, dic.lista[id]) > 0)
			id++;

		// mostrando as proximas 3 palavras
		while(id+k < dic.qtdPalavras && k < 3){
			printf(" %s", dic.lista[id+k]);
			k++;
		}

		printf("\n");
	}

	destruirDicionario(&dic);
	return 0;
}