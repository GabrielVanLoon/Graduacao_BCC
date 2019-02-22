#ifndef ARVORE_QUART_H
	#define ARVORE_QUART_H
	
	typedef enum _tipoNo{
		PRETO, BRANCO 
	} Cor;
	
	typedef enum _cor{
		FOLHA, SUB 
	}TipoNo;
	
	typedef struct _no{
		struct _no* filhos[4];
		TipoNo      tipo;
		Cor         cor;
	}No;
	
	typedef struct _arvoreQuart{
		No *ini;
	} ArvoreQuart;
	
	/**
	 * @construirArvore(ArvoreQuart *arv, char *str, int size);
	 * - Dada uma string, tamanho da string e uma arvore vazia, cria uma
	 *   arvore binária.
	 */
	void construirArvore(ArvoreQuart *arv, char *str, int size);
	
	/**
	 * @destruirArvore(ArvoreQuart *arv);
	 * - Desaloca uma variável do tipo ArvoreQuart da memória.
	 */
	void destruirArvore(ArvoreQuart *arv);

	/**
	 * @printArvore(ArvoreQuart *arv);
	 * - Realiza o print de uma arvore quartenaria linearmente
	 */
	void printArvore(ArvoreQuart *arv);
	
	/**
	 * @mesclarCores(ArvoreQuart *arv);
	 * - Realiza a mescla de cores das arvores binarias, retornando a quanti-
	 *   dade de pixels pretos.
	 */
	int mesclarCores(ArvoreQuart *arv1, ArvoreQuart *arv2);

	
#endif
