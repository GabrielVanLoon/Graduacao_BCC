#ifndef HASH_TABLE_H
	#define HASH_TABLE_H
	
	#define TABLESIZE 100
	#define PRIME_P   5659
	#define PRIME_Q   33
	
	#include "arvore_bb.h"

	typedef struct _hasht{
		ArvoreBB*  vet;
		int    colisoes;
	}HashTable;

	/**
	 * @criarHashTable(HashTable* ht)
	 * - Estancia uma nova variável do tipo HashTable, preparando-a para uso. 
	 */
	void criarHashTable(HashTable* ht);

	/**
	 * @criarHashTable(HashTable* ht)
	 * - Desaloca a variável do tipo HashTable da memória. 
	 */
	void removerHashTable(HashTable* ht);

	/**
	 * @criarHashTable(HashTable* ht, int x)
	 * - Insere uma string na HashTable. 
	 * 
	 *  Retorno:
	 *  - -1 em caso de falha.
	 *  - index na HashTable em caso de sucesso.
	 */
	int ht_inserirDado(HashTable* ht, int x);

	/**
	 * @ht_buscarDado(HashTable* ht, int x);
	 * - Dada uma string, verifica se a mesma está contina na hash table.
	 *
	 *  Retorno:
	 *  - -1 em caso de falha.
	 *  - index na HashTable em caso de sucesso.
	 */
	int ht_buscarDado(HashTable* ht, int x);

	/**
	 * @ht_buscarDado(HashTable* ht, int x);
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
	int ht_removerDado(HashTable* ht, int x);

	/**
	 * @ht_printHashTable(HashTable* ht);
	 */
	void ht_printHashTable(HashTable* ht);

#endif