#ifndef LISTA_ENCAD_H
	#define LISTA_ENCAD_H
	
	/**
	 * @typedef Nó
	 * Representa um elemento dentro da lista encadeada. Além disso, aponta 
	 * para o próximo Nó da Lista ou para NULL caso seja o último.
	 * 
	 * Variáveis:
	 *    *prox - Ponteiro para o próximo Nó
     *    *back - Ponteiro para algum Nó anterior ou para NULL
     *    chave - Valor de identificação do Nó
     *    tempo - Tempo discreto que o nó foi inserido no programa
     *    pos   - Posição atual do nó na lista.
	 */
	typedef struct _no{
		struct _no *prox, *back;
		int chave, tempo, pos;
	}No;
	
	/**
	 * @typedef Nó
	 * TAD de Lista Encadeada, possui o ponteiro para o Nó inicial da lista.
	 */
	typedef struct _listaEncad{
		No* ini;
	}ListaEnc;
	
	/**
	 * @novaListaEncadeada(ListaEnc *l);
	 * Prepara uma nova variável do tipo Lista Encadeada para uso.
	 */
	void novaListaEncadeada(ListaEnc *l);
	
	/**
	 * @novaListaEncadeada(ListaEnc *l);
	 * Remove os Nós inseridos na lista e os desaloca da memória
	 */
	void removerListaEncadeada(ListaEnc *l);
	
	/**
	 * @novaListaEncadeada(ListaEnc *l);
	 * Insere um novo elemento da lista.
	 * 
	 * Variáveis:
	 *    chave - Valor inteiro que identifica o nó
	 *    back  - Se 0, indica que o ponteiro *back do nó não referenciará
	 *            ninguem, caso contrario, vai referencair o i-ésimo nó
	 *            anterior caso exista.
	 *    tempo - Salva o tempo discreto que o nó foi inserido na lista
	 */
	void inserirElemento(ListaEnc *l, int chave, int back, int tempo);
	
	/**
	 * @novaListaEncadeada(ListaEnc *l);
	 * Remove um nó do lista por meio de seu valor de chave. Também apaga 
	 * qualquer referência que possua em nós posteriores.
	 */
	void removerElemento(ListaEnc *l, int chave);
	
	/**
	 * @novaListaEncadeada(ListaEnc *l);
	 * Realiza um print de toda a lista encadeada. Para cada nó exibe:
	 *    [@chave, @tempo, @back_position] caso o nó possua ponteiro para 
	 *       algum nó anterior
	 *    [@chave, @tempo] caso o nó não possua ponteiro para nenhum anterior
	 */
	void printarListaEncadeada(ListaEnc *l);
	
#endif 
