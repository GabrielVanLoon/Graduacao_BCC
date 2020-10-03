#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"

// Prototypes
int _hashFunction(char* str);
int _charValue(char c);
int _powMod(int x, int y, int mod);

/**
 * @criarHashTable(HashTable* ht)
 * - Estancia uma nova variável do tipo HashTable, preparando-a para uso. 
 */
void criarHashTable(HashTable* ht){
	ht->colisoes = 0;
	ht->vet      = malloc(PRIME_P*sizeof(Elem));
	
	for(int i = 0; i < PRIME_P; i++){
		ht->vet[i].status = EMPTY;
		ht->vet[i].str    = NULL;
	}
}

/**
 * @criarHashTable(HashTable* ht)
 * - Desaloca a variável do tipo HashTable da memória. 
 */
void removerHashTable(HashTable* ht){
	if(ht->vet == NULL) return;
	
	for(int i = 0; i < PRIME_P; i++){
		if(ht->vet[i].status == OCCUPIED)
			free(ht->vet[i].str);
	}
	
	free(ht->vet); 
	ht->vet = NULL;
}

/**
 * @criarHashTable(HashTable* ht, char* str)
 * - Insere uma string na HashTable. 
 * 
 *  Retorno:
 *  - 1 em caso de falha.
 *  - 0 em caso de sucesso.
 */
int ht_inserirDado(HashTable* ht, char* str){
	if(str == NULL || ht->vet == NULL) return 0;

	int index = _hashFunction(str);
	int cont = 0, houveColisoes = 0;


	// Procurando um slot vazio ou removido para inserir o dado.
	// O vetor age como uma lista circular.
	while(ht->vet[index].status == OCCUPIED && cont <= PRIME_P){
		index = (index+1 == PRIME_P) ? 0 : index+1;
		cont++;
		houveColisoes = 1;
	}

	// Dado para avaliação da eficiencia da funcao hash
	ht->colisoes += (houveColisoes) ? 1 : 0;

	// A tabela hash está lotada.
	if(cont > PRIME_P) return -1;
	
	// Inserindo o dado na tabela e marcando ele como ocupado.
	ht->vet[index].status = OCCUPIED;
	ht->vet[index].str    = str;

	return index;
}

/**
 * @ht_buscarDado(HashTable* ht, char* str);
 * - Dada uma string, verifica se a mesma está contina na hash table.
 *
 *  Retorno:
 *  - -1 em caso de falha.
 *  - index na HashTable em caso de sucesso.
 */
int ht_buscarDado(HashTable* ht, char* str){
	if(str == NULL || ht->vet == NULL) return 0;

	int index = _hashFunction(str);
	int cont = 0;

	// Buscando até achar a string correta ou um espaço vazio.
	while(ht->vet[index].status  != EMPTY && cont <= PRIME_P){
		if(ht->vet[index].status == OCCUPIED && strcmp(ht->vet[index].str, str) == 0)
			break;
		cont++;
		index = (index+1 == PRIME_P) ? 0 : index+1;
	}

	// O hash aponta para um index vazio ou removido.
	if(ht->vet[index].status != OCCUPIED)
		return -1;

	// O hash aponta para uma string que não é a buscada
	if(strcmp(ht->vet[index].str, str) != 0)
		return -1;

	return index;
}

/**
 * @ht_buscarDado(HashTable* ht, char* str);
 * - Dada uma string, verifica se a mesma está contina na hash table,
 *   caso exista, remove a informação.
 * - Qual é a melhor abordagem para remover dados quando estamos lidando
 *   com colisões? "Marcar o dado como vazio, ocupado e removido"
 *   Font: https://stackoverflow.com/questions/279539/best-way-to-remove-
 *         an-entry-from-a-hash-table
 *  Retorno:
 *  - 0 em caso de sucesso.
 *  - 1 em caso de falha.
 */
int ht_removerDado(HashTable* ht, char* str){
	if(str == NULL || ht->vet == NULL) return 0;

	int index;

	// Caso a str não exista na hash table.
	if((index = ht_buscarDado(ht, str)) == -1) 
		return 1;

	ht->vet[index].str    = NULL;
	ht->vet[index].status = DELETED;

	return 0;
}

// Prototypes

/**
 * @int _hashFunction(char* str)
 * 
 * - Realiza um hash polinomal de string, utilizando a formula:
 *   str[0]*A^0 + str[1]*A^1 + str[2]*A^2 .... str[K]*A^K
 *   tal que A é um numéro primo escolhido aleatóriamente.
 *	
 */
int _hashFunction(char* str){
	
	int index = 0; 
	int size  = strlen(str);

	int power, coef;

	for(int i = 0; i < size; i++){
		coef   = _charValue(str[i]) % PRIME_P;
		power  = _powMod(PRIME_Q, i,  PRIME_P);
		index += ( coef * power )   % PRIME_P;
	}

	// printf("Index value: %d\n", index % PRIME_P);
	return (index % PRIME_P);
}

int _charValue(char c){
	if('a' <= c && c <= 'z')
		return c - 'a' + 1;
	
	else if('A' <= c && c <= 'Z')
		return c - 'A' + 1;

	else if('0' <= c && c <= '9')
		return c - '0' + 1;
	
	return 1;
}

int _powMod(int x, int y, int mod){
	int result = 1;
	for(int i = 1; i <= y; i++){
		result = (x * result) % mod;
	}
	return result % mod;
}