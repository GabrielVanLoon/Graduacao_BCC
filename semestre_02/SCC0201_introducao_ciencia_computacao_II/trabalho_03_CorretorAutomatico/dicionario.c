#include "dicionario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Helpers Header
void _strToLower(char* w);
void _merge(Dictionary *d, int l, int m, int r);
void _mergeSort(Dictionary *d, int l, int r);
int _binarySearch(Dictionary *d, int l, int r, char* w);

// Main Functions
Dictionary newDictionary(){
	Dictionary temp;
	temp.size = 0;
	temp.malloc_size = 1;
	temp.vet = (char**) malloc( MALLOC_BLOCK_SIZE * temp.malloc_size * sizeof(char*));
	return temp;
}

void freeDictionary(Dictionary *d){
	if(d->vet != NULL){
		for(int i = 0; i < d->size; i++)
			free(d->vet[i]);

	 	free(d->vet);
	}
}

int fillWithFile(Dictionary *d, char* fileLocation){

	char  aux[STR_MAX_SIZE];
	FILE* file = fopen(fileLocation, "r");
	
	// Error: The file does not exists.
	if(file == NULL)
		return 1;

	while(fscanf(file, "%[a-zA-Z]%*[^a-zA-Z]", aux) != EOF){	
		// printf("String aux %s", aux);
		insertWord(d, aux);
	}

	fclose(file);
	return 0;
}

void insertWord(Dictionary *d, char* w){

	_strToLower(w);
	
	// Increasing the words count
	d->size++;

	// Increasing the size of the malloc
	if( d->malloc_size * MALLOC_BLOCK_SIZE <= d->size ){
		d->malloc_size++;
		d->vet = (char**) realloc(d->vet, MALLOC_BLOCK_SIZE * d->malloc_size * sizeof(char*));
	}

	// copying the string to the dictionary
	d->vet[d->size-1] = malloc(STR_MAX_SIZE * sizeof(char));
	strcpy(d->vet[d->size-1], w);
}

void printDictionary(Dictionary *d){
	for(int i = 0; i < d->size; i++)
		printf("%06d - %s\n", i, d->vet[i]);
}

void sortDictionary(Dictionary *d){
	_mergeSort(d, 0, d->size-1);
}

void removeRepeatWords(Dictionary *d){
	// i - iterator of loop
	// j - array is correct in [0,1,2 ... j]
	int i, j = 0;
	for(i = 1; i < d->size; i++){
		
		if(strcmp(d->vet[j], d->vet[i]) == 0) {
			free(d->vet[i]); // duplicated word
		
		} else {
			d->vet[j+1] = d->vet[i];
			j++;

		}
	}

	// Adjusting the size of the Dictionary
	d->size = j+1;
}

int searchForWord(Dictionary *d, char *str){
	char temp[STR_MAX_SIZE];
	
	strcpy(temp, str);

	_strToLower(temp);
	
	return _binarySearch(d, 0, d->size-1, temp);
}

// Helpers
void _removeNonAlphabetic(char* s, char r){
	for(int i = 0; i < strlen(s); i++){
		if('a' <= s[i] && s[i] <= 'z')
			continue;
		if('A' <= s[i] && s[i] <= 'Z')
			continue;

		s[i] = r;
	}
}

void _strToLower(char* w){
	for(int i = 0; i < strlen(w); i++){
		w[i] = tolower(w[i]);
	}
}

void _mergeSort(Dictionary *d, int l, int r){
	// Stop case
	if(l >= r) return;

	int m = (l + r)/2;

	_mergeSort(d, l, m);
	_mergeSort(d, m+1, r);
	
	_merge(d, l, m, r);
}

void _merge(Dictionary *d, int l, int m, int r){

	int i = l, j = 0, k = 0;
	int sizeL = m-l+1, sizeR = r-m;

	char** left  = (char**) malloc(sizeL*sizeof(char*));
	char** right = (char**) malloc(sizeR*sizeof(char*));

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
		if( strcmp(left[j], right[k]) <= 0)
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

int _binarySearch(Dictionary *d, int l, int r, char* w){

	if(l > r) return -1;

	int m = (l+r)/2;

	int pos = strcmp(w, d->vet[m]);

	if(pos == 0) return m;
	
	else if(pos < 0) return _binarySearch(d, 0, m-1, w);
	
	else return _binarySearch(d, m+1, r, w);
}