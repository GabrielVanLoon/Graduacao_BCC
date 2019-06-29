#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/** 
 * MANIPULAÇÃO DE REGISTROS DE CABEÇALHO
 */ 
    HeaderIndex gvl_carregarCabecalhoIndex(Arquivo *bin){
        HeaderIndex hi;
        memset(&hi, GVL_LIXO_MEM, sizeof(HeaderIndex));

        if(bin == NULL || bin->fp == NULL)
            return hi;

        gvl_seek(bin, 0, SEEK_SET);
        gvl_lerArquivo(bin, &(hi.status),       sizeof(char));
        gvl_lerArquivo(bin, &(hi.nroRegistros), sizeof(int));

        return hi;
    }

    int gvl_escreverCabecalhoIndex(Arquivo* bin, HeaderIndex* hi){
        if(bin == NULL || bin->fp == NULL || hi == NULL)
            return 1;

        gvl_seek(bin, 0, SEEK_SET);
        gvl_escreverArquivo(bin, &(hi->status),       sizeof(char));
        gvl_escreverArquivo(bin, &(hi->nroRegistros), sizeof(int));
        
        // Economiza o fato de ter que fazer o fill com lixo
        bin->bf.tamanhoPagina[0] = GVL_TAM_PAGINA; 

        return 0;
    }

    int gvl_setStatusCabecalhoIndex(Arquivo* bin, HeaderIndex* hi, char flag){
        if(bin == NULL || bin->fp == NULL || hi == NULL)
            return 1;

        gvl_seek(bin, 0, SEEK_SET);
        if( gvl_escreverArquivo(bin, &flag, sizeof(char)) )
            return 1;

        hi->status = flag;
        return 0;
    }

/**
 * MANIPULAÇÂO DE REGISTROS DE INDEX
 */
    Index gvl_carregarIndex(Arquivo* bin){
        Index i;
        memset(&i, GVL_LIXO_MEM, sizeof(Index));

        if(bin == NULL || bin->fp == NULL)
            return i;

        if(gvl_lerArquivo(bin, &(i.chaveBusca), sizeof(char) * 120))
            return i;
        if(gvl_lerArquivo(bin, &(i.byteOffset), sizeof(long)))
            return i;

        return i;
    }

    int gvl_escreverIndex(Arquivo* bin, HeaderIndex* hi, Index* i){
        if(bin == NULL || bin->fp == NULL || hi == NULL || i == NULL)
            return 1;

        gvl_escreverArquivo(bin, &(i->chaveBusca), sizeof(char) * 120);
        gvl_escreverArquivo(bin, &(i->byteOffset), sizeof(long));

        return 0;
    }

/**
 * MANIPULAÇÃO DO VETOR DE INDICES
 */
    Index* gvl_carregarArquivoIndices(Arquivo* bin, HeaderIndex* hi ){
        if(bin == NULL || bin->fp == NULL || hi == NULL || hi->nroRegistros == 0)
            return NULL;

        gvl_seek(bin, GVL_TAM_PAGINA, SEEK_SET);
        Index* indices = malloc(hi->nroRegistros * sizeof(Index));

        for(int i = 0; i < hi->nroRegistros; i++)
            indices[i] = gvl_carregarIndex(bin);

        return indices;
    }

    int gvl_escreverArquivoIndices(Arquivo* bin, HeaderIndex* hi, Index** indices){
        if(bin == NULL || bin->fp == NULL || hi == NULL || hi->nroRegistros == 0)
            return 1;

        // Escreve o cabeçalho
        gvl_escreverCabecalhoIndex(bin, hi);

        // Escreve os indices
        gvl_seek(bin, GVL_TAM_PAGINA, SEEK_SET);
        for(int i = 0; i < hi->nroRegistros; i++)
            gvl_escreverIndex(bin, hi, &((*indices)[i]) ) ;

        return 0;
    }

    int gvl_destruirIndices(Index** indices){ 
        if(*indices != NULL)
            free(*indices);
        *indices = NULL;
    }

    int gvl_inserirIndice(Index** indices, HeaderIndex* hi, Index i){
        if(indices == NULL  || hi == NULL)
            return 1;

        hi->nroRegistros              += 1;
        (*indices)                     = realloc((*indices), hi->nroRegistros * sizeof(Index));
        (*indices)[hi->nroRegistros-1] = i;

        return 0;
    }

/**
 * BUSCA E ORDENAÇÂO DE INDICES
 */
    void _gvl_mergeIndices(Index** indices, int l, int m, int r){
        int i, j, k;
        int tamLeft  = m - l + 1;
        int tamRight = r - m;

        // Arrays temporários
        Index L[tamLeft], R[tamRight];

        // Copiando os arrays
        for(i = 0; i < tamLeft; i++)
            L[i] = (*indices)[l+i];
        for(j = 0; j < tamRight; j++)
            R[j] = (*indices)[m+1+j];

        // Fazendo o merge dos dois arrays
        i = j = 0;
        k = l;
        while(i < tamLeft && j < tamRight){
            if(strcmp(L[i].chaveBusca, R[j].chaveBusca) < 0){
                (*indices)[k++] = L[i++];


            } else if(strcmp(L[i].chaveBusca, R[j].chaveBusca) > 0){
                (*indices)[k++] = R[j++];
            
            } else if(L[i].byteOffset < R[j].byteOffset) {
                (*indices)[k++] = L[i++];

            } else {
                (*indices)[k++] = R[j++];

            }
            
        }

        while(i < tamLeft)
            (*indices)[k++] = L[i++];
        
        while(j < tamRight)
            (*indices)[k++] = R[j++];
    }

    void _gvl_ordenarIndices(Index** indices, int l, int r){
        // printf("Merge: [%d, %d]\n", l, r);
        if(l < r){
            int m = (l+r)/2;

            _gvl_ordenarIndices(indices, l,   m);
            _gvl_ordenarIndices(indices, m+1, r);
            
            _gvl_mergeIndices(indices, l, m, r);
        }
    }

    int gvl_ordenarIndices(HeaderIndex* hi, Index** indices){
        if(hi == NULL || hi->nroRegistros == 0 || indices == NULL)
            return 1;

        _gvl_ordenarIndices(indices, 0, hi->nroRegistros-1);
        return 0;
    }

    int gvl_buscarIndice(HeaderIndex* hi, Index** indices, char* valor){
        if(hi == NULL || indices == NULL || valor == NULL)
            return -1;

        // Realiza busca binária para achar o valor
        int l, r, m, comp;
        l = 0;
        r = hi->nroRegistros-1;
        m = (l+r)/2;

        comp = strcmp(valor, (*indices)[m].chaveBusca);
        while(l <= r && comp != 0){
            if(comp < 0)
                r = m-1;
            else
                l = m+1;
            
            m = (l+r)/2;
            comp = strcmp(valor, (*indices)[m].chaveBusca);
        }

        // Caso não tenha achado
        if(comp != 0)
            return -1;

        // Achou, mas precisa retornar a primeira ocorrencia
        int i = m-1;
        while(i >= 0 && strcmp(valor, (*indices)[i].chaveBusca) == 0) 
            i -= 1;

        return (i+1);
    }