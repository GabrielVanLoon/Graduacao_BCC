/**
 * Trabalho de Introdução a Ciencia da Computacao
 * Título: Balanceamento de recursos
 * Autor:  Gabriel Van Loon
 * Prof.:  Moacir Ponti
 * Data:   maio/2018
 * 
 * Descricao:
 *   Programa que calcula se a distribuicao de recursos de um jogo com 
 * 2 jogadores eh justa, utilizando-se de um mapa 2D representada por
 * uma matriz 9x9.
 *   Uma formula eh utilizada para verificar o custo de exploracao que cada
 * um dos jogadores (E1 e E2) tera para alcancar todos os recursos do jogo.
 *   Quanto menor o valor, mais proximos estao o recurso de sua posicao
 * inicial.
 *   Se a diferenca absoluta entre E1 e E2 for superior a 0.001, entao o
 * jogador cujo valor de exploracao for menor tera vantagem sobre o outro.
 * 
 * Entradas:
 * 		@mapa[][]:	Valor 0 quando transponivel, 1 quando intransponivel
 * 		@pos1:		Coordenada inicial do jogador 1
 * 		@pos2:		Coordenada inicial do jogador 2
 * 		@nRec:		Quantidade de recursos no mapa
 * 		@recursos[] Vetor de coordenadas dos N recursos
 * 
 * Saida:
 * 		@E1: Valor de exploracao do jogador 1
 * 		@E2: Valor de exploracao do jogador 2
 * 		@"O mapa eh balanceado" ou "O jogador %d possui vantagem"
 */
 # include <stdio.h>
 # include <stdlib.h>
 # include <math.h>
 
 # define QTD_LINHAS 9
 # define QTD_COLUNAS 9
 
 typedef struct _coordenada{
	int l;
	int c;
 } Coordenada;

// Prototipos de funcoes
int flood_fill(int mapa[QTD_LINHAS][QTD_COLUNAS], int explore[QTD_LINHAS][QTD_COLUNAS], Coordenada pos, int distancia);

int main(){
	
	/**
	 * Variaveis:
	 * 		@explore1:	Distancia da base do jogador 1 para cada campo
	 * 		@explore2:	.............................2................
	 * 		@campos_transponiveis: Quantidade de campos transp. no mapa
	 *
	 * 		@dif:			Diferenca de E1 e E2
	 * 		@soma_dist_N: 	Utilizada no calculo de E1 e E2
	 */
	
	int nRec, campos_transponiveis = 0;
	int mapa[QTD_LINHAS][QTD_COLUNAS], explore1[QTD_LINHAS][QTD_COLUNAS] = {0}, explore2[QTD_LINHAS][QTD_COLUNAS] = {0};
	Coordenada pos1, pos2, *recursos;
	
	double E1, E2, dif; 
	double soma_dist_1 = 0, soma_dist_2 = 0;
	
	// Preenchendo o mapa
	for(int i = 0; i < QTD_LINHAS; i++){
		for(int j = 0; j < QTD_COLUNAS; j++){
			scanf(" %d", &mapa[i][j]);
			if(mapa[i][j] == 0) campos_transponiveis++;
		}
	}
	
	// Posicao jogador 1
	scanf(" %d", &pos1.l);
	scanf(" %d", &pos1.c);
	
	// Posicao jogador 2
	scanf(" %d", &pos2.l);
	scanf(" %d", &pos2.c);
	
	// Preenchendo os recursos
	scanf(" %d", &nRec);
	recursos = malloc( nRec * sizeof(Coordenada));
	
	for(int i = 0; i < nRec; i++){
		scanf(" %d", &recursos[i].l);
		scanf(" %d", &recursos[i].c);
	}
	
	// Executando Flood Fill dos Jogadores
	flood_fill(mapa, explore1, pos1, 1);
	flood_fill(mapa, explore2, pos2, 1);
	
	// Calculo de exploracao para os jogadores
	for(int i = 0; i < nRec; i++){
		int rec_l = recursos[i].l;
		int rec_c = recursos[i].c;
		
		soma_dist_1 += explore1[rec_l][rec_c]/(double)campos_transponiveis;
		soma_dist_2 += explore2[rec_l][rec_c]/(double)campos_transponiveis;
	}
	
	E1 = (1/(double)(nRec)) * soma_dist_1;
	E2 = (1/(double)(nRec)) * soma_dist_2;
	
	dif = E1 - E2;
	
	// Saidas
	printf("%lf\n", E1);
	printf("%lf\n", E2);
	
	if( fabs(dif) > (double) 0.001){
		
		if(E1 < E2)
			printf("O jogador 1 possui vantagem\n");
		else
			printf("O jogador 2 possui vantagem\n");
			
		
	} else {
		printf("O mapa eh balanceado\n");	
	}
	
	free(recursos);
	
	return 0;
 }

 
 /**
  * Funcao: Flood Fill
  * 
  *   Dada uma coordenada inicial, preenche a matriz de exploracao com a
  * distancia do campo ate aquele ponto. Porem, o caminho executado leva
  * em conta a prioridade Sul, Norte, Oeste, Leste sem se preocupar em 
  * associar o menor caminho ate determinada coordenada.
  *   O programa eh executado recursivamente e nao visita locais que ja
  * foram explorados ou fora dos limites da matriz do mapa.
  * 
  * Variaveis:
  * 	@mapa:		Matriz de campos transponiveis e intransponveis
  * 	@explore: 	Matriz que ira salvar as distancias das coordenadas
  * 	@pos:		Coordenadas da posical atual do Flood Fill
  * 	@distancia:	Distancia atual ao executar o Flood Fill
  * 
  * Retorno
  * 	@Distancia: Distancia maxima percorrida em todas as direcoes.
  */
 
 int flood_fill(int mapa[QTD_LINHAS][QTD_COLUNAS], int explore[QTD_LINHAS][QTD_COLUNAS], Coordenada pos, int distancia){
	
	// Verifica se essa posicao eh intrasponivel ou se ja foi visitado
	if(mapa[pos.l][pos.c] == 1 || explore[pos.l][pos.c] != 0)
		return distancia - 1;
	
	// Marca a distancia percorrida ate o ponto
	explore[pos.l][pos.c] = distancia;
	
	// Sul
	if( (pos.l+1) < QTD_LINHAS){
		Coordenada sul = pos; 
		sul.l += 1;
		distancia = flood_fill(mapa, explore, sul, distancia+1);
	}
	
	// Norte
	if( (pos.l-1) > -1){
		// printf("%d ", pos.l);
		Coordenada norte = pos; 
		norte.l -= 1;
		distancia = flood_fill(mapa, explore, norte, distancia+1);
	}
	
	// Oeste
	if( (pos.c-1) > -1){
		Coordenada oeste = pos; 
		oeste.c--;
		distancia = flood_fill(mapa, explore, oeste, distancia+1);
	}
	
	// Leste
	if( (pos.c+1) < QTD_COLUNAS){
		Coordenada leste = pos; 
		leste.c++;
		distancia = flood_fill(mapa, explore, leste, distancia+1);
	}
	
	return distancia;
}
