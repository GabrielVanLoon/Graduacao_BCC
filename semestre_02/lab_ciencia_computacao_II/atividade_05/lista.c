#include "lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Prototype Hidden Functions
int _compararPeloNome(Elemento a, Elemento b);
int _compararPeloID(Elemento a, Elemento b);
int _mergeSort(Lista *d, int l, int r, int qtd, int (*compare)(Elemento, Elemento));
void _merge(Lista *d, int l, int m, int r, int (*compare)(Elemento, Elemento));

// Main Functions
Lista novaLista(){
	Lista temp;
	temp.vet = NULL;
	temp.size = 0;
	return temp;
}

void liberarLista(Lista *l){
	if(l->vet != NULL) free(l->vet);
	*l = novaLista();
}

void inserirElemento(Lista *l, Elemento e){
	l->vet = (Elemento*) realloc(l->vet, ++l->size*sizeof(Elemento));
	l->vet[l->size-1] = e;
}

void ordenarPeloNome(Lista *l, int max){
	_mergeSort(l, 0, l->size-1, max, _compararPeloNome);
}

void ordernarPeloID(Lista *l, int max){
	_mergeSort(l, 0, l->size-1, max, _compararPeloID);
}

void printLista(Lista *l){
	for(int i = 0; i < l->size; i++)
		printf("%s %d %s\n", (l->vet[i].facul == FEDERAL) ? "FEDERAL":"CAASO", l->vet[i].id, l->vet[i].nome );
}


// Hide Functions
int _compararPeloNome(Elemento a, Elemento b){
	return strcmp(a.nome, b.nome);
}

int _compararPeloID(Elemento a, Elemento b){
	return (a.id <= b.id) ? -1 : 1;
}

int _mergeSort(Lista *d, int l, int r, int qtd, int (*compare)(Elemento, Elemento)){
	// Stop case
	if(l >= r || qtd == 0) return qtd;

	int m = (l + r)/2;

	// Ajuste para o lado direito ser maior
	if ( m > 0 && (m-l) > (r-m-1)) m--;

	qtd = _mergeSort(d, l, m, qtd, compare);
	qtd = _mergeSort(d, m+1, r, qtd, compare);
	
	if(qtd > 0)
		_merge(d, l, m, r, compare);

	return qtd-1;
}

void _merge(Lista *d, int l, int m, int r, int (*compare)(Elemento, Elemento)){

	int i = l, j = 0, k = 0;
	int sizeL = m-l+1, sizeR = r-m;

	Elemento* left = (Elemento*) malloc(sizeL*sizeof(Elemento));
	Elemento* right = (Elemento*) malloc(sizeR*sizeof(Elemento));

	// Making copy os left and right side
	for(int w = 0; w < sizeL; w++)
		left[w] = d->vet[l+w];

	for(int w = 0; w < sizeR; w++)
		right[w] = d->vet[m+1+w];
	
	// Compare and merge between the two copied sides
	// i - interactor to merge/destiny 
	// j - interactor to left side
	// k - interactor to right side
	while(j < sizeL && k < sizeR){
		if( compare(left[j], right[k]) <= 0)
			d->vet[i++] = left[j++];
		else
			d->vet[i++] = right[k++];
	}

	// Copy the rest of left
	while(j < sizeL)
		d->vet[i++] = left[j++];

	// Copy the rest of right
	while(k < sizeR)
		d->vet[i++] = right[k++];
	
	free(left);
	free(right);
}
