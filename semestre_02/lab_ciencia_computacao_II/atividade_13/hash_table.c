#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"

// Prototypes
int  _hashFunction(char* str);
int  _charValue(char c);
int  _powMod(int x, int y, int mod);
int _printInOrdem_hash(NoArvoreBB *no, int comma);

/**
 * @criarHashTable(HashTable* ht)
 * - Estancia uma nova variável do tipo HashTable, preparando-a para uso. 
 */
void criarHashTable(HashTable* ht){
	ht->colisoes = 0;
	ht->vet      = malloc(TABLESIZE*sizeof(ArvoreBB));
	
	for(int i = 0; i < TABLESIZE; i++)
		criarArvoreBB(ht->vet + i);
}

/**
 * @criarHashTable(HashTable* ht)
 * - Desaloca a variável do tipo HashTable da memória. 
 */
void removerHashTable(HashTable* ht){
	if(ht->vet == NULL) return;
	
	for(int i = 0; i < TABLESIZE; i++)
		destruirArvoreBB(ht->vet + i);
	
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
int ht_inserirDado(HashTable* ht, int x){
	if(ht->vet == NULL) return 0;

	int index = x % TABLESIZE; 

	if(abb_inserirElemento(&ht->vet[index], x))
		return 1; // O elemento ja foi inserido anteriormente.

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
int ht_buscarDado(HashTable* ht, int x){
	if(ht->vet == NULL) return 0;

	int index = x % TABLESIZE; 

	if(!abb_buscarElemento(&ht->vet[index], x))
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
int ht_removerDado(HashTable* ht, int x){
	if(ht->vet == NULL) return 0;

	int index = x % TABLESIZE; 

	abb_removerElemento( &(ht->vet[index]) , x);

	return 0;
}

/**
 * @ht_printHashTable(HashTable* ht);
 */
void ht_printHashTable(HashTable* ht){
	
	int comma = 0;


	for(int i = 0; i < TABLESIZE; i++){

		if(ht->vet[i].size == 0) continue;

		if(ht->vet[i].size == 1) {
			_printInOrdem_hash(ht->vet[i].raiz, comma);
		}
		else {
			printf(", (");
			_printInOrdem_hash(ht->vet[i].raiz, 0);
			printf(")");
		}
		
		if(comma == 0) comma = 1;
	}

	printf("\n");
}


// Prototypes usadas na prática 11

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

// Prototypes do print

	// esquerda >> raiz >> direita
	int _printInOrdem_hash(NoArvoreBB *no, int comma){
		if(no == NULL) return comma;

		comma = _printInOrdem_hash(no->left, comma);

		if(comma)
			printf(", %d", no->info);
		else
			printf("%d", no->info);
		
		comma = 1;

		comma = _printInOrdem_hash(no->right, comma);

		return comma;
	}