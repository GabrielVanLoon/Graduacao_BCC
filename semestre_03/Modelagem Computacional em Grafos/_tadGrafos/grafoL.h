#ifndef GRAFO_H
    #define GRAFO_H

    #define MAXNUMVERTICES  100
    #define ARESTA_VAZIA    0
    #define ARESTA_COMUM    1
    
    #define BRANCO          0
    #define PRETO           1
    #define CINZA           2
    #define VERMELHO        3

    /**
     * Implementação de TAD Grafo utilizando matriz de adjacência
     */
        struct _aresta {
            int peso;
            int adjacente;
            int cor;
            struct _aresta *proxAresta;
        };
        typedef struct _aresta  Aresta;

        struct _vertice{
            char*   label;
            int     cor;
            struct _aresta *header, *fim;
        };
        typedef struct _vertice Vertice;

        struct _grafo{
            Vertice vertices[MAXNUMVERTICES];
            int numVertices;
        };
        typedef struct _grafo   Grafo;

    /** 
     * As funções da biblioteca não devem ser sensiveis à implementação.
     * 
     * Os vértices devem ser 0-based, logo um grafo com
     * N vértices possui V = {0, 1, ..., (n-1)}.
     */ 
        
    /**
     * Funções para criar o grafo
     */
        int criar_grafo(Grafo* g, int qtdVertices);

        int destruir_grafo(Grafo* g);

        int inserir_aresta(Grafo* g, int vOrigem, int vDestino, int digrafo);

        int inserir_arestaPonderada(Grafo* g, int vOrigem, int vDestino, int peso, int digrafo);

        int remover_aresta(Grafo* g, int vOrigem, int vDestino, int digrafo);

        int calcularGrauVertice(Grafo* g, int v);

        void exibirGrafo(Grafo* g);

    /**
     * Funções para iterar nos vizinhos de um vertice
     */
        int possuiVerticesAdjacentes(Grafo* g, int v);

        int primeroVerticeAdjacente(Grafo* g, int v);

        int proximoVerticeAdjacente(Grafo *g, int v, int adjAtual);

    /**
     * Funções que vão ser afetadas pela implementação
     */ 
        void exibirCoresVertices(Grafo *g);

        int bfs(Grafo *g, int vOrigem);

        int colorirGrafo(Grafo *g);

        int fleury(Grafo *g);

#endif