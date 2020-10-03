/**
 * Trabalho de Organização de arquivos
 * Autor:  Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
 *         Tamiris Fernandes Tinelli
 * Prof.:  Dra. Cristina Dutra de Aguiar Ciferri
 * Data:   maio/2019
 * 
 * @library index.h
 * 
 * DESCRIÇÃO
 * 
 * Essa biblioteca tem como objetivo implementar um index secundário
 * fortemente ligado conforme especificado nas aulas e no trabalho 4
 * da disciplina de organização de arquivos.
 * 
 */


#ifndef GVL_INDEX_H
    #define GVL_INDEX_H

    /**
     * Bibliotecas e Constantes Importantes
     */
        #include "IOprocessor.h"

    
     /**
     * @struct HeaderIndex
     * 
     * Representa um registro de cabeçalho, seguindo todos os campos
     * e nomenclaturas conforme especificadas na documentação do trabalho.
     * 
     * ATRIBUTOS
     * @char status       - '1' caso o arquivo esteja consistente 
     *                       '0' caso não esteja.
     * @int  nroRegistros - topo da lista de registros de dados removidos.
     */ 
        typedef struct _regCabecalhoIndex{
            char status;    
            int  nroRegistros; 
        } HeaderIndex;

    /**
     * @struct Index
     * 
     * Representa um registro de index, seguindo todos os campos
     * e nomenclaturas conforme especificadas na documentação do trabalho.
     * 
     * ATRIBUTOS
     * @char chaveBusca[120]    - armazena a chave de busca do indice.
     * @long byteOffset         - armazena o byte offsetdo registro que corresponde 
     *                            à chave de busca associada.
     */ 
    typedef struct _regIndex{
        char chaveBusca[120];
        long byteOffset;
    } Index;


    /** 
     * MANIPULAÇÃO DE REGISTROS DE CABEÇALHO
     */ 
        /**
         * @HeaderIndex gvl_carregarCabecalhoIndex(Arquivo *bin);
         * 
         * Lê um arquivo .index e retorna o struct HeaderIndex na
         * primeira página do arquivo.
         */
        HeaderIndex gvl_carregarCabecalhoIndex(Arquivo *bin);

        /**
         * @int gvl_escreverCabecalhoIndex(Arquivo* bin, HeaderIndex* hi);
         * 
         * Escreve o struct HeaderIndex na primeira página do arquivo bin.
         * Retorna 1 em caso de erro.
         */
        int gvl_escreverCabecalhoIndex(Arquivo* bin, HeaderIndex* hi);

        /**
         * @int gvl_setStatusCabecalhoIndex(Arquivo* bin, HeaderIndex* hi, char flag);
         * 
         * Altera o bit de status do arquivo de index. Caso seja atualizado com
         * sucesso altera também o valor no hi. Retorna 1 em caso de erro.
         */
        int gvl_setStatusCabecalhoIndex(Arquivo* bin, HeaderIndex* hi, char flag);
        
    /**
     * MANIPULAÇÂO DE REGISTROS DE INDEX
     */
        /**
         * @Index gvl_carregarIndex(Arquivo* bin);
         * 
         * Lê e retorna um Index na posição atual do arquivo. retorna lixo caso
         * haja algum erro na leitura.
         */
        Index gvl_carregarIndex(Arquivo* bin);

        /**
         * @int gvl_escreverIndex(Arquivo* bin, HeaderIndex* hi, Index* i);
         * 
         * Escreve o Index na posição atual do arquivo.
         * Retorna 1 em caso de erro.
         */
        int gvl_escreverIndex(Arquivo* bin, HeaderIndex* hi, Index* i);

    /**
     * MANIPULAÇÃO DO VETOR DE INDICES
     */
        /**
         * @Index* gvl_carregarArquivoIndices(Arquivo* bin, HeaderIndex* hi);
         * 
         * Lê o arquivo bin e retorna um vetor com todos os indices.
         * Retorna NULL caso haja algum erro ou o arquivo de indice esteja vazio.
         */
        Index* gvl_carregarArquivoIndices(Arquivo* bin, HeaderIndex* hi);

        /**
         * @int gvl_escreverArquivoIndices(Arquivo* bin, HeaderIndex* hi, Index** indices);
         * 
         * Recebe um HeaderIndex e um vetor de indices e escreve em bin.
         * Retorna 1 em caso de erro.
         */
        int gvl_escreverArquivoIndices(Arquivo* bin, HeaderIndex* hi, Index** indices);

        /**
         * @int gvl_destruirIndices(Index** indices); 
         * 
         * Realiza free() no vetor de indices para evitar memory leaks.
         */
        int gvl_destruirIndices(Index** indices); 

        /**
         * @int gvl_inserirIndice(Index** indices, HeaderIndex* hi, Index i);
         * 
         * Insere um novo Index no final do vetor de indices. É necessário
         * ordenar o vetor de indices antes de realizar a próxima busca.
         */
        int gvl_inserirIndice(Index** indices, HeaderIndex* hi, Index i);

    /**
     * BUSCA E ORDENAÇÂO DE INDICES
     */
        /**
         * @int gvl_ordenarIndices(HeaderIndex* hi, Index** indices);
         * 
         * Ordena o vetor de índices utilizando o algoritmo Merge Sort.
         */
        int gvl_ordenarIndices(HeaderIndex* hi, Index** indices);

        /**
         * @int gvl_buscarIndice(HeaderIndex* hi, Index** indices, char* busca);
         * 
         * Busca e retorna a posição da primeira ocorrência do valor buscado.
         * Retorna -1 caso não encontre.
         */
        int gvl_buscarIndice(HeaderIndex* hi, Index** indices, char* busca);

#endif