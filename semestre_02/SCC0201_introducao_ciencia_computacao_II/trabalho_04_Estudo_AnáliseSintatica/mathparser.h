#ifndef MATHPARSER_H
	#define MATHPARSER_H
	
	/**
	 * Definindo os TOKENS dos LEXEMAS
	 */	
		// Classes Gramaticais
		#define LETTER    1
		#define DIGIT     2
		#define DOT       3
		#define COMMA     4
		#define SEMICOLON 5
		#define OTHERS    0

		// Valores literais / terminais
		#define INTEGER_LIT   6
		#define LONGINT_LIT   7
		#define FLOAT_LIT     8
		#define DOUBLE_LIT    9
		
		// Operadores binarios
		#define ADD_OP    10
		#define SUB_OP    11
		#define MULT_OP   12
		#define DIV_OP    13
		#define EXP_OP    14
		
		// Operadores Unarios		
		#define SQRT2_OP   15
		#define EXP2_OP    16
		#define LOG2_OP    17
		
		// Parenteses(), chaves{braces} e colchetes[brackets]
		#define PARENT_LEFT   20
		#define PARENT_RIGHT  21
		#define BRACE_LEFT    23
		#define BRACE_RIGHT   24
		#define BRACKET_LEFT  25
		#define BRACKET_RIGHT 26

		#define EMPTY_SEQUENCE -1
	
	/**
	 * ANALISE LÉXICA
	 * - Recebe uma string que representa uma expressão matemática e converte
	 * em uma sequência de Lexemas.
	 */
		// Union auxiliar para otimizacao do typedef Lexema
		typedef union _value{
			char  c[4];
			int   i;
			float f;
		} Value;

		typedef struct _lexema{
			int token;   //Classe do lexema
			Value valor; // Valor do lexema caso exista
		} Lexema;

		typedef struct _seq{
			Lexema* vet;
			int size;
			int current; // Index auxiliar utilizada na @analiseSintatica()
		} Sequencia;

		/**
		 * @int analiseLexica(char* str, Lexema* seq)
		 * 
		 * - Recebe uma expressão matemática e executa o processo de análise
		 *   léxica.
		 * - Retorna em caso de sucesso ou 1 para caso de falha.
		 * - Exemplos de erros léxicos: Palavras reservadas escritas incorreta-
		 *   mente; Variáveis não declaradas na tabela. 
		 */
		int analiseLexica(char* str, Sequencia* seq);

		/**
		 * @void printSequencia(Sequencia* seq);
		 * 
		 * - Imprime os tokens de uma sequência de Lexemas. Caso um Lexema 
		 *   possua um valor agregado (e.g. um FLOAT com valor 1.5) exibe 
		 *   também esse valor na forma "<token,valor>"
		 */
		void printSequencia(Sequencia* seq);

	/**
	 * ANALISE SINTÁTICA
	 * 
     * - Recebe uma sequência de lexemas e, por meio das regras de uma gramática
     *   livre de contexto, gera uma Arvore de Análise Sintática (Parse Tree).
     * - Utiliza-se de um Algoritmo de Derivação Top-Down "LL"
     *	
     * BNF Extendida (Formas de Backus-Naur)
     * 
     * - Regras que vão regir as expressões matemáticas desse programa.
     * - Seja o Símbolo inicial <expr> e 'x' representando um valor terminal:
	 *
	 *	<expr> := <add>  {(+|-) <add>}
	 *  <add>  := <mult> {(*|/) <mult>}
	 *  <mult> := <expo> {** <expo>}
	 *  <expo> := 'x' 
	 *            | (+|-) 'x'
	 *            | (<expr>)      | {<expr>}      | [<expr>]
	 *			  | sqrt (<expr>) | sqrt {<expr>} | sqrt [<expr>]  
	 *            | exp  (<expr>) | exp  {<expr>} | exp  [<expr>]  
	 *            | log  (<expr>) | log  {<expr>} | log  [<expr>]  
	 *
	 * Obs.: Como essa gramática estará lidando apenas com expressões matemá-
	 *       ticas, a Parse Tree Será construida apenas abstratamente, não 
	 *       sendo necessário criar uma struct que salve as suas informações.
	 */

		/**
		 * @int analiseSintatica(Sequencia* seq, int* erro);
		 * 
		 * - Recebe uma sequência de lexemas e aplica as regras BNF estabele-
		 *   cidas pela gramática.
		 * - Retorna 0 em caso de sucesso e 1 em caso de erro.		 
		 * - Exemplos de erros sintáticos: Não fechar um escopo; expressões 
		 *   mal formadas; 
		 */
		float analiseSintatica(Sequencia* seq, int* erro);


#endif