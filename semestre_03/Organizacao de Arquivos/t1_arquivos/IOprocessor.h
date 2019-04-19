/**
 * Trabalho de Organização de arquivos
 * Título: T1 - Geração e Leitura de Arquivos Binários
 * Autor:  Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
 * Prof.:  Dra. Cristina Dutra de Aguiar Ciferri
 * Data:   abril/2019
 * 
 * @library IOprecessor.h
 * 
 * DESCRIÇÃO
 * 
 * Essa biblioteca tem como objetivo simular a leitura e escrita
 * de páginas de discos, assim como o funcionamento de um Buffer 
 * Pool, que é uma função não visível para o programador em nível
 * de programação.
 * 
 * A motivação para a criação dessa biblioteca é de tornar mais fácil
 * o entendimento e a contagem de acessos à disco realizadas pelo programa, 
 * uma vez que ela encapsula as funções utilizada pelo FILE* do stdlib.
 */

#ifndef GVL_IO_PROCESSOR_H
    #define GVL_IO_PROCESSOR_H
    
    /**
     * Dependências da biblioteca.
     */
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    /**
     * CONSTANTES IMPORTANTES
     * 
     * @GVL_TAM_PAGINA      - Tamanho da página de disco utilizada.
     * @GVL_TAM_BUFFER_POOL - Quantidade máxima de páginas que o Buffer Pool
     *                        irá manter simultâneamente. 
     * @GVL_INDEX_NULO      - Constante usada para informar que um dos espaços
     *                        do buffer está inutilizado no momento.
     * @GVL_LIXO_MEM        - Byte de lixo de memória que irá ocupar posições não
     *                        escritas nos blocos de memória.
     */
        #define GVL_TAM_PAGINA       32000
        #define GVL_TAM_BUFFER_POOL  1
        #define GVL_INDEX_NULO      -1
        #define GVL_LIXO_MEM        '@'

    /**
     * @struct BufferPool
     * 
     * Representa a estrutura de um Buffer Pool durante a manipulação da
     * struct Arquivo (abaixo). Quando o usuário realiza uma leitura no disco
     * o sistema irá salvar um bloco de memória em um dos slots disponíveis do 
     * BufferPool.
     * 
     * ATRIBUTOS
     * @char* paginas[i]       - Array de bytes que irá armazenar os blocos de memória.
     * @char* foiModificado[i] - Flag que indica se aquele bloco de memória sofreu alguma
     *                           alteração e, portanto, deve ser reescrito no disco.
     * @int indexPaginas[i]    - Salva o index que identifica a i-ésima página de disco 
     *                           no Buffer Pool. Caso não haja nenhum bloco de memória salvo
     *                           no momento irá conter o valor de GVL_INDEX_NULO.
     * @long tamanhoPagina[i]  - Salva quanto da i-ésima página de disco foi de fato utiliza
     *                           da pelo usuário. Dessa forma, caso o usuário não utilize a 
     *                           página inteira do disco o programa escreverá apenas este valor.
     * @int contadorAcessos    - Salva quantos acessos o usuário já realizou ao disco desde a
     *                           abertura do arquivo.
     */ 
        typedef struct _bufferpool{
            char*       paginas[GVL_TAM_BUFFER_POOL];
            char        foiModificado[GVL_TAM_BUFFER_POOL];
            int         indexPaginas[GVL_TAM_BUFFER_POOL];
            long        tamanhoPagina[GVL_TAM_BUFFER_POOL];
            int         contadorAcessos;
        } BufferPool;

    /**
     * @struct Arquivo
     * 
     * Para o usuário final, essa estrutura irá funcionar similar ao
     * tipo FILE*. Porém ela irá contar com o BufferPool para realizar
     * todas as ações de acesso à disco.
     * 
     * ATRIBUTOS
     * @FILE* fp        - File pointer que irá realizar os acessos ao arquivo.
     * @BufferPool bf   - BufferPool que irá realizar as bufferizações de I/O
     * @long posicaoPtr - Ponteiro que irá apontar para a posição de leitura
     *                    atual.
     */
        typedef struct _arquivo{
            FILE*       fp;
            BufferPool  bf;
            long        posicaoPtr;
        } Arquivo;

    /** 
     * FUNÇÕES PARA ABRIR E MANIPULAR ARQUIVOS
     */

        /** 
         * @int gvl_abrirArquivo(Arquivo *arq, const char* nome, const char* modo);
         * Similar à função fopen().
         * 
         * @Arquivo* arq - Recebe, em caso de sucesso, o manipulador do Arquivo.
         * @char* nome   - Nome/path do caminho que será aberto.
         * @char* modo   - Modo de abertura do arquivo (Ex. wb+, r+, w+, etc).
         * @return 0 em caso de sucesso ou 1 em caso de erro. 
         */
        int     gvl_abrirArquivo(Arquivo *arq, const char* nome, const char* modo);

        /**
         * @int gvl_fecharArquivo(Arquivo *arq);
         * similar à função fclose().
         * 
         * @Arquivo *arq - Manipulador do arquivo que queremos fechar.
         * @return 0 em caso de sucesso ou 1 em caso de erro.
         */
        int     gvl_fecharArquivo(Arquivo *arq);

        /**
         * @int gvl_lerArquivo(Arquivo *arq, void* var, size_t qtdBytes);
         * similar à função fread().
         * 
         * @Arquivo *arq    - Manipulador do arquivo que queremos ler.
         * @void*    var    - Ponteiro da variável que irá armazenar os dados lidos.
         * @size_t qtdBytes - Quantidade de bytes que serão lidos do arquivo para @var.
         * @return 0 em caso de sucesso, 1 em caso de erro ou ao alcanar o EOF.
         */
        int     gvl_lerArquivo(Arquivo *arq, void* var, size_t qtdBytes);

        /**
         * @int gvl_escreverArquivo(Arquivo *arq, void* var, size_t qtdBytes);
         * similar à função fwrite().
         * 
         * @Arquivo *arq    - Manipulador do arquivo que queremos escrever.
         * @void*    var    - Ponteiro da variável que iremos escrever no arquivo.
         * @size_t qtdBytes - Quantidade de bytes que serão escritos de @var para o arquivo.
         * @return 0 em caso de sucesso, 1 em caso de erro.
         */
        int     gvl_escreverArquivo(Arquivo *arq, void* var, size_t qtdBytes);

        /**
         * @int gvl_seek(Arquivo *arq, long offset, int referencia);
         * similar à função fseek().
         * 
         * @Arquivo *arq   - Manipulador do arquivo que queremos alterar o ponteiro.
         * @long offset    - Posicao usada de acorto com a referência utilizada.
         * @int referencia - Estão implementadas as seguintes: SEEK_SET e SEEK_CUR
         * @return 0 em caso de sucesso, 1 em caso de erro.
         */
        int     gvl_seek(Arquivo *arq, long offset, int referencia);

    /**
     * FUNÇÕES PARA MANIPULAÇÃO EXPECÍFICA DE ARQUIVOS TEXTO
     */
        /**
         * @int gvl_lerLinha(Arquivo *arq, char* str, size_t qtdBytes);
         * similar à função gvl_lerArquivo(), irá ler até o máximo de qtdBytes ou
         * até encontrar uma quebra de linha '\n'.
         * 
         * @Arquivo *arq    - Manipulador do arquivo que queremos ler.
         * @void*    var    - Ponteiro da variável que irá armazenar os dados lidos.
         * @size_t qtdBytes - Quantidade máxima de bytes que serão lidos do arquivo para @var.
         * @return 0 em caso de sucesso, 1 em caso de erro ou ao alcanar o EOF.
         */
        int   gvl_lerLinha(Arquivo *arq, char* str, size_t qtdBytes);

    /**
     * FUNÇÕES DE CONTROLE DO BUFFER POOL
     */ 
        /**
         * @int gvl_paginaEstaCarregada(Arquivo *arq, int indexPag);
         * Verifica se a página de memória, identificada pelo seu @indexPag,
         * está carregada em algum dos slots do bufferPool.
         * 
         * @Arquivo *arq  - Manipulador do arquivo.
         * @int indexPag  - Index que identifica a página no disco.
         * @return 1 caso esteja ou 0 em caso de erro ou não esteja.
         */
        int     gvl_paginaEstaCarregada(Arquivo *arq, int indexPag);

        /**
         * @int gvl_carregarPagina(Arquivo *arq, int indexPag); 
         * Carrega, caso exista, a página de disco identificada por 
         * @indexPag do disco para algum dos slots do BufferPool.
         * Caso o BufferPool esteja cheio, libera algum dos slots.  
         * 
         * @Arquivo *arq  - Manipulador do arquivo.
         * @int indexPag  - Index que identifica a página no disco.
         * @return 0 em caso de sucesso, 1 em caso de erro.
         */
        int     gvl_carregarPagina(Arquivo *arq, int indexPag); // Usado na leitura

        /**
         * @int gvl_appendNovaPagina(Arquivo *arq, int indexDesejado);
         * Insere uma nova página de disco no fim do arquivo. Essa página
         * será identificada pelo @indexDesejado.
         * 
         * @Arquivo *arq  - Manipulador do arquivo.
         * @int indexPag  - Index da página que será inserida.
         * @return 0 em caso de sucesso, 1 em caso de erro.
         */
        int     gvl_appendNovaPagina(Arquivo *arq, int indexDesejado); // Usado na escrita

        /**
         * @int gvl_removerPagina(Arquivo *arq, int indexPag);
         * Remove a página identificada por @indexPag do bufferPool.
         * Escrevendo na memória as alterações caso tenha ocorrido alguma
         * escrita.
         * 
         * @Arquivo *arq  - Manipulador do arquivo.
         * @int indexPag  - Index da página que será removida.
         * @return 0 em caso de sucesso, 1 em caso de erro.
         */
        int     gvl_removerPagina(Arquivo *arq, int indexPag);

        /**
         * @int gvl_flushBuffer(Arquivo *arq);
         * Remove todas as páginas carregadas no Buffer Pool, escrevendo
         * na memória as alterações caso tenha ocorrido alguma escrita.
         * 
         * @Arquivo *arq  - Manipulador do arquivo.
         * @return 0 em caso de sucesso, 1 em caso de erro.
         */
        int     gvl_flushBuffer(Arquivo *arq);

    /**
     * FUNÇÕES AUXILIARES 
     */
        /**
         * @int gvl_indexPagina(long posicaoPtr);
         * Dada uma posição de ponteiro, retorna qual o index de página
         * aquele byte está.
         * 
         * Ex.:              0 <  pos < GVL_TAM_PAGINA => index 0
         *      GVL_TAM_PAGINA <= pos < 2*GVL_TAM_PAGINA => index 1
         *      ...
         * @return index da pagina
         */
        int     gvl_indexPagina(long posicaoPtr);

        /**
         * @int gvl_ptrPagina(Arquivo* arq, long posicaoPtr, int indexPagina);
         * Dada uma posição de ponteiro e um index de Pagina retorna um ponteiro
         * para o char do byte desejado no Buffer.
         * 
         * @Arquivo *arq    - Manipulador do arquivo.
         * @long posicaoPtr - posicaoPtr  do byte no arquivo.
         * @int indexPagina - index da página desejada.
         * @return ponteiro para byte na página
         */
        char*   gvl_ptrPagina(Arquivo* arq, long posicaoPtr, int indexPagina);

#endif