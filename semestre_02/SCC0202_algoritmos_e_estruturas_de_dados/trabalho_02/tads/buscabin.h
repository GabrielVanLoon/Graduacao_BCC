#ifndef BUSCABIN_H
	#define BUSCABIN_H
	
	#define BB_TAMANHO 100050

	typedef struct _buscaBin{
		int* v;
		int  size;
	} BuscaBin;

	/**
	 * @void bb_criarVetor(void *bv);
	 * - Estancia uma variável do tipo Vetor de Busca Binária.
	 */
	void bb_criarVetor(void *bv);

	/**
	 * @void bb_eliminarVetor(void *bv);
	 * - Elimina a estância de um Vetor de Busca Binária.
	 */
	void bb_finalizarVetor(void *bv);

	/**
	 * @int bb_estaVazio(void *bv);
	 * - Retorna 1 se o Vetor de Busca Binária estiver vazio.
	 */
	int bb_estaVazio(void *bv);

	/**
	 * @int bb_inserirElemento(void *bv, int x);
	 * - Insere um novo elemento no vetor de Busca Binária.
	 * - Retorna 1 em caso de erro.
	 */
	int bb_inserirElemento(void *bv, int x);

	/**
	 * @int bb_buscarElemento(void *av, int x);
	 * - Busca um elemento na arvore, retorna 1 caso ele exista e 0 caso
	 *   não seja posivel encontrá-lo.
	 */
	int bb_buscarElemento(void *bv, int x);

	/**
	 * @int bb_eliminarElemento(void *bv, int x);
	 * - Busca um elemento na arvore, remove ele caso seja encontrado.
	 */
	int bb_eliminarElemento(void *bv, int x);

	/**
	 * @void bb_ordenarElementos(void *bv);
	 * - Realiza um Radix Sort para ordenar os elementos do Vetor BB.
	 */
	void bb_ordenarElementos(void *bv);

	/**
	 * @void bb_printVetor(void *bv);
	 * - Imprime na tela os elementos do vetor de busca binária.
	 */
	void bb_printVetor(void *bv);


#endif