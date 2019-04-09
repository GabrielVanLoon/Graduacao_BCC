#ifndef GVL_IO_PROCESSOR_H
    #define GVL_IO_PROCESSOR_H
    
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    /**
     * Constantes definidas pela biblioteca
     */
        #define GVL_TAM_PAGINA       32000
        #define GVL_TAM_BUFFER_POOL  1
        #define GVL_INDEX_NULO      -1
        #define GVL_LIXO_MEM        '@'
    /**
     * Estruturas utilizadas pela biblioteca
     */ 
        typedef struct _bufferpool{
            char*       paginas[GVL_TAM_BUFFER_POOL];
            int         indexPaginas[GVL_TAM_BUFFER_POOL];
            int         contadorAcessos;
        } BufferPool;

        typedef struct _arquivo{
            FILE*       fp;
            BufferPool  bf;
            long        posicaoPtr;
        } Arquivo;

    /**
     *  Funções da Struct Arquivo (Binários e Textuais)
     */
        int     gvl_abrirArquivo(Arquivo *arq, const char* nome, const char* modo);

        int     gvl_fecharArquivo(Arquivo *arq);

        int     gvl_lerArquivo(Arquivo *arq, void* var, size_t qtdBytes);

        int     gvl_escreverArquivo(Arquivo *arq, void* var, size_t qtdBytes);

        int     gvl_seek(Arquivo *arq, long offset, int referencia);

    /**
     * Funções para Arquivos em formato texto
     */
        int   gvl_lerLinha(Arquivo *arq, char* str, size_t qtdBytes);

    /**
     * Funções de Controle do Buffer Pool
     */
        int     gvl_paginaEstaCarregada(Arquivo *arq, int indexPag);

        int     gvl_carregarPagina(Arquivo *arq, int indexPag);

        int     gvl_removerPagina(Arquivo *arq, int indexPag);

        int     gvl_flushBuffer(Arquivo *arq);

    /**
     * Funções auxiliares importantes da biblioteca
     */
        int     gvl_indexPagina(long posicaoPtr);

        char*   gvl_ptrPagina(Arquivo* arq, long posicaoPtr, int indexPagina);

#endif