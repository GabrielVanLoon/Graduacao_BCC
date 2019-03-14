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
    inserir_aresta(g, 0, 2, 2, &erro);
    inserir_aresta(g, 1, 2, 3, &erro);
    inserir_aresta(g, 2, 3, 1, &erro);
    inserir_aresta(g, 3, 4, 1, &erro);
    exibir_matrizAdj(g);
    printf("\n\n");

    gComplementar = criar_complementar(g, 1, &erro);
    exibir_matrizAdj(gComplementar);
    return 0;
}