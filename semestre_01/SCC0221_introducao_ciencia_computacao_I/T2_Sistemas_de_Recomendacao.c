/**
 * Trabalho de Introdução a Ciencia da Computacao
 * Título: Sistema de Recomendacao
 * Autor:  Gabriel Van Loon
 * Prof.:  Moacir Ponti
 * Data:   Abril/2018
 * 
 * Resumo:
 * Programa para predizer a nota que um usuario atribuiria a um item
 * que ele ainda nao avaliou baseando-se nas notas de usuarios com
 * preferencias similares a dele.
 *
 * Descricao:
 * - O programa preenche uma matriz listando as notas que usuários deram para
 *   uma coletânea de filmes de diferentes gêneros. 
 * - A segunda matriz que o programa preenche é a similaridade entre os usuários, 
 *   gerando uma matriz quadrada cujos valores variam entre [0,1]
 * - Em seguida, o programa percorre os itens dessa matriz buscando por filmes 
 *   que os usuários ainda não tenham visto e tenta predizer qual será sua avaliação
 *   baseado nas notas dos usuários cuja similaridade são maiores que o limiar
 *   recebido via input.
 *
 * 
 * Entradas:
 *     @qtd_usuarios
 *     @qtd_itens
 *     @limiar:
 *     @notas[usuario][item]
 *     @similaridade[usuario][usuario]
 * 
 */
 
 # include <stdio.h>
 # include <math.h>
 
 // Prototypes
 double calcular_similaridade(int qtd_itens, int* notas_a, int* notas_b);
 double calcular_media_notas(int qtd_itens, int* notas);
 double predizer_nota(int qtd_usuarios, double media_usuario, double usuarios_similares[][3]);
 
 int main(int argc, char *argv[]){
	
	int qtd_usuarios, qtd_itens;
	double limiar;
	
	scanf(" %d", &qtd_usuarios);  
	scanf(" %d", &qtd_itens);  
	scanf(" %lf", &limiar);
	
	int notas[qtd_usuarios][qtd_itens];
	double similaridade[qtd_usuarios][qtd_usuarios];
	
	// Preenchendo a matriz @notas
	for(int u = 0; u < qtd_usuarios; u++){
	   for(int i = 0; i < qtd_itens; i++){
		   scanf(" %d", &notas[u][i]);
	   }
	}
	
	/**
	* Preenchendo a matriz @similaridade:
	* Preenche a matriz entre o usuario 'u1' e 'u2', tal que 
	*     
	*     similaridade[u1][u2] = similaridade[u2][u1] (Matriz Simetrica)
	* 
	* Exemplo de funcionamento do loop de preenchimento:
	* 
	*     Dados os usuarios A, B, C e D. Os simbolos: 
	*     a: Valores obtidos na primeira iteracao.
	*     b: Valores obtidos na segunda iteracao.
	*     c: Valores obtidos na terceira iteracao.
	*     -: Valores nao calculados.
	* 
	*     Matriz @similaridade de A,B,C e D:
	* 	  
	*         [A] [B] [C] [D]
	*     [A]  -   a   a   a
	*     [B]  a   -   b   b
	*     [C]  a   b   -   c
	*     [D]  a   b   c   -
	* 
	*/
	for(int u1 = 0; u1 < qtd_usuarios; u1++){
	   for(int u2 = u1 + 1; u2 < qtd_usuarios; u2++){	   
		   similaridade[u1][u2] = similaridade[u2][u1] = calcular_similaridade(qtd_itens, notas[u1], notas[u2]);
	   }
	}
	
	// Predizendo as notas
	for(int u = 0; u < qtd_usuarios; u++){
	   
	   char mostrar_quebra = 'n';
	   double media_usuario = calcular_media_notas(qtd_itens, notas[u]);
	   
	   for(int i = 0; i < qtd_itens; i++){
		   
		   // Caso o usuario ja tenha avaliado este item, vai para o proximo item
		   if(notas[u][i] != 0){
		       continue;
		   } else {
			   mostrar_quebra = 's';
		   }
		   
		   int qtd_usuarios_similares = 0;
		   double nota_prevista, usuarios_similares[qtd_usuarios-1][3];
		   
		   for(int u_similar = 0; u_similar < qtd_usuarios; u_similar++){
		       
		       /**
			   * Filtrando quais usuarios serao utilizados para predizer a nota
			   * 
			   * Caso:
			   *     1º O usuario 'u_similar' seja o usuario 'u'
			   *     2º A similaridade entre 'u' e 'u_similar' nao ultrapassa o limiar
			   *     3º O usuario 'u_similar' tambem nao avaliou o item 'i' ainda
			   * 
			   * O usuario 'u_similar' nao sera utilizado para o calculo de predicao.
			   */
		       if( u_similar == u || similaridade[u][u_similar] <= limiar || notas[u_similar][i] == 0 ){
		           continue;
		       }
		       
		       /**
		       * Para cada Usuario na matriz de usuarios_similares
		       *     [0]: valor da similaridade
		       *     [1]: nota dada para o item i
		       *     [2]: media das notas do usuario
		       */
		       usuarios_similares[qtd_usuarios_similares][0] = similaridade[u][u_similar];
		       usuarios_similares[qtd_usuarios_similares][1] = (double) notas[u_similar][i];
		       usuarios_similares[qtd_usuarios_similares][2] = calcular_media_notas(qtd_itens, notas[u_similar]);
		       
		       qtd_usuarios_similares++;
		   }
		   
		   /**
		   * Nota prevista do usuario 'u' para o item 'i' utilizando
		   * utilizando a media das notas do usuario 'u' e tambem dados
		   * de usuarios similares.
		   */ 
		   nota_prevista = predizer_nota(qtd_usuarios_similares, media_usuario, usuarios_similares);
		   
		   if(nota_prevista > 0)
		      printf("%.2lf ", nota_prevista);
		   else
		      printf("DI ");
		   
	   }
	   
	   if(mostrar_quebra == 's')
	      printf("\n");
    }
	
	return 0;
 }
 
 /**
 * Funcao: Calcular Similaridade
 * 
 * Calcula a similaridade entre o vetor de notas de dois usuarios A e B 
 * utilizando a equacao matematica Cosseno, tal que:
 * 
 *     cos(A,B) = produto_escalar(A,B) / (norma(A) * norma(B))
 * 
 * A função então retorna o valor de cos(A,B) que varia entre 0 e 1.
 * Quanto mais proximo de 1, maior e a similaridade entre os dois usuarios.
 * 
 * Entradas:
 *     @qtd_itens:  Quant. de notas nos arrays seguintes.
 *     @notas_a:    Array de notas do usuario A.
 *     @notas_b:    Array de notas do usuario B.
 * 
 * Retorno:
 *     @cos_ab:     Valor da similaridade entre A e B.
 */
 double calcular_similaridade(int qtd_itens, int* notas_a, int* notas_b){
	 
	 double cos_ab, prod_escalar = 0, norma_a = 0, norma_b = 0;
	 
	 for(int i = 0; i < qtd_itens; i++){
		 prod_escalar += (double) notas_a[i] * notas_b[i]; 
         norma_a      += (double) pow(notas_a[i], 2);
	     norma_b      += (double) pow(notas_b[i], 2);
	 }
	 
	 cos_ab = prod_escalar / (sqrt(norma_a) * sqrt(norma_b));
	 
	 return cos_ab;
 }
 
 /**
  * Funcao Calcular Media das Notas
  * 
  * Calcula a media das notas de um usuario levando em conta apenas os
  * itens que ja foram avaliados por ele.
  * 
  * Entradas:
  *     @qtd_itens:    Quant. itens no array de notas.
  *     @notas:        Array de notas do usuario.
  * 
  * Retorno:
  *     @media:        Media das avaliacoes.
  */
 double calcular_media_notas(int qtd_itens, int* notas){
     
     int qtd_itens_avaliados = 0;
     double media = 0, soma = 0;
     
     for(int i = 0; i < qtd_itens; i++){
	     
	    // Caso o usuario nao tenha avaliado este item, ignore
	    if(notas[i] == 0)
		    continue; 
		 
		soma += (double) notas[i];
	    qtd_itens_avaliados++;
	 
	 }
     
     if(qtd_itens_avaliados > 0)
	     media = soma / (double) qtd_itens_avaliados;
	 else
	     media = 0;
     
     return media;
 }
 
 /**
 * Funcao: Predizer Nota
 * 
 * Calcula a nota que o usuario daria para um item que ele ainda nao avaliou
 * utilizando como parametro a media das notas de suas outras avaliacoes
 * e os dados de outros usuarios com preferencias similares
 * 
 * Entradas:
 *     @qtd_usuarios:   Quant. de usuarios com preferencias similares.
 *     @media_usuario.
 *     @usuarios_similares[usuario][ {@similaridade, @nota_item, @media} ]
 *         @similaridade: Grau de similaridade com o usuario e o usuario similar
 *         @nota: Nota que o usuario similar deu para o mesmo item
 *         @media: Media de notas do usuario similar
 * 
 * Retorno:
 *     @nota_prevista:   Nota prevista pelo calculo.
 */
 double predizer_nota(int qtd_usuarios, double media_usuario, double usuarios_similares[][3]){
	 
	 double soma_notas = 0, soma_similaridades = 0; 
	 double nota_prevista = 0;
	 
	  // printf(" (%lf) - ", media_usuario);

	 for(int u = 0; u < qtd_usuarios; u++){
	     soma_notas += usuarios_similares[u][0] * ( usuarios_similares[u][1] - usuarios_similares[u][2]);
		 soma_similaridades += usuarios_similares[u][0];

		 // printf(" %lf*(%lf - %lf) + ", usuarios_similares[u][0], usuarios_similares[u][1], usuarios_similares[u][2]);
	 }
	 
	 // printf("\n", media_usuario);

	 nota_prevista = media_usuario + (soma_notas / soma_similaridades);
	 
	 return nota_prevista; 
		   
 }
