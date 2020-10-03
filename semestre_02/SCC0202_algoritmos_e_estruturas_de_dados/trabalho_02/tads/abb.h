#ifndef ARVORE_BUSCA_BINARIA_H
	#define ARVORE_BUSCA_BINARIA_H
	
	// ABB_ prefixo para funcoes da arvore de busca binaria
	
	typedef int elem_ABB;

	typedef struct _noABB {
		elem_ABB info;
		struct _noABB *esq, *dir;
	} NoABB;

	typedef struct _abb{
		NoABB *raiz;
	} ABB;

	/**
	 * @void abb_criarArvore(ABB *a);
	 * - Estancia uma variável do Arvore de Busca Binaria
	 */
	void abb_criarArvore(void *av);
	
	/**
	 * @void lo_finalizarListaOrdenada(ListaOrdenada *l);
	 * - Elimina a estância de uma Arvore de Busca Binária
	 */
	void abb_eliminarArvore(void *av);
	
	/**
	 * @int abb_estaVazia(ABB a);
	 * - Retorna se uma arvore está ou não vazia
	 */
	int abb_estaVazia(ABB a);
	
	/**
	 * @void abb_printArvore(ABB a);
	 * - Realiza o print dos elementos de uma arvore
	 */
	void abb_printArvore(ABB a);
	
	/**
	 * @int abb_buscarElemento(ABB a, elem_ABB x);
	 * - Busca um elemento na arvore, retorna 1 caso encontra e 0 caso não.
	 */
	//int abb_buscarElemento(ABB *a, elem_ABB x);
	int abb_buscarElemento(void *av, int x);
	
	/**
	 * @int abb_inserirElemento(ABB a, elem_ABB x);
	 * - insere um novo elemento na arvore abb, retorna 1 em caso de erro
	 */
	//int abb_inserirElemento(ABB *a, elem_ABB x);
	int abb_inserirElemento(void *av, int x);
	
	/**
	 * @int abb_eliminarElemento(ABB *a, elem_ABB x);
	 * - Busca um elemento na arvore, remove ele caso ele exista.
	 */
	//int abb_eliminarElemento(ABB *a, elem_ABB x);
	int abb_eliminarElemento(void *av, int x);

#endif
