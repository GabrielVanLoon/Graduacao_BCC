/**
 * Trabalho de Introdução a Ciencia da Computacao II
 * Título: T3 - Corretor Automático 
 * Autor:  Gabriel Van Loon
 * Prof.:  Moacir Ponti
 * Data:   Setembro/2018

 * Description:
 *    O programa receberá dois arquivos: um book.txt, que servirá para popular  
 *    um dicionário de palavras conhecidas, e um tweet.json, que será 
 *    percorrido a fim de extrair seus textos e analizar suas palavras pelo 
 *    corretor.
 * 
 * Input:
 *    nameBook:   localizacao do arquivo book.txt
 *    nameTweets: localizacao do arquivo tweets.json
 *
 * Output:
 *    Para cada tweet encontrado no json, imprime a lista de palavras que não
 *    foram encontradas no dicionário.
 *
 *    Obs: As palavras compostas ou que contenham caracteres especiais são 
 *    vistas como palavras distintas 
 *    Ex.: Guarda-Chuva => [Guarda, Chuva]
 *         They're      => [They, re] 
 *
 * Obs: Nesse trabalho eu tentei utilizar os comentários e os nomes de
 * variáveis em inglês para ver como eu me saia.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dicionario.h"

// Header

int main(void){

	/**
	 * Main Variables: 
	 *    nameBook[]:     location of book.txt file.
	 *    nameTweets[]:   Location of tweets.json file.
	 *	  dic:            Dictionary of the corrector.
	 *
	 *    json:           Pointer to the JSON file.
	 *    tweetsCounter:  Count how many tweets has in the tweet.json file.        
	 */
	char nameBook[STR_MAX_SIZE], nameTweets[STR_MAX_SIZE];
	Dictionary dic;

	FILE *json;
	int tweetsCounter = 0;

	/**
	 * First, the program will read the location of the two files. Then, will
	 * try to use the Book.txt to fill the Dictionary with distinct words.
	 * 
	 * If the location received is wrong, the program throws a error and stop
	 * the execution.
	 */
		dic = newDictionary();

		scanf("%s", nameBook);
		scanf("%s", nameTweets);
	
		if(fillWithFile(&dic, nameBook)){
			printf("Wrong book.txt location, try again.\n");
			freeDictionary(&dic);
			return 1;
		}

		sortDictionary(&dic);
		
		removeRepeatWords(&dic);
		
		// printDictionary(&dic);


	/**
	 * Now the program will scan the Tweets.json file line by line searching
	 * for Tweets. For every match, it will uses the dictionary to
	 * verify every word in the phrase and printf those that do not exist.
	 * 
	 * Auxiliar Variables: 
	 *    firstStr:    Helper to adjust the printf of the lines.
	 *    jsonKey:     Saves the key of this line of the json.
	 *    jsonLine:    Keeps the content of a line of the json.
	 *    word:        Saves the words of the line.
	 *    maxLength:   The max quantity of chars to read in a line.
	 */
		char firstStr;
		char *jsonLine, *word, jsonKey[STR_MAX_SIZE];
		size_t maxLength = 400;

		// Open the json file
		json = fopen(nameTweets, "r");
		if(json == NULL){
			printf("Wrong Tweets.json location, try again.\n");
			freeDictionary(&dic);
			return 1;
		}

		// Starting to read the lines
		jsonLine = malloc(maxLength * sizeof(char));

		while(getline(&jsonLine, &maxLength, json) > 0){

			// Verify if this is a ["text": "Tweet content",] line.
			sscanf(jsonLine, "%s", jsonKey);
			
			if(strcmp("\"text\":", jsonKey) != 0) 
				continue;

			// Remove all the symbols and replace by blank spaces.
			_removeNonAlphabetic(jsonLine, ' ');

			// Split the phrase into words and ignore the "text" string
			word = strtok(jsonLine, " ");
			word = strtok(NULL, " "); 

			firstStr = 'y';
			while(word != NULL){
				
				// If the word does not exist, printf.
				if(searchForWord(&dic, word) == -1){
					
					if(firstStr == 'y') {
						printf("%s", word);
						firstStr = 'n';
					} else
						printf(" %s", word);
					
				}

				word = strtok(NULL, " ");
			}

			printf("\n"); tweetsCounter++;
		}

		// Free the alocated memory
		free(jsonLine);
		fclose(json);

		// If there was no tweet in the json, print
		if(tweetsCounter == 0)
			printf("No tweets to check\n");

	// If nothing went wrong until here, job is done!!
	freeDictionary(&dic);

	return 0;
}