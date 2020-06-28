#ifndef LISTA_ORDENADA_H
	#define LISTA_ORDENADA_H
	
	// LO_ PREFIXO PARA ELEMENTOS DA LISTA ORDENADA
	
	typedef int elem_LO;

	typedef struct _noLO {
		elem_LO info;
		struct _noLO *prox;
	} NoListaOrd;

	typedef struct {
		NoListaOrd *ini, *fim;
	} ListaOrdenada;

	/**
	 * @void lo_criarListaOrdenada(void *lv);
	 * - Estancia uma variável do tipo lista ordenada.
	 */
	void lo_criarListaOrdenada(void *lv);

	/**
	 * @void lo_finalizarListaOrdenada(ListaOrdenada *l);
	 * - Elimina a estância de uma Lista Ordenada.
	 */
	void lo_finalizarListaOrdenada(void *lv);

	/**
	 * @int lo_inserirElemento(ListaOrdenada *l, elem_LO x);
	 * - Estancia uma variável do tipo lista ordenada.
	 */
	//  int lo_inserirElemento(ListaOrdenada *l, elem_LO x);
	int lo_inserirElemento(void *lv, int x);
	
	/**
	 * @void lo_printLista(ListaOrdenada l);
	 * - Realiza o print dos elementos da lista
	 */
	void lo_printLista(ListaOrdenada l);

	/**
	 * @int lo_buscarElemento(ListaOrdenada l, elem_LO x);
	 * - Busca um elemento na lista, retorna 1 caso encontra e 0 caso não.
	 */
	// int lo_buscarElemento(ListaOrdenada *l, elem_LO x);
	int lo_buscarElemento(void *lv, int x);
	
	/**
	 * @int lo_eliminarElemento(ListaOrdenada *l, elem_LO x);
	 * - Procura o elemento x na lista, caso ele exista o elimina.
	 */
	// int lo_eliminarElemento(ListaOrdenada *l, elem_LO x);
	int lo_eliminarElemento(void *lv, int x);
	
	
	/**
	 * @void lo_ordenarLista(ListaOrdenada *l);
	 * - Ordena os elementos inseridos na lista
	 */
	void lo_ordenarLista(void *lv);

#endif
