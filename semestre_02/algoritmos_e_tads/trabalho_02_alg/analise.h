#ifndef ANALISE_H
	#define ANALISE_H
	
	#define CRESCENTE 	0
	#define DECRESCENTE 1
	#define ALEATORIO   2
	
	typedef struct _dados {
		double insercao[3];
		double remocao[3];
		double busca[3];
	} Dados;
	
	/**
	 * @clock_t tempo_insercao(int n, int opt, int (*insere)(void*, int)); 
	 * 
	 * Testa o tempo para inserir n elementos em um tad de elementos inteiros
	 * Entradas:
	 * - int n: 	Quantidade de elementos;
	 * - int opt:	0 para inserir em ordem crescente, 1 em ordem decrescente
	 *              e 2 para ordem aleatória;
	 * - void* tad:	Estrutura sendo testada passada por referencia,
	 * - int(*insere):	Função de inserção específica da estrutura.
	 */
	double tempo_insercao(int n, int opt, int (*insere)(void*, int), void* tad, void (*aux)(void*)); 
	
	/**
	 * @clock_t tempo_remocao(int n, int opt, int (*remove)(void*, int)); 
	 * 
	 * Testa o tempo para inserir n elementos em um tad de elementos inteiros
	 */
	double tempo_remocao(int n, int opt, int (*remove)(void*, int), void* tad); 
	
	/**
	 * @clock_t tempo_insercao(int n, int opt, int (*busca)(void*, int)); 
	 * 
	 * Testa o tempo para inserir n elementos em um tad de elementos inteiros
	 */
	double tempo_busca(int n, int opt, int (*busca)(void*, int), void* tad); 	

#endif
