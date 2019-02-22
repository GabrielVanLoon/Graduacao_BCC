#ifndef AVL_H
	#define AVL_H

	typedef int elem_AVL;

	typedef struct n {
	    elem_AVL info;
	    struct n  *esq, *dir;
	    int fb, altura;
	} NoAVL;

	typedef struct {
	    NoAVL *raiz;
	} AVL;

	/**
	 * @void avl_criarArvore(void *av);
	 * - Estancia uma variável do tipo Árvore AVL
	 */
	void avl_criarArvore(void *av);
	

	/**
	 * @void avl_finalizarArvore(void *av);
	 * - Elimina a estância de uma Árvore AVL
	 */
	void avl_finalizarArvore(void *av);
	
	/**
	 * @int avl_estaVazia(void *av);
	 * - Retorna 1 caso a árvore avl esteja vazia
	 */
	int avl_estaVazia(void *av);

	/**
	 * @int avl_estaVazia(void *av);
	 * - Retorna a altura da árvore avl. Obs. A função é O(n), sendo n
	 *   a quantidade de filhos da árvore.
	 */
	int avl_altura(void *av);

	/**
	 * @int avl_buscarElemento(void* av, int x);
	 * - Busca um elemento na Árvore, retorna 1 caso o encontre e 
	 *   0 caso contrário.
	 */
	int avl_buscarElemento(void* av, int x);

	/**
	 * @int avl_inserirElemento(void* av, int x);
	 * - Insere um elemento na Árvore, retorna 1 caso ocorra algum erro ou,
	 *   esse elemento já exista na árvore e 0 em caso de sucesso.
	 */
	int avl_inserirElemento(void* av, int x);
	
	/**
	 * @int avl_eliminarElemento(void* av, int x);
	 * - Busca o valor x na árvore e, caso exista, o remove.
	 */
	int avl_eliminarElemento(void* av, int x);

	/**
	 * @void avl_printInOrdem(void* av);
	 * - Imprime a árvore na ordem (esq) (raiz) (dir)
	 */
	void avl_printInOrdem(void* av);
	

#endif