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
            arq->bf.indexPaginas[i]  = GVL_INDEX_NULO;
            arq->bf.paginas[i]       = NULL;
            arq->bf.tamanhoPagina[i] = 0;
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

        // Iterador que ira percorer os bytes de var.
        char* varByte = (char*) var;

        // Verificando se a página que queremos ler já está no buffer.
        // Se não estiver, tentamos carregá-la no buffer.
        // Se não conseguimos, então quer dizer que alcançamos o fim
        // do arquivo e devemos retornar o EOF.
        int indexPagina = gvl_indexPagina(arq->posicaoPtr);
        if(!gvl_paginaEstaCarregada(arq, indexPagina))
            if(gvl_carregarPagina(arq, indexPagina))
                return EOF; // a página indicada não existe.

        // Loop que irá ler os próximos n bytes do arquivo
        while((qtdBytes--) >= 1){

            // Caso o ponteiro tenha mudado para a proxima pagina.
            if(arq->posicaoPtr % GVL_TAM_PAGINA == 0){
                indexPagina = gvl_indexPagina(arq->posicaoPtr);
                if(!gvl_paginaEstaCarregada(arq, indexPagina))
                    if(gvl_carregarPagina(arq, indexPagina))
                        return EOF; // a página indicada não existe.
            }

            // Carregando ponteiro da pagina do buffer que irá ler os bytes.
            char* byte  = gvl_ptrPagina(arq, arq->posicaoPtr, indexPagina);
            
            *varByte = *byte;

            ++varByte;
            ++arq->posicaoPtr;
        }

        return 0;
    }

    int gvl_escreverArquivo(Arquivo *arq, void* var, size_t qtdBytes){
        // printf("inicioFuncao...\n");
        if(arq == NULL || arq->fp == NULL || var == NULL || qtdBytes == 0)
            return 1;

        char* varByte = (char*) var;

        // Verificando se a página que queremos ler já está no buffer.
        // Se não estiver, tentamos carregá-la no buffer.
        // Se não conseguimos, então quer dizer que alcançamos o fim
        // do arquivo e devemos adicionar mais um bloco de memória para
        // conseguirmos escrever os bytes.
        int indexPagina = gvl_indexPagina(arq->posicaoPtr);
        if(!gvl_paginaEstaCarregada(arq, indexPagina))
            if(gvl_carregarPagina(arq, indexPagina)){
                if(gvl_appendNovaPagina(arq, indexPagina))
                    return EOF; // a página indicada não existe.
            } else{
                arq->bf.foiModificado[0] = 1;
            }

        // Loop que irá escrever os n bytes no arquivo
        while((qtdBytes--) >= 1){

            // Caso o ponteiro tenha mudado para a proxima pagina.
            if(arq->posicaoPtr % GVL_TAM_PAGINA == 0){
                indexPagina = gvl_indexPagina(arq->posicaoPtr);
                
                if(!gvl_paginaEstaCarregada(arq, indexPagina))
                     if(gvl_carregarPagina(arq, indexPagina)){
                        if(gvl_appendNovaPagina(arq, indexPagina))
                            return EOF; // a página indicada não existe.
                    } else{
                        arq->bf.foiModificado[0] = 1;
                    }
            }

            // Carregando ponteiro da pagina do buffer que irá receber o byte.
            char* byte  = gvl_ptrPagina(arq, arq->posicaoPtr, indexPagina);
            
            // Se estiver inserindo dado numa pagina nova, incrementa o tam. da pagina.
            if(arq->bf.tamanhoPagina[0] <= (arq->posicaoPtr % GVL_TAM_PAGINA))
                ++arq->bf.tamanhoPagina[0];

            *byte = *varByte; 
            ++varByte;
            ++arq->posicaoPtr;
        }

        return 0;
    }

    int gvl_seek(Arquivo *arq, long offset, int referencia){
        if(arq == NULL || arq->fp == NULL )
            return 1;

        if(referencia == SEEK_CUR)
            arq->posicaoPtr += offset;
        else
            arq->posicaoPtr = offset;
            
        return 0;
    }

/**
 * Funções para Arquivos em formato texto
 */
    int gvl_lerLinha(Arquivo *arq, char* str, size_t qtdBytes){
        if(arq == NULL || arq->fp == NULL || str == NULL || qtdBytes == 0)
            return 1;

        char* iteradorStr = str;

        // Verificando se a página que queremos ler já está no buffer.
        int indexPagina = gvl_indexPagina(arq->posicaoPtr);
        if(!gvl_paginaEstaCarregada(arq, indexPagina))
            if(gvl_carregarPagina(arq, indexPagina))
                return EOF; // a página indicada não existe.

        // Loop que irá ler os (n-1) bytes do arquivo
        while((qtdBytes--) >= 1){

            // Caso o ponteiro tenha mudado para a proxima pagina.
            if(arq->posicaoPtr % GVL_TAM_PAGINA == 0){
                indexPagina = gvl_indexPagina(arq->posicaoPtr);
                if(!gvl_paginaEstaCarregada(arq, indexPagina))
                    if(gvl_carregarPagina(arq, indexPagina))
                        return EOF; // a página indicada não existe.
            }

            // Carregando ponteiro da pagina do buffer que irá ler os bytes.
            char* byte  = gvl_ptrPagina(arq, arq->posicaoPtr, indexPagina);
            
            // Se estiver inserindo dado numa pagina nova, incrementa o tam. da pagina.
            if(arq->bf.tamanhoPagina[0] <= (arq->posicaoPtr % GVL_TAM_PAGINA))
                ++arq->bf.tamanhoPagina[0];

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
        
        gvl_flushBuffer(arq);

        // @TODO: Verificar se há slots vazios no buffer pool
        // Se não houver precisa desalocar um slot para carregar
        // a página abaixo.
        size_t qtdBytes   = (size_t) GVL_TAM_PAGINA;

        char*  novaPagina = malloc(qtdBytes * sizeof(char));
        memset(novaPagina, GVL_LIXO_MEM, qtdBytes);

        long offset = indexPag * qtdBytes;
       
        // Quer acessar um offset maior do que o disponivel no arquivo 
        fseek(arq->fp, -1, SEEK_END); 

        if(offset >= ftell(arq->fp)){
            free(novaPagina);
            return 1;
        }

        fseek(arq->fp, offset, SEEK_SET);
        size_t lidos = fread(novaPagina, sizeof(char), qtdBytes, arq->fp);

        // Caso a leitura cause algum erro
        if(lidos == 0){
            free(novaPagina);
            return (feof(arq->fp) || ferror(arq->fp));
        }

        // @TODO: Ajustar para substituir a pagina menos utilizada
        if(arq->bf.paginas[0] != NULL)
            free(arq->bf.paginas[0]);

        arq->bf.paginas[0]       = novaPagina;
        arq->bf.indexPaginas[0]  = indexPag;
        arq->bf.foiModificado[0] = 0;
        arq->bf.contadorAcessos += 1;
        arq->bf.tamanhoPagina[0] = lidos;

        // Para visualizar a página que foi lida do arquivo.
        // printf("%32000s", novaPagina);

        return 0;   
    }

    int gvl_appendNovaPagina(Arquivo *arq, int indexDesejado){
        
        gvl_flushBuffer(arq);

        size_t qtdBytes   = (size_t) GVL_TAM_PAGINA;
        
        fseek(arq->fp, 0, SEEK_END);
        
        int indexPag;
        if(ftell(arq->fp) == 0) // Arquivo vazio
            indexPag = 0;
        else
            indexPag = (ftell(arq->fp)/qtdBytes);

        // Verificando se o usuário não quer acessar muito além do fim do arquivo
        if(indexDesejado != indexPag)
            return 1;
        
        char*  novaPagina = malloc(qtdBytes * sizeof(char));
        memset(novaPagina, GVL_LIXO_MEM, qtdBytes);

        arq->bf.paginas[0]       = novaPagina;
        arq->bf.indexPaginas[0]  = indexPag;
        arq->bf.foiModificado[0] = 1;
        arq->bf.tamanhoPagina[0] = 0;

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
            size_t qtdBytes   = (size_t) GVL_TAM_PAGINA;
            
            if(arq->bf.indexPaginas[i] != GVL_INDEX_NULO && arq->bf.foiModificado[i]){
                
                fseek(arq->fp, arq->bf.indexPaginas[i] * qtdBytes, SEEK_SET);
                // printf("Escrevendo %ld bytes\n", arq->bf.tamanhoPagina[0]);
                fwrite(arq->bf. paginas[i], sizeof(char), arq->bf.tamanhoPagina[0], arq->fp);
                
                arq->bf.contadorAcessos += 1;
            }
            
            if(arq->bf.indexPaginas[i] != GVL_INDEX_NULO)
                free(arq->bf.paginas[i]);
            
            arq->bf.paginas[i]      = NULL;
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

