#include "IOprocessor.h"

/**
 *  Funções da Struct Arquivo (Binários e Textuais)
 */
    int gvl_abrirArquivo(Arquivo* arq, const char* nome, const char* modo){
        if(arq == NULL)
            return 1;

        if( (arq->fp = fopen(nome, modo)) == NULL )
            return 1;

        for(int i = 0; i < GVL_TAM_BUFFER_POOL; i++){
            arq->bf.indexPaginas[i] = GVL_INDEX_NULO;
            arq->bf.paginas[i]      = NULL;
        }
        arq->posicaoPtr = 0;
        arq->bf.contadorAcessos = 0;
        return 0;
    }

    int gvl_fecharArquivo(Arquivo *arq){
        if(arq == NULL || arq->fp == NULL)
            return 1;

        gvl_flushBuffer(arq);

        fclose(arq->fp);
        arq->fp = NULL;

        return 0;
    }

    int gvl_lerArquivo(Arquivo *arq, void* var, size_t qtdBytes){
        if(arq == NULL || arq->fp == NULL || var == NULL || qtdBytes == 0)
            return 1;
        
        char* varByte = (char*) var;

        // Loop que irá ler os X bytes do arquivo
        while(qtdBytes--){
            
            // Verificando se a página que queremos ler já está no buffer.
            int indexPagina = gvl_indexPagina(arq->posicaoPtr);
            if(!gvl_paginaEstaCarregada(arq, indexPagina))
                if(gvl_carregarPagina(arq, indexPagina))
                    return EOF; // a página indicada não existe.

            // Carregando ponteiro da pagina do buffer que irá ler os bytes.
            char* byte  = gvl_ptrPagina(arq, arq->posicaoPtr, indexPagina);
            
            *varByte = *byte;
            ++varByte;
            ++arq->posicaoPtr;
        }

        return 0;
    }

    int gvl_escreverArquivo(Arquivo *arq, void* var, size_t qtdBytes){
        if(arq == NULL || arq->fp == NULL || var == NULL || qtdBytes == 0)
            return 1;
        
        char* varByte = (char*) var;

        // Loop que irá ler os X bytes do arquivo
        while(qtdBytes--){
            
            // Verificando se a página que queremos ler já está no buffer.
            int indexPagina = gvl_indexPagina(arq->posicaoPtr);
            if(!gvl_paginaEstaCarregada(arq, indexPagina))
                if(gvl_carregarPagina(arq, indexPagina))
                    return EOF; // a página indicada não existe.
            
            // Carregando ponteiro da pagina do buffer que iremos escrever os bytes.
            char* byte  = gvl_ptrPagina(arq, arq->posicaoPtr, indexPagina);
            
            *byte = *varByte;
            ++varByte;
            ++arq->posicaoPtr;
        }

        return 0;
    }

    int gvl_seek(Arquivo *arq, long offset, int referencia){
        if(arq == NULL || arq->fp == NULL )
            return 1;

        if(fseek(arq->fp, offset, referencia) == -1){
            fseek(arq->fp, arq->posicaoPtr, SEEK_SET);
            return 1;
        }
        
        arq->posicaoPtr = ftell(arq->fp);
        return 0;
    }

/**
 * Funções para Arquivos em formato texto
 */
    int gvl_lerLinha(Arquivo *arq, char* str, size_t qtdBytes){
        // printf("inicioFuncao...\n");
        if(arq == NULL || arq->fp == NULL || str == NULL || qtdBytes == 0)
            return 1;

        char* iteradorStr = str;

        // Loop que irá ler os (n-1) bytes do arquivo
        while((qtdBytes--) >= 1){

            // Verificando se a página que queremos ler já está no buffer.
            int indexPagina = gvl_indexPagina(arq->posicaoPtr);
            if(!gvl_paginaEstaCarregada(arq, indexPagina))
                if(gvl_carregarPagina(arq, indexPagina))
                    return EOF; // a página indicada não existe.

            // Carregando ponteiro da pagina do buffer que irá ler os bytes.
            char* byte  = gvl_ptrPagina(arq, arq->posicaoPtr, indexPagina);
            
            *iteradorStr = *byte;
            ++iteradorStr;
            ++arq->posicaoPtr;

            if(*byte == '\n') 
                break;
        }

        // Inserindo o fim de linha do C
        *iteradorStr = '\0';

        return 0;
    }

/**
 * Funções de Controle do Buffer Pool
 */
    int gvl_paginaEstaCarregada(Arquivo *arq, int indexPag){
        for(int i = 0; i < GVL_TAM_BUFFER_POOL; i++){
            if(arq->bf.indexPaginas[i] == indexPag)
                return 1;
        }
        return 0;
    }

    int gvl_carregarPagina(Arquivo *arq, int indexPag){
        
        // @TODO: Verificar se há slots vazios no buffer pool
        // Se não houver precisa desalocar um slot para carregar
        // a página abaixo.
        long   aux        = ftell(arq->fp);
        size_t qtdBytes   = (size_t) GVL_TAM_PAGINA;

        char*  novaPagina = malloc(qtdBytes * sizeof(char));
        memset(novaPagina, GVL_LIXO_MEM, qtdBytes);

        long offset = indexPag * qtdBytes;
        fseek(arq->fp, offset, SEEK_SET);
        
        size_t lidos = fread(novaPagina, 1, qtdBytes, arq->fp);
        
        // Caso a leitura cause algum erro
        if(lidos == 0){
            free(novaPagina);
            return (feof(arq->fp) || ferror(arq->fp));
        }
        
        // @TODO: Ajustar para substituir a pagina menos utilizada
        if(arq->bf.paginas[0] != NULL)
            free(arq->bf.paginas[0]);

        arq->bf.paginas[0]      = novaPagina;
        arq->bf.indexPaginas[0] = indexPag;
        arq->bf.contadorAcessos += 1;

        // Para visualizar a página que foi lida do arquivo.
        // printf("%32000s", novaPagina);

        return 0;   
    }

    int gvl_removerPagina(Arquivo *arq, int indexPag){
        // @TODO, será utilizada quando o buffer pool tiver mais
        // de 1 slot de página
    }

    int gvl_flushBuffer(Arquivo *arq){
        for(int i = 0; i < GVL_TAM_BUFFER_POOL; i++){
            // @TODO: caso essa página tenha sido alterada 
            // escreve ela no arquivo e depois apaga do buffer
            
            if(arq->bf.indexPaginas[i] != GVL_INDEX_NULO)
                free(arq->bf.paginas[i]);
            
            arq->bf.paginas[i]   = NULL;
            arq->bf.indexPaginas[i] = GVL_INDEX_NULO;
        }
    }

/**
 * Funções auxiliares importantes da biblioteca
 */
    int gvl_indexPagina(long posicaoPtr){
        return (posicaoPtr / GVL_TAM_PAGINA);
    }

    char* gvl_ptrPagina(Arquivo* arq, long posicaoPtr, int indexPagina){
        int offsetPagina = posicaoPtr - (indexPagina * GVL_TAM_PAGINA);
        
        for(int i = 0; i < GVL_TAM_PAGINA; i++)
            if(arq->bf.indexPaginas[i] == indexPagina)
                return &(arq->bf.paginas[i][offsetPagina]);
        
        return NULL;
    }

