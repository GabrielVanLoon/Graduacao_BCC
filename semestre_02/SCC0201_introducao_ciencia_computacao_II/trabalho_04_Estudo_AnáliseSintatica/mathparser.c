#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "mathparser.h"


/* FUNÇÕES DE ANÁLISE LÉXICA */
	int _getClass(char c);
	int _caseLetter(char* str, Sequencia* seq, int* i, int strSize, char* lexeme);
	int _caseDigit(char* str, Sequencia* seq, int* i, int strSize, char* lexeme);
	int _caseOperator(char* str, Sequencia* seq, int* i, int strSize, int class);
	int _caseOthers(char* str, Sequencia* seq, int* i, int strSize, char* lexeme);

	int analiseLexica(char* str, Sequencia* seq){
		
		int i, strSize = strlen(str), erro = 0, class;
		char c, lexeme[100];
		
		// preparando a sequencia de lexemas
		seq->vet = malloc(sizeof(Lexema));
		seq->size = 0;

		// Percorre a string gerando os lexemas
		for(i = 0; i < strSize && erro == 0; i++){

			// Le o prox caractere e ignora espaços em branco
			if((c = str[i]) == ' ') continue;

			printf("Char atual %c \n", c);

			switch( (class = _getClass(c)) ){

				case LETTER: 
					erro = _caseLetter(str, seq, &i, strSize, lexeme);
					break;

				case DIGIT:
					erro = _caseDigit(str, seq, &i, strSize, lexeme);
					break;

				case ADD_OP:
				case SUB_OP:
				case MULT_OP:
				case DIV_OP:
					erro = _caseOperator(str, seq, &i, strSize, class);
					break;

				case OTHERS:
					erro = _caseOthers(str, seq, &i, strSize, lexeme);
					break;

				case DOT:
				case COMMA:
				case SEMICOLON:
				default:
					erro = 1;
					break;
			}
		}

		if(erro && seq->vet != NULL) 
			free(seq->vet);

		return erro;
	}

	void printSequencia(Sequencia* seq){
		for(int i = 0; i < seq->size; i++){
			if(seq->vet[i].token == FLOAT_LIT || seq->vet[i].token == INTEGER_LIT)
				printf("<%d,%.02f> ", seq->vet[i].token, seq->vet[i].valor.f);
			else
				printf("<%d> ", seq->vet[i].token);
		}
		printf("\n");
	}

	int _getClass(char c){
		if('a' <= c && c <= 'z') return LETTER;
		if('A' <= c && c <= 'Z') return LETTER;
		if('0' <= c && c <= '9') return DIGIT;
		
		if( c  == '.') return DOT;
		if( c  == ',') return COMMA;
		if( c  == ';') return SEMICOLON;

		if( c  == '+') return ADD_OP;
		if( c  == '-') return SUB_OP;
		if( c  == '*') return MULT_OP;
		if( c  == '/') return DIV_OP;

		return OTHERS;
	}

	int _caseLetter(char* str, Sequencia* seq, int* i, int strSize, char* lexeme){
		
		Lexema aux;
		int j = 0;
		
		// Lendo o lexema
		while(*i < strSize && _getClass(str[*i]) == LETTER){
			lexeme[j++] = str[(*i)++];
		}
		lexeme[j] = '\0';
		--(*i); // Ajuste para não pular chars na str.

		// Verificando se o lexema pertence à uma das classes de token
		if(strcmp(lexeme, "sqrt") == 0)
			aux.token = SQRT2_OP;
		else if(strcmp(lexeme, "exp") == 0) 
			aux.token = EXP2_OP;
		else if(strcmp(lexeme, "log") == 0) 
			aux.token = LOG2_OP;
		else
			return 1;

		seq->size++;
		seq->vet = (Lexema*) realloc(seq->vet, seq->size * sizeof(Lexema));
		seq->vet[seq->size-1] = aux;

		return 0;
	}

	int _caseDigit(char* str, Sequencia* seq, int* i, int strSize, char* lexeme){
		
		Lexema aux;
		int j = 0, class = _getClass(str[*i]);
		
		// Lendo o lexema
		while(*i < strSize && (class == DIGIT || class == DOT)){
			lexeme[j++] = str[(*i)++];
			class = _getClass(str[*i]);
		}
		lexeme[j] = '\0';
		--(*i); // Ajuste para não pular chars na str.

		// Por enquanto, todos os numeros obrigatoriamente serao um float
		aux.token = FLOAT_LIT;
		sscanf(lexeme, "%f", &aux.valor.f);

		seq->size++;
		seq->vet = (Lexema*) realloc(seq->vet, seq->size * sizeof(Lexema));
		seq->vet[seq->size-1] = aux;

		return 0;
	}

	int _caseOperator(char* str, Sequencia* seq, int* i, int strSize, int class){
		Lexema aux;

		// Verifica se é uma multiplicação "a*b" OU exponenciação "a**b" 
		if(class == MULT_OP && (*i)+1 < strSize && str[(*i)+1] == '*'){
			aux.token = EXP_OP;
			(*i) += 1;
		} else{
			aux.token = class;
		}

		seq->size++;
		seq->vet = (Lexema*) realloc(seq->vet, seq->size * sizeof(Lexema));
		seq->vet[seq->size-1] = aux;

		return 0;
	}

	int _caseOthers(char* str, Sequencia* seq, int* i, int strSize, char* lexeme){
		
		Lexema aux;
		int j = 0;
		// lexeme[j] = str[*i];

		// Verificando se o lexema pertence à uma das classes de token
		if(str[*i] ==  '(')
			aux.token = PARENT_LEFT;
		else if(str[*i] ==  ')') 
			aux.token = PARENT_RIGHT;
		else if(str[*i] ==  '{') 
			aux.token = BRACE_LEFT;
		else if(str[*i] ==  '}') 
			aux.token = BRACE_RIGHT;
		else if(str[*i] ==  '[') 
			aux.token = BRACKET_LEFT;
		else if(str[*i] ==  ']') 
			aux.token = BRACKET_RIGHT;
		else
			return 1;

		seq->size++;
		seq->vet = (Lexema*) realloc(seq->vet, seq->size * sizeof(Lexema));
		seq->vet[seq->size-1] = aux;

		return 0;
	}

/* FUNÇÕES DE ANÁLISE LÉXICA */
	float _expr(Sequencia* seq, int* erro);
	float _add(Sequencia* seq, int* erro);
	float _mult(Sequencia* seq, int* erro);
	float _expo(Sequencia* seq, int* erro);

	Lexema _currentLex(Sequencia* seq);
	int _step(Sequencia* seq);
	int _currentToken(Sequencia* seq);
	int _nextToken(Sequencia* seq);

	float analiseSintatica(Sequencia* seq, int* erro){
		float result = 0;
		
		// Preparando as variaveis para a analise
		seq->current = 0;
		*erro = 0;

		result = _expr(seq, erro);

		// Casos de erro: 
		// - A BNF não construiu a sequencia inteira
		// - Ocorreu o erro em alguma das regras
		if(_step(seq) != EMPTY_SEQUENCE)
			*erro = 1;

		return result;
	}

	// REGRA INICIAL: 	<expr> := <add>  {(+|-) <add>}
	float _expr(Sequencia* seq, int* erro){

		printf("Função <expr> no token %d\n", seq->current);

		float result;
		int currentToken = _currentToken(seq);

		result = _add(seq, erro);

		currentToken = _currentToken(seq);
		while( *erro == 0 && (currentToken == ADD_OP || currentToken == SUB_OP)){
			
			_step(seq);
			
			float add = _add(seq, erro);
			result = (currentToken == SUB_OP) ? result - add : result + add;
			
			//Atualizando o currentToken
				currentToken = _currentToken(seq);
		}

		printf("Função <expr> retornou %f\n", result);

		return result;
	}

	// REGRA 2ª: 		<add>  := <mult> {(*|/) <mult>}
	float _add(Sequencia* seq, int* erro){

		printf("Função <add> no token %d\n", seq->current);

		float result;
		int currentToken = _currentToken(seq);

		result = _mult(seq, erro);

		currentToken = _currentToken(seq);
		while( *erro == 0 && (currentToken == MULT_OP || currentToken == DIV_OP)){
			_step(seq);
			
			float mult = _mult(seq, erro);
			result = (currentToken == MULT_OP) ? result*mult : result/mult;
			
			//Atualizando o currentToken
			currentToken = _currentToken(seq);
		}

		printf("Função <add> retornou %f\n", result);

		return result;
	}

	// REGRA 3ª: 		 <mult> := <expo> {** <expo>}
	float _mult(Sequencia* seq, int* erro){
		
		printf("Função <mult> no token %d\n", seq->current);

		float result;

		result = _expo(seq, erro);

		while( *erro == 0 && (_currentToken(seq) == EXP_OP)){
			_step(seq);
			float expo = _expo(seq, erro);
			result = pow(result, expo);
		}

		printf("Função <mult> retornou %f\n", result);

		return result;
	}

	// REGRA 4ª: 		 	<expo> := 'x' 
	//			            | (+|-) 'x'
	//          			| (<expr>) | {<expr>} | [<expr>]
	//			  			| sqrt<expr> | exp <expr> | log<expr>
	float _expo(Sequencia* seq, int* erro){

		printf("Função <expo> no token %d\n", seq->current);

		int currentToken = _currentToken(seq);
		int nextToken   = _nextToken(seq);
		Lexema aux;

		if(currentToken == FLOAT_LIT) {
			aux = _currentLex(seq);
			_step(seq);
			return aux.valor.f;
		
		} else if(currentToken == ADD_OP && nextToken == FLOAT_LIT){
			_step(seq);
			aux = _currentLex(seq);
			_step(seq);
			return aux.valor.f;
		
		} else if(currentToken == SUB_OP && nextToken == FLOAT_LIT){
			_step(seq);
			aux = _currentLex(seq);
			_step(seq);
			return -aux.valor.f;
		
		} else if(currentToken == PARENT_LEFT){
			_step(seq);
			float expr = _expr(seq, erro);

			currentToken = _currentToken(seq);
			// Executou a expr sem nenhum erro e fechou a parenteses
			if(currentToken == PARENT_RIGHT && *erro == 0){
				_step(seq);
				return expr;
			}

		} else if(currentToken == BRACE_LEFT){
			_step(seq);
			
			float expr = _expr(seq, erro);

			currentToken = _currentToken(seq);
			
			// Executou a expr sem nenhum erro e fechou a chave
			if(currentToken == BRACE_RIGHT && *erro == 0){
				_step(seq);
				return expr;
			}
		
		} else if(currentToken == BRACKET_LEFT){
			_step(seq);
			float expr = _expr(seq, erro);

			currentToken = _currentToken(seq);
			
			// Executou a expr sem nenhum erro e fechou o colchete
			if(currentToken == BRACKET_RIGHT && *erro == 0){
				_step(seq);
				return expr;
			}
		
		} else if(currentToken == SQRT2_OP){
			
			_step(seq);
			currentToken = _currentToken(seq);

			// Verifica se abriu parenteses, chaves ou colchetes
			if(currentToken != PARENT_LEFT && currentToken != BRACE_LEFT && currentToken != BRACKET_LEFT){
				*erro = 1;
				return 1;
			}

			_step(seq); 
			float expr = _expr(seq, erro);
			
			// Executou a expr corretamente e fechou com o token corretoc
			if(*erro == 0 && (currentToken+1) == _currentToken(seq)){
				_step(seq); 
				return (float) sqrt(expr);
			}
		
		} else if(currentToken == EXP2_OP){
			
			_step(seq);
			currentToken = _currentToken(seq);

			// Verifica se abriu parenteses, chaves ou colchetes
			if(currentToken != PARENT_LEFT && currentToken != BRACE_LEFT && currentToken != BRACKET_LEFT){
				*erro = 1;
				return 1;
			}

			_step(seq); 
			float expr = _expr(seq, erro);
			
			// Executou a expr corretamente e fechou com o token corretoc
			if(*erro == 0 && (currentToken+1) == _currentToken(seq)){
				_step(seq); 
				return expr * expr;
			}

		} else if(currentToken == LOG2_OP){
			
			_step(seq);
			currentToken = _currentToken(seq);

			// Verifica se abriu parenteses, chaves ou colchetes
			if(currentToken != PARENT_LEFT && currentToken != BRACE_LEFT && currentToken != BRACKET_LEFT){
				*erro = 1;
				return 1;
			}

			_step(seq); 
			float expr = _expr(seq, erro);
			
			// Executou a expr corretamente e fechou com o token corretoc
			if(*erro == 0 && (currentToken+1) == _currentToken(seq)){
				_step(seq); 
				return log(expr) / log(2);
			}

		} 

		*erro = 1;
		return 1;
	}

	Lexema _currentLex(Sequencia* seq){
		return seq->vet[seq->current];
	}

	int _step(Sequencia* seq){
		if(seq->current+1 >= seq->size)
			return EMPTY_SEQUENCE;
		seq->current += 1;
		return 0;
	}

	int _currentToken(Sequencia* seq){
		return seq->vet[seq->current].token;
	}

	int _nextToken(Sequencia* seq){
		if(seq->current+1 >= seq->size) 
			return EMPTY_SEQUENCE;
		return seq->vet[seq->current+1].token;
	}