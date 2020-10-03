/** 
 * Modelagem Computacional em Grafos
 * Prof.: Thiago Pardo
 * Autor: Gabriel Van Loon
 * Data:  mar/2019
 */
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main(void){

    grafo *g, *gTransposto, *gComplementar;
    int erro = 0;

    g = criar_grafo(5, &erro);

    inserir_aresta(g, 0, 1, 1, &erro);
    inserir_aresta(g, 1, 2, 2, &erro);
    inserir_aresta(g, 2, 3, 3, &erro);
    inserir_aresta(g, 3, 4, 3, &erro);
    inserir_aresta(g, 4, 0, 4, &erro);
    // inserir_aresta(g, 3, 4, 5, &erro);
    
    exibir_matrizAdj(g);
    printf("\n\n");
    
    /*if(eh_fortemente_conectado(g, 0, &erro))
        printf("Eh fortemente conectado\n");
    else
        printf("Não eh fortemente conectado.\n");*/

    /*if(existe_caminho(g, 0, 7, &erro))
        printf("Existe caminho\n");
    else
        printf("Não existe caminho.\n");*/

    
    return 0;
}