#include <stdlib.h>
#include <stdio.h>
#include "grafoL.h"

int main(void){

    Grafo g;

    criar_grafo(&g, 5);

    inserir_aresta(&g, 0, 1, 0);
    inserir_aresta(&g, 0, 2, 0);   
    inserir_aresta(&g, 1, 2, 0);
    inserir_aresta(&g, 2, 3, 0);
    inserir_aresta(&g, 2, 4, 0);
    inserir_aresta(&g, 3, 4, 0);

    exibirGrafo(&g);

    // bfs(&g, 0);
    // colorirGrafo(&g);

    exibirCoresVertices(&g);

    destruir_grafo(&g);

    return 0;
}