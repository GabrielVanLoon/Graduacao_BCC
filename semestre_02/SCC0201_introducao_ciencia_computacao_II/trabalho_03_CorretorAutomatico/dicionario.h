#ifndef DICTIONARY_H
	#define DICTIONARY_H
	
	#define STR_MAX_SIZE 60
	#define MALLOC_BLOCK_SIZE 10000
	
	/**
	 * @typedef Dictionary
     * 
     * Description:
     *    The Dictionary is a TAD that holds a dinamic matrix of strings. It
     *    uses O(n.log(n)) ordenation method and O(log(n)) search method.
     *    To avoid reallocation after every string input, it mallocs memory in
     *    blocks with defined size.
     *
     *
	 * Variabels:
	 *    vet:           The pointer to the dynamic matrix.
	 *    size:          Number of words the dictionary have.
	 *    malloc_size:   Number of blocks that are allocated
	 */
	typedef struct _dictionary{
		char** vet;
		int size;
		int malloc_size;
	}Dictionary;

	/**
	 * @Dictionary newDictionary()
	 * Prepares a new instance of Dictionary variable for use.
	 */
	Dictionary newDictionary();

	/**
	 * @Dictionary newDictionary()
	 * Frees the alocated memory to prevent memories leaks.
	 */
	void freeDictionary(Dictionary *d);

	/**
	 * @Dictionary newDictionary()
	 * Inserts a new string into the Dictionary file.
	 */
	void insertWord(Dictionary *d, char* word);

	/**
	 * @int fillWithFile(Dictionary *d, char* fileLocation);
	 * Given a fileLocation, fill the dictionary with all strings in the
	 * txt file.
	 * 
	 * Returns 0 when success and 1 when it fails
	 */
	int fillWithFile(Dictionary *d, char* fileLocation);

	/**
	 * @void printDictionary(Dictionary *d);
	 * Print all words saved in the dictionary.
	 */
	void printDictionary(Dictionary *d);

	/**
	 * @void sortDitionary(Dictionary *d);
	 * Sort the words in the dictionary using the merge sort.
	 */
	void sortDictionary(Dictionary *d);

	/**
	 * @void sortDitionary(Dictionary *d);
	 * Remove the reapeated words of a sorted dictionary.
	 */
	void removeRepeatWords(Dictionary *d);
	
	/**
	 * @int searchForWord(Dictionary *d, char *str);
	 * Searches if the given string exists in the dictionary.
	 *
	 * Returns the index position of the word or -1 in failure case
	 */
	int searchForWord(Dictionary *d, char *str);

	/**
	 * @void _removeNonAlphabetic(char* s, char r);
	 * This is a helper function that is visible to the main.c file.
	 * Given a string and a replace char, it will replace all non alphabetic
	 * characteres.
	 */
	void _removeNonAlphabetic(char* s, char r);

#endif