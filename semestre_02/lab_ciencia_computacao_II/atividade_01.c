/**
 * Laboratório de Introdução a Ciencia da Computacao II
 * Ex01. 	A raposa e o Coelho
 * Autor:  	Gabriel Van Loon
 * 
 * RESUMO
 * Uma raposa deseja se alimentar de um coelho, que para sobreviver deve fugir
 * para um dos buracos no mapa e se esconder. O programa deve cálcular se o 
 * coelho conseguirá ou não sobreviver à caçada. Além disso, a raposa se move
 * 2x mais rápido do que o coelho.
 *
 * DESCRIÇÃO
 * - O algoritmo receberá a quantidade X de buracos que há no mapa, as coordenadas
 *   (x,y) do coelho, da raposa e em seguida as coordenadas dos X buracos.
 * - O algoritmo busca se existe algum buraco que o coelho consiga alcançar antes
 *   da raposa, se sim então há uma forma do coelho escapar.
 */
 # include <stdlib.h>
 # include <stdio.h>
 # include <math.h>
 
 typedef struct _coordenada{
	float x;
	float y;
 } Coord;
 
 int main(void){
	
	int qtdBuracos;
	Coord coelho, raposa;
	Coord* buracos;
	
	// Quant. de Buracos no Mapa
	scanf(" %d", &qtdBuracos);
	
	buracos = (Coord*) malloc(qtdBuracos*sizeof(Coord));
	
	// Coordenadas coelho
	scanf(" %f", &coelho.x);
	scanf(" %f", &coelho.y);
	
	// Coordenadas raposa
	scanf(" %f", &raposa.x);
	scanf(" %f", &raposa.y);
	
	// Carregando os buracos
	for(int i = 0; i < qtdBuracos; i++){
		scanf(" %f", &buracos[i].x);
		scanf(" %f", &buracos[i].y);
	}	
	
	// Vericiando se existe algum buraco para fuga
	for(int i = 0; i < qtdBuracos; i++){
		
		float distXcoelho = coelho.x - buracos[i].x; 
		float distYcoelho = coelho.y - buracos[i].y; 
		float distCoelho  = sqrt((distXcoelho*distXcoelho) + (distYcoelho*distYcoelho));
		
		float distXraposa = raposa.x - buracos[i].x;
		float distYraposa = raposa.y - buracos[i].y;
		float distRaposa  = sqrt((distXraposa*distXraposa) + (distYraposa*distYraposa));
		
		if( ((distRaposa/2) - distCoelho) > 0 ){
			printf("O coelho pode escapar pelo buraco (%.03f,%.03f).\n", buracos[i].x, buracos[i].y);
			return 0;
		}
	}

	printf("O coelho nao pode escapar.\n");
	
	free(buracos);
	return 0;
 }
 
 
