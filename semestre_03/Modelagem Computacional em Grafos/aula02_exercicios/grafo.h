#ifndef GRAFO_H
    #define GRAFO_H
    
    /**
     * @typedef struct grafo
     * 
     * Implementação de versão estática de um grafo simples. Além disso,
     * a biblioteca dispões da possibilidade de decidir se será utilizado
     * um grafo normal ou direcionado. Para isso, basta definir nesse arquivo
     * uma constante GRAFO_DIRECIONADO
     * 
     * O grafo é implementado de maneira 0-based 
     */

    #define GRAFO_MAXSIZE 101
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

    /**
     * Algoritmos ligados à Caminho Euleriano
     */
        int possuiCicloEuleriano(grafo *g, int* erro);

        int percorrerCaminhoEuleriano(grafo* g, int *erro);

    /**
     * Algoritmos de Conectividade - Austado para percorrer Caminho Euleriano
     */ 
        typedef enum _cor{
            branco, cinza, preto
        } cor;

        // Verifica se existe caminho entre dois vértices distintos. Retornando
        // 1 em caso afirmativo e 0 caso contrário. Utiliza dfs: O(V+E)
        int existe_caminho(grafo* g, int origem, int destino, int *erro);

        // Verifica se o grafo é um Componente Fortemente conectado
        // Utilizando o algoritmo de Kosaraju com DFS: O(V+E).
        // @vInicial controla se o grafo é 0-based ou 1-based
        int eh_fortemente_conectado(grafo *g, int vInicial, int *erro);


#endif