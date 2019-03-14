#ifndef GRAFO_H
    #define GRAFO_H
    
    /**
     * @typedef struct grafo
     * 
     * Implementação de versão estática de um grafo simples. Além disso,
     * a biblioteca dispões da possibilidade de decidir se será utilizado
     * um grafo normal ou direcionado. Para isso, basta definir na sua main
     * uma constante GRAFO_DIRECIONADO
     */

    #define GRAFO_MAXSIZE 100
    #define ARESTA_VAZIA  -1

    typedef int aresta; 

    typedef struct _grafo{
        aresta  adj[GRAFO_MAXSIZE][GRAFO_MAXSIZE];
        int     numVertices;
    } grafo;

    /**
     * Funções básicas para manipulação de um grafo 'g'
     */
        grafo* criar_grafo(int n, int* erro);

        void destruir_grafo(grafo *g, int* erro);

        void inserir_aresta(grafo *g, int v1, int v2, aresta p, int* erro);

        void remover_aresta(grafo *g, int v1, int v2, int* erro);

        void exibir_matrizAdj(grafo *g);

    /**
     * Geradores de grafos associados
     */
        grafo* criar_transposta(grafo* g, int* erro);

        grafo* criar_complementar(grafo* g, int p, int* erro);

#endif