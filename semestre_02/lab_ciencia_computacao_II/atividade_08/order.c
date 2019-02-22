#include "order.h"
#include <stdlib.h>

void swap(elem *a, elem *b){
	elem temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(elem* v, int size, int *comps, int *moves){
	
	for(int i = 0; i < size; i++){
		for(int j = i+1; j < size; j++){
			
			*comps += 1;
			if(v[j] < v[i]){
				*moves += 3;
				swap(v+i, v+j);
			}
		}
	}
}

void insertionSort(elem* v, int size, int *comps, int *moves){

	for(int i = 0; i < size; i++){
		
		*moves += 1;
		elem aux = v[i]; 
		int j = i-1;
		
		*comps += 1;
		while(j >= 0 && v[j] > aux){
			*moves += 1;
			v[j+1] = v[j]; 
			j--; 
			*comps += 1;
		}
		
		*moves += 1;
		v[j+1] = aux; 
	}
}

void merge(elem* v, int l, int m, int r, int *comps, int *moves){
	
	// Creating the auxiliar arrays
	int sizeL = m-l+1;
	int sizeR = r-m;
	
	elem *auxLeft =  (elem*) malloc(sizeL*sizeof(elem));
	elem *auxRight = (elem*) malloc(sizeR*sizeof(elem));
	
	// Copying the contents
	*moves += r-l+1;
	for(int i = 0; i < sizeL; i++)
		auxLeft[i] = v[l+i];
		
	for(int j = 0; j < sizeR; j++)
		auxRight[j] = v[m+1+j];
	
	// Making the merge
	int i = 0;
	int j = 0;
	int k = l;
	
	while(i < sizeL && j < sizeR){
		*moves += 1;
		*comps += 1;
		if(auxLeft[i] <= auxRight[j]){
			v[k++] = auxLeft[i++];
		} else {
			v[k++] = auxRight[j++];
		}
	}
	
	while(i < sizeL){
		*moves += 1;
		v[k++] = auxLeft[i++];
	}
	
	while(j < sizeR){
		*moves += 1;
		v[k++] = auxRight[j++];
	}
	
	free(auxLeft);
	free(auxRight);
}

void mergeSort(elem* v, int l, int r, int *comps, int *moves){
	
	// Base case
	if(l>=r) return;
	
	int m = (l+r)/2;
	
	mergeSort(v, l, m, comps, moves);
	mergeSort(v, m+1, r, comps, moves);
	merge(v,l, m, r, comps, moves);
	
}

void quickSort(elem* v, int l, int r, int *comps, int *moves){
	
	// Base case
	if(l >= r) return;

	// Chose pivot and send to init
	*moves += 3;
	int p = (l+r)/2;
	swap(v+l, v+p); 
	p = l;
	
	int i = l+1; 
	int j = r;
	
	while(i <= j){
		
		*comps += 1;
		while(i <= r && v[i] <= v[p]){ i++; *comps += 1; }
		
		*comps += 1;
		while(v[j] > v[p]){ j--; *comps += 1; }
		
		if(i < j){
			*moves += 3;
			swap(v+i, v+j);
		}
	}
	
	// Return pivot to the right place
	*moves += 3;
	swap(v+p, v+j);
	p = j;

	quickSort(v, l, p-1, comps, moves);
	quickSort(v, p+1, r, comps, moves);
}


void heapify(elem* v, int size, int n, int *comps, int *moves){
	
	int i = 2*n;
	
	// This is a leaf.
	if(i > size) return;
	
	// Have two children
	if( i+1 <= size){
		*comps += 1;
		i = (v[i] > v[i+1]) ? i : i+1;
	} 
	
	if(v[n] < v[i]){
		*moves += 3;
		swap(v+i, v+n);
		
		heapify(v, size, i, comps, moves);
	}
}

void heapSort(elem* v, int size, int *comps, int *moves){
	
	// Building the Max_Heap - Vector One Based
	int m = size/2;
	for(int i = m; i > 0; i--){
		heapify(v, size, i, comps, moves);
	}
	
	// Making the heapSort
	while(size > 0){
		
		*moves += 3;
		swap(v+1, v+size); 
		
		size--;
		heapify(v, size, 1, comps, moves);
	}
}

















