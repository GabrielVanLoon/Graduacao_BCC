#ifndef LISTACIRC_FREQ_H
	#define LISTACIRC_FREQ_H
	
	typedef int elem_LFREQ;

	typedef struct _noLFREQ {
	    elem_LFREQ info;
	    int 	   busca; // qtd de buscas pelo elemento
	    struct _noLFREQ *ant, *prox;
	} NoLFREQ;

	typedef struct {
	    NoLFREQ *ini, *fim;
	} ListaFreq;

	/**
	 * @void lfreq_criarLista(void *lv);
	 * - Estancia uma variável do tipo Lista de Frequencia
	 */
	void lfreq_criarLista(void *lv);

	/**
	 * @void lfreq_eliminarLista(void *lv);
	 * - Elimina a estância de uma Lista de Frequencia
	 */
	void lfreq_eliminarLista(void *lv);

	/**
	 * @int lfreq_inserirElemento(void *lv, int x);
	 * - Insere um novo elemento no final da Lista de Frequencia
	 */
	int lfreq_inserirElemento(void *lv, int x);

	/**
	 * @int lo_eliminarElemento(void *lv, int x);
	 * - Procura o elemento x na lista, caso ele exista o elimina.
	 */	
	int lfreq_eliminarElemento(void *lv, int x);

	/**
	 * @int lo_buscarElemento(void *lv, int x);
	 * - Procura o elemento x na lista. Retorna 1 caso exista.
	 */	
	int lfreq_buscarElemento(void *lv, int x);

	/**
	 * @void lfreq_printLista(void *lv);
	 */	
	void lfreq_printLista(void *lv);

#endif