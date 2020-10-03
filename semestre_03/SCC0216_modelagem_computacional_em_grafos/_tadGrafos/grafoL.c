#include <stdlib.h>
#include <stdio.h>
#include "grafoL.h"

/**
 * Funções para criar o grafo
 */
    int criar_grafo(Grafo* g, int qtdVertices){
        if(g == NULL || qtdVertices >= MAXNUMVERTICES)
            return 1;

        g->numVertices = qtdVertices;
        for(int i = 0; i < g->numVertices; i++){
            Aresta* cabecalho = malloc(sizeof(cabecalho));
            cabecalho->adjacente  = 0;
            cabecalho->peso       = 0;
            cabecalho->proxAresta = NULL;

            g->vertices[i].label  = NULL;
            g->vertices[i].header = cabecalho;
            g->vertices[i].fim    = cabecalho;
        }

        return 0;
    }

    int destruir_grafo(Grafo* g){
        if(g == NULL)
            return 1;

        for(int i = 0; i < g->numVertices; i++){
            // Se houver label desaloca
            if(g->vertices[i].label != NULL){
                free(g->vertices[i].label);
                g->vertices[i].label == NULL;
            }
                
            // Percorre a lista de adjacencia desalocando os nós
            while(g->vertices[i].header != NULL){
                Aresta* aux = g->vertices[i].header;
                g->vertices[i].header = g->vertices[i].header->proxAresta;
                free(aux);
            }
        }

        return 0;
    }

    int _inserir_aresta(Grafo* g, int vOrigem, int vDestino, int peso){
        // Alocando a nova aresta
        Aresta* novaAresta = malloc(sizeof(Aresta));
        novaAresta->adjacente   = vDestino;
        novaAresta->peso        = peso;
        novaAresta->proxAresta  = NULL;

        // Inserindo a aresta no fim da lista de adjacência
        g->vertices[vOrigem].fim->proxAresta = novaAresta;
        g->vertices[vOrigem].fim = novaAresta;

        return 0;
    }

    int inserir_aresta(Grafo* g, int vOrigem, int vDestino, int digrafo){
        if(g == NULL || vOrigem >= g->numVertices || vDestino >= g->numVertices || vOrigem < 0 || vDestino < 0 )
            return 1;

        _inserir_aresta(g, vOrigem, vDestino, ARESTA_COMUM);
        if(!digrafo)
            _inserir_aresta(g, vDestino, vOrigem, ARESTA_COMUM);

        return 0;
    }

    int inserir_arestaPonderada(Grafo* g, int vOrigem, int vDestino, int peso, int digrafo){
        if(g == NULL || vOrigem >= g->numVertices || vDestino >= g->numVertices || vOrigem < 0 || vDestino < 0 )
            return 1;

        _inserir_aresta(g, vOrigem, vDestino, peso);
        if(!digrafo)
            _inserir_aresta(g, vDestino, vOrigem, peso);

        return 0;
    }

    int _remover_aresta(Grafo* g, int vOrigem, int vDestino){
        Aresta** anterior = &(g->vertices[vOrigem].header->proxAresta);
        Aresta*  busca    = g->vertices[vOrigem].header->proxAresta;

        while(busca != NULL && busca->adjacente != vDestino){
            anterior    = &(busca->proxAresta);
            busca       = busca->proxAresta;
        }

        // Percorreu toda lista de adjacencia e não encontrou
        if(busca == NULL)
            return 1;

        // Caso seja a ultima aresta da lista, atualiza fim
        if(busca == g->vertices[vOrigem].fim){
            if(busca->proxAresta == NULL) 
                g->vertices[vOrigem].fim = g->vertices[vOrigem].header;
            else 
                g->vertices[vOrigem].fim = busca->proxAresta;
        }
        
        // Atualizando o nó anterior.
        *anterior = busca->proxAresta;
        
        // Destruindo o nó
        free(busca);

        return 0;
    }

    int remover_aresta(Grafo* g, int vOrigem, int vDestino, int digrafo){
        if(g == NULL || vOrigem >= g->numVertices || vDestino >= g->numVertices || vOrigem < 0 || vDestino < 0 )
            return 1;

        _remover_aresta(g, vOrigem, vDestino);
        if(!digrafo)
            _remover_aresta(g, vDestino, vOrigem);

        return 0;
    }

    int calcularGrauVertice(Grafo* g, int v){
        if(g == NULL ||  v >= g->numVertices || v < 0 )
            return -1;

        int     grau = 0;
        Aresta* aux  = g->vertices[v].header->proxAresta;
        while(aux != NULL){
            grau += 1;
            aux   = aux->proxAresta;
        }

        return grau;
    }

    void exibirGrafo(Grafo* g){
        if(g == NULL)
            return;

        printf("Grafo G = {V,A}\n");
        printf("V = {0, ... ,%d}\n", g->numVertices-1);
        printf("A = {\n");
        
        for(int v = 0; v < g->numVertices; v++){
            printf("\t");
            Aresta* aux  = g->vertices[v].header->proxAresta;
            while(aux != NULL){
                printf("(%d,%d), ", v, aux->adjacente);
                aux = aux->proxAresta;
            }
            printf("\n");
        }
            
        printf("}\n\n");
    }

/**
 * Funções para iterar nos vizinhos de um vertice
 */
    int possuiVerticesAdjacentes(Grafo* g, int v){
        if(g == NULL || v >= g->numVertices || v < 0 )
            return 0;

        // Se a lista possui apenas o nó de cabeçalho então não possui.
        if(g->vertices[v].fim != g->vertices[v].header)
            return 1;

        return 0;
    }

    int primeroVerticeAdjacente(Grafo* g, int v){
        if(g == NULL || v >= g->numVertices || v < 0 || !possuiVerticesAdjacentes(g, v))
            return -1;

        return g->vertices[v].header->proxAresta->adjacente;
    }

    int proximoVerticeAdjacente(Grafo *g, int v, int adjAtual){
        if(g == NULL || v >= g->numVertices || v < 0 )
            return -1;

        Aresta* aux  = g->vertices[v].header->proxAresta;
        while(aux != NULL && aux->adjacente != adjAtual){
            // printf("(%d,%d), ", v, aux->adjacente);
            aux = aux->proxAresta;
        }

        if(aux == NULL || aux->proxAresta == NULL)
            return -1;

        return aux->proxAresta->adjacente;
    }

/**
 * Funções que vão ser afetadas pela implementação
 */ 
    void exibirCoresVertices(Grafo *g){
        if(g == NULL)
            return;

        for(int i = 0; i < g->numVertices; i++)
            printf("[%d]->cor = %d\n", i, g->vertices[i].cor);
    }

    int bfs(Grafo *g, int vOrigem){
        if(g == NULL)
            return 1;

        // Marcando todos vertices como branco
        for(int i = 0; i < g->numVertices; i++)
            g->vertices[i].cor = BRANCO;

        // Gambiarra: usar um grafo como fila
        Grafo fila;
        criar_grafo(&fila, g->numVertices);

        // Empilhando o primeiro vértice
        g->vertices[vOrigem].cor = CINZA;
        inserir_aresta(&fila, 0, vOrigem, 1);

        // Percorre o loop até a fila ficar vazia
        int vAtual, vAdj;
        while( (vAtual = primeroVerticeAdjacente(&fila, 0)) != -1 ){
            remover_aresta(&fila, 0, vAtual, 1);
            
            // printf("Visitando vértice nº %d...\n", vAtual);
            g->vertices[vAtual].cor = PRETO;

            // Inserindo vizinhos brancos na pilha
            vAdj = primeroVerticeAdjacente(g, vAtual);
            if(vAdj == -1)
                    continue;

            do {
                // printf("Vizinho de %d -> Vertice nº %d\n", vAtual, vAdj);

                // Enfileirando vizinhos não visitados.
                if(g->vertices[vAdj].cor == BRANCO){
                    g->vertices[vAdj].cor = CINZA;
                    inserir_aresta(&fila, 0, vAdj, 1);
                }

                vAdj = proximoVerticeAdjacente(g, vAtual, vAdj);           

            } while(vAdj != -1);
        }

        destruir_grafo(&fila);
    }

    int colorirGrafo(Grafo *g){
        if(g == NULL)
            return 1;

        int sortIndex[g->numVertices];

        // Colorindo todos os grafos com branco
        for(int i = 0; i < g->numVertices; i++){
            sortIndex[i]        = i;
            g->vertices[i].cor  = BRANCO;
        }

        // Ordenando os index dos vértices do com maior grau
        // para o de menor grau. Bubble Sort mesmo pra ser enxuto.
        for(int l = 0; l < g->numVertices; l++){
            for(int r = r+1; r < g->numVertices; r++){
                int grauL = calcularGrauVertice(g, sortIndex[l]);
                int grauR = calcularGrauVertice(g, sortIndex[r]);

                if(grauR > grauL){
                    int aux = sortIndex[l];
                    sortIndex[l] = sortIndex[r];
                    sortIndex[r] = aux;
                }
            }
        }

        int cor = 1, possuiBrancos = 1;
        
        // Loop incrementa a qtd de cores até colorir todo grafo
        while(possuiBrancos){
            possuiBrancos = 0;

            for(int i = 0; i < g->numVertices; i++){
                int v = sortIndex[i];

                if(g->vertices[v].cor != BRANCO)
                    continue;

                // Inserindo vizinhos brancos na pilha
                int vAdj = primeroVerticeAdjacente(g, v);
                
                if(vAdj == -1){
                    g->vertices[v].cor = cor;
                    continue;
                }
                
                int podePintar = 1;
                do { // Verificando se não existem vizinhos da cor atual.
                    if(g->vertices[vAdj].cor == cor){
                        podePintar = 0;
                        break;
                    }
                    vAdj = proximoVerticeAdjacente(g, v, vAdj);           
                } while(vAdj != -1);

                if(podePintar)
                    g->vertices[v].cor = cor;
                else 
                    possuiBrancos = 1;   
            }

            cor += 1; // Cor do proximo loop
        }

        return 0;
    }

    int _fleury(Grafo* g, int v, int *path, int i){
        path[i] = v;

        // caso se parada: não há mais vizinhos
        



    }


    int fleury(Grafo *g){
        if(g == NULL)
            return 1;

        // Verificando se todos os vertices possuem grau 2
        for(int i = 0; i < g->numVertices; i++){
            if(calcularGrauVertice(g, i) % 2 != 0){
                printf("o grafo não satisfaz os requisitos!\n");
                return 1;
            }
        }

        int eulerPath[g->numVertices*g->numVertices];

        _fleury(g, 0, eulerPath, 0);
    }