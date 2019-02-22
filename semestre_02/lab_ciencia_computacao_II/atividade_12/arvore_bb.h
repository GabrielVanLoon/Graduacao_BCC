#ifndef ARVORE_BB_H
	#define ARVORE_BB_H
	
	#include "lista.h"

	// Definindo o tipo de elmeneto da árvore
	typedef int Elem;

	// Nó da Arvore de Busca Binária
	typedef struct _noarvorebb{
		Elem info;
		struct _noarvorebb *left, *right;
	} NoArvoreBB;

	// TAD da Árvore de Busca Binária
	typedef struct _arvorebb{
		struct _noarvorebb *raiz;
	} ArvoreBB;

	/**
	 * @void criarArvoreBB();
	 */
	void criarArvoreBB(ArvoreBB *abb);

	/**
	 * @void destruirArvoreBB();
	 */
	void destruirArvoreBB(ArvoreBB *abb);

	/**
	 * @int abb_inserirElemento(ArvoreBB *abb, Elem e);
	 */
	int abb_inserirElemento(ArvoreBB *abb, Elem e);

	/**
	 * @int abb_removerElemento(ArvoreBB *abb, Elem e);
	 */
	int abb_removerElemento(ArvoreBB *abb, Elem e);

	/**
	 * @int abb_buscarElemento(ArvoreBB *abb, Elem e);
	 */
	int abb_buscarElemento(ArvoreBB *abb, Elem e);

	/**
	 * @int abb_printInOrdem(ArvoreBB *abb);
	 */
	int abb_printInOrdem(ArvoreBB *abb);

	/**
	 * @int abb_printPreOrdem(ArvoreBB *abb);
	 */
	int abb_printPreOrdem(ArvoreBB *abb);

	/**
	 * @int abb_printPosOrdem(ArvoreBB *abb);
	 */
	int abb_printPosOrdem(ArvoreBB *abb);

	/**
	 * @int abb_printLargura(ArvoreBB *abb);
	 */
	int abb_printLargura(ArvoreBB *abb);

#endif