#ifndef ORDER_H
	#define ORDER_H
	
	typedef int elem;
	
	void bubbleSort(elem* v, int size, int *comps, int *moves);

	void insertionSort(elem* v, int size, int *comps, int *moves);
	
	void mergeSort(elem* v, int l, int r, int *comps, int *moves);
	
	void quickSort(elem* v, int l, int r, int *comps, int *moves);
	
	void heapSort(elem* v, int size, int *comps, int *moves);
	
#endif
