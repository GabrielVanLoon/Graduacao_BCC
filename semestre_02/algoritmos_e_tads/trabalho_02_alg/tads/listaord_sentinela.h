#ifndef LISTAORD_SENT_H
	#define LISTAORD_SENT_H
	
	// LOS_ PREFIXO PARA ELEMENTOS DA LISTA ORDENADA COM SENTINELA
	
	typedef int elem_LOS;

	typedef struct _noLOS {
		elem_LOS info;
		struct _noLOS *prox;
	} NoLOS;

	typedef struct {
		NoLOS *ini, *sentinela;
	} ListaOrdSent;
	
	
	/**
	 * @int los_criarLista(ListaOrdSent *l);
	 * - Estancia uma variável do tipo lista ordenada Sentinela.
	 */
	void los_criarLista(void *lv);
	
	/**
	 * @void lo_finalizarListaOrdenada(ListaOrdenada *l);
	 * - Elimina a estância de uma Lista Ordenada com Sentinela
	 */
	void los_finalizarLista(void *lv);
	
	/**
	 * @int los_inserirElemento(ListaOrdenada *l, elem_LO x);
	 * - Insere um novo elemento na Lista Ordenada com Sentinela
	 */
	// int los_inserirElemento(ListaOrdSent *l, elem_LOS x);
	int los_inserirElemento(void *lv, int x);

	/**
	 * @int lo_eliminarElemento(ListaOrdenada *l, elem_LO x);
	 * - Procura o elemento x na lista, caso ele exista o elimina.
	 */	
	//int los_eliminarElemento(ListaOrdSent *l, elem_LOS x);
	int los_eliminarElemento(void *lv, int x);
	
	/**
	 * @int los_buscarElemento(ListaOrdenada l, elem_LOS x);
	 * - Busca um elemento na lista, retorna 1 caso encontra e 0 caso não.
	 */
	//int los_buscarElemento(ListaOrdSent *l, elem_LOS x);
	int los_buscarElemento(void *l, int x);
	
	int  los_esta_vazia(ListaOrdSent l);
	void los_imprime(ListaOrdSent l);

#endif
