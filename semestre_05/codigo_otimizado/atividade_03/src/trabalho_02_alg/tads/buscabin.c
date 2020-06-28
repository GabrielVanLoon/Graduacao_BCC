#include <stdlib.h>
#include <stdio.h>
#include "buscabin.h"

// Auxiliares 
int bb_posicaoElemento(int *v, int l, int r, int x);


/**
 * @void bb_criarVetor(void *bv);
 */
void bb_criarVetor(void *bv){
	BuscaBin *bb = (BuscaBin*) bv;
	bb->v 	 = malloc(BB_TAMANHO*sizeof(int));
	bb->size = 0;
	return;
}

/**
 * @void bb_eliminarVetor(void *bv);
 */
void bb_finalizarVetor(void *bv){
	BuscaBin *bb = (BuscaBin*) bv;
	if(bb->v != NULL) 
		free(bb->v);
}

/**
 * @int bb_estaVazio(void *bv);
 */
int bb_estaVazio(void *bv){
	BuscaBin *bb = (BuscaBin*) bv;
	return (bb->size < 1);
}

/**
 * @int bb_inserirElemento(void *bv, int x);
 */
int bb_inserirElemento(void *bv, int x){
	BuscaBin *bb = (BuscaBin*) bv;

	// O vetor já alcançou a capacidade máxima.
	if(bb->size == BB_TAMANHO) return 1; 

	bb->v[bb->size] =  x;
	bb->size 		+= 1;

	return 0;
}

/**
 * @int bb_buscarElemento(void *av, int x);
 */
int bb_buscarElemento(void *bv, int x){
	BuscaBin *bb = (BuscaBin*) bv;
	
	if(bb_estaVazio(bb)) return 0;
	return (bb_posicaoElemento(bb->v, 0, (bb->size-1), x) >= 0);
}

/**
 * @int bb_eliminarElemento(void *bv, int x);
 * - Busca um elemento na arvore, remove ele caso seja encontrado.
 */
int bb_eliminarElemento(void *bv, int x){
	BuscaBin *bb = (BuscaBin*) bv;
	
	int pos = bb_posicaoElemento(bb->v, 0, (bb->size-1), x);

	// Verificando se o elemento existe
	if(pos == -1) return 1;

	// Shiftando elementos seguintes.
	for(int i = (pos+1); i < bb->size; i++)
		bb->v[i-1] = bb->v[i];

	bb->size -= 1;

	return 0;
}

/**
 * @void bb_ordenarElementos(void *bv);
 * - Realiza um Radix Sort para ordenar os elementos do Vetor BB.
 */
void bb_ordenarElementos(void *bv){
	BuscaBin *bb = (BuscaBin*) bv;

	int contagem[256] = {0};
	int posicoes[256];
	int *copia = malloc(bb->size*sizeof(int));

	/**
	 * O Radix vai ordenar os elementos ajustando-os em blocos de 1 byte.
	 * O Counting sort ordena dos 8 bits menos significantes para os 8 mais
	 * significantes em cada iteração.
	 */
	for(int shift = 0; shift <= 24; shift += 8){

		/**
		 * 1ª Etapa - Realiza a etapa da contagem dos valores, enquanto faz
		 *			  uma cópia do vetor sendo ordenado.
		 */
		for(int i = 0; i < bb->size; i++){
			// Realiza um AND dos 8 bits e retorna pro mod.
			int mod = (bb->v[i] >> shift) & 255;
			contagem[mod]++;
			copia[i] = bb->v[i];
		}

		/**
		 * 2ª Etapa - O vetor posição indica qual deveria ser posição da
		 *            primeira ocorrencia de cada valor.
		 *            Caso trivial, 0 é sempre o primeiro valor.
		 */
		posicoes[0] = 0;
		for(int i = 1; i < 256; i++){
			posicoes[i]   = posicoes[i-1] + contagem[i-1];
			contagem[i-1] = 0;
		}

		/**
		 * 3ª Etapa - Percorre o vetor cópia e então, consulta o vetor posicao
		 *            para reinserir os valores em suas posições corretas.
		 */
		for(int i = 0; i < bb->size; i++){
			int mod = (copia[i] >> shift) & 255;
			bb->v[posicoes[mod]] = copia[i];
			posicoes[mod]++;
		}
	}

	// Limpando a memória alocaad
	free(copia);
	return;
}

/**
 * @void bb_printVetor(void *bv);
 * - Imprime na tela os elementos do vetor de busca binária.
 */
void bb_printVetor(void *bv){
	BuscaBin *bb = (BuscaBin*) bv;

	printf("Tamanho: %d\n", bb->size);
	for(int i = 0; i < bb->size; i++) printf("%d ", bb->v[i]);
	printf("\n");
	return;
}

// Auxiliares
int bb_posicaoElemento(int *v, int l, int r, int x){
	if(l > r) return -1; // Erro na busca binária.
	int m = (l+r)/2;
	if(v[m] == x) 		return m;
	else if(v[m]  > x) 	return bb_posicaoElemento(v, l, m-1, x);
	else  				return bb_posicaoElemento(v, m+1, r, x);
}