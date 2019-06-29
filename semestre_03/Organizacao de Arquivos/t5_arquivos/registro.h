/**
 * Trabalho de Organização de arquivos
 * Autor:  Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
 * Prof.:  Dra. Cristina Dutra de Aguiar Ciferri
 * Data:   abril/2019
 * 
 * @library registro.h
 * 
 * DESCRIÇÃO
 * 
 * Essa biblioteca tem como objetivo implementar as especificações
 * do trabalho em si. Ela utiliza a biblioteca IOprocessor.h para 
 * realizar os acessos a disco.
 * 
 */


#ifndef GVL_REGISTRO_H
    #define GVL_REGISTRO_H
    
    /**
     * Bibliotecas e Constantes Importantes
     */
        #include "IOprocessor.h"
        #include "index.h"
        #include "arvoreB.h"
        #include <time.h>

    /**
     * @struct Header
     * 
     * Representa um registro de cabeçalho, seguindo todos os campos
     * e nomenclaturas conforme especificadas na documentação do trabalho.
     * 
     * ATRIBUTOS
     * @char status[       - '1' caso o arquivo esteja consistente ou '0' caso
     *                       não esteja.
     * @long topoLista     - topo da lista de registros de dados removidos.
     * @char tagCampoN     - Tag que descreve o n-ésimo campo de dado.
     * @char desCampoN[]   - Descrição do n-ésimo campo de dado.
     */ 
        typedef struct _regCabecalho{
            char status;    
            long topoLista; 
            char tagCampo1;
            char desCampo1[40];
            char tagCampo2;
            char desCampo2[40];
            char tagCampo3;
            char desCampo3[40];
            char tagCampo4;
            char desCampo4[40];
            char tagCampo5;
            char desCampo5[40];
        } Header;

    /**
     * @struct Registro
     * 
     * Representa um registro de dados, seguindo todos os campos
     * e nomenclaturas conforme especificadas na documentação do trabalho.
     * 
     * ATRIBUTOS
     * @char removido       - '-' caso o arquivo esteja em suo ou '*' caso
     *                        o arquivo tenha sido removido.
     * @int tamanhoRegistro - Tamanho em bytes do registro desconsiderando os
     *                        5 bytes de @removido e @tamanhoRegistro.
     * @long encadeamentoLista - proximo elemento da lista de registros removidos
     * @type ____Servidor      - dados do servidor.
     */ 
        typedef struct _regDados{
            char    removido;
            int     tamanhoRegistro;
            long    encadeamentoLista;
            int     idServidor;
            double  salarioServidor;
            char    telefoneServidor[15];
            char*   nomeServidor;
            char*   cargoServidor;
        } Registro;

    /** 
     * MANIPULAÇÃO DE REGISTROS DE CABEÇALHO
     */ 
        /**
         * @Header gvl_textoParaCabecalho(char* str, size_t size);
         * Transforma a linha de cabeçalho do CSV em um struct Header
         * e retorna ele para o usuário.
         * 
         * @char*  str  - linha de cabeçalho do CSV.
         * @site_t size - tamanho da linha de cabeçalho.
         * @return registro de cabeçalho.
         */
        Header gvl_textoParaCabecalho(char* str, size_t size);

        /**
         * @int gvl_escreverCabecalho(Arquivo* bin, Header* h);
         * Escreve o registro de cabeçalho na primeira página de
         * um arquivo binário.
         * 
         * @Arquivo*  bin  - Manipulador do arquivo binário.
         * @Header h       - Registro de cabeçalho.
         * @return 0 em caso de sucesso e 1 em caso de erro.
         */
        int gvl_escreverCabecalho(Arquivo* bin, Header* h);

        /**
         * @Header gvl_carregarCabecalho(Arquivo *bin);
         * Carrega de um arquivo binário o registro de cabeçalho.
         * 
         * @Arquivo*  bin  - Manipulador do arquivo binário.
         * @return registro de cabeçalho.
         */
        Header gvl_carregarCabecalho(Arquivo *bin);
        
        /**
         * @int gvl_setStatusCabecalho(Arquivo* bin, Header* h, char flag);
         * Altera a flag de status no arquivo binário para o conteudo de @flag.
         * Usada para saber se um arquivo que sofria alterações foi encerrado de
         * maneira devida.
         * 
         * @Arquivo*  bin  - Manipulador do arquivo binário.
         * @Header*   h    - Manipulador do registro de cabeçalho.
         * @return 0 em caso de sucesso e 1 em caso de erro.
         */
        int gvl_setStatusCabecalho(Arquivo* bin, Header* h, char flag);

    /** 
     * MANIPULAÇÃO DE REGISTROS DE DADOS
     */ 
         /**
         * @int gvl_inserirNovoRegistro(Arquivo* bin, Header* h, Registro* r);
         * Insere um novo registro no arquivo bin. O Registro pode ser inserido
         * em um espaço de registro lógicamente removido OU no final do arquivo
         * caso não haja espaços livres disponiveis.
         */
        int gvl_inserirNovoRegistro(Arquivo* bin, Header* h, Registro* r);

        /**
         * @void gvl_destruirRegistro(Registro* r);
         * Função auxiliar para desalocar as variáveis dinâmicas de um
         * registro de dados.
         */
        void gvl_destruirRegistro(Registro* r);

        /**
         * @int gvl_gerarBinFromCSV(Arquivo* csv, Arquivo* bin);
         * Lê um arquivo CSV com múltiplos registros de dados e transcreve
         * esses dados em um arquivo binário.
         * 
         * @Arquivo*  bin  - Manipulador do arquivo binário.
         * @Arquivo*  csv  - Manipulador do arquivo CSV.
         * @return 0 em caso de sucesso ou 1 em caso de erro
         */
        int gvl_gerarBinFromCSV(Arquivo* csv, Arquivo* bin);

        /**
         * @int gvl_listarRegistros(Arquivo* bin);
         * Lê um arquivo binário válido e exibe na tela todos os
         * registros de dados salvos.
         * 
         * @Arquivo*  bin  - Manipulador do arquivo binário.
         * @return quantidade de registros exibidos.
         */
        int gvl_listarRegistros(Arquivo* bin);

        /**
         * @int gvl_buscarRegistros(Arquivo* bin, Header* h, char tagCampo, char* valor, int onlyFirst);
         * Lê um arquivo binário válido e exibe na tela todos os
         * registros de dados salvos cujo valor buscado esteja contido 
         * no campo desejado.
         * 
         * @Arquivo*  bin  - Manipulador do arquivo binário.
         * @Header*   h    - Manipulador do registro de cabeçalho
         * @char tagCampo  - Campo em que o dado será pesquisado.
         * @char* valor    - Valor sendo buscado nos dados.
         * @int onlyFirst  - Caso verdadeira, pausa a busca após encontar
         *                   o primeiro registro.
         * @return quantidade de registros exibidos.
         */
        int gvl_buscarRegistros(Arquivo* bin, Header* h, char tagCampo, char* valor, int onlyFirst);
        
        /**
         * @int gvl_removerRegistros(Arquivo* bin, Header* h, char tagCampo, char* valor, int onlyFirst);
         * Busca e remove os registros que corresponderem ao critério de busca. Os
         * registros removidos são adicionados ao encadeamento de registros
         * removidos lógicamente.
         */
        int gvl_removerRegistros(Arquivo* bin, Header* h, char tagCampo, char* valor, int onlyFirst);

        /**
         * @int gvl_atualizarRegistros(Arquivo* bin, Header* h, char tagBusca, char* valorBusca, char tagAtualiza, char* valorAtualiza, int onlyFirst);
         * Busca e atualiza os registros que corresponderem ao critério de busca. Caso
         * o tamanho do registro aumente e não haja espaço suficiente ele é removido e
         * reinserido no arquivo.
         */
        int gvl_atualizarRegistros(Arquivo* bin, Header* h, char tagBusca, char* valorBusca, char tagAtualiza, char* valorAtualiza, int onlyFirst);
        
        /**
         * @int gvl_ordenarArquivo(Arquivo* binEntrada, Arquivo* binSaida, Header* h);
         * Realiza a ordenação interna do arquivo. Porém não sobrescreve o arquivo atual
         * mas gera um arquivo de saída com os dados ordenados pelo idServidos.
         */
        int gvl_ordenarArquivo(Arquivo* binEntrada, Arquivo* binSaida, Header* h);
      
        /**
         * @int gvl_mergingArquivos(Arquivo* binL, Arquivo* binR, Arquivo* binSaida, Header* h);
         * Realiza o merging entre dois arquivos e gera um arquivo de saída com os
         * registros resultados.
         * 
         * Obs.: os arquivos precisam estar previamente ordenados por idServidor.
         */
        int gvl_mergingArquivos(Arquivo* binL, Arquivo* binR, Arquivo* binSaida, Header* h);

        /**
         * @int gvl_matchingArquivos(Arquivo* binL, Arquivo* binR, Arquivo* binSaida, Header* h);
         * Realiza o matching entre dois arquivos e gera um arquivo de saída com os
         * registros resultados.
         * 
         * Obs.: os arquivos precisam estar previamente ordenados por idServidor.
         */
        int gvl_matchingArquivos(Arquivo* binL, Arquivo* binR, Arquivo* binSaida, Header* h);
        
    /**
     * MANIPULAÇÃO DA LISTA DE REGISTROS REMOVIDOS
     */
        typedef struct _removido{
            int         tamanhoRegistro;
            long        filePos;
            int         tempoRemocao;
        } RegRemovido;
        
        RegRemovido*    listaRemovidos;
        int             tamListaRemovidos;
        int             tempoRemovidos;

        void gvl_carregarListaRemovidos(Arquivo* bin, Header* h);

        void gvl_limparListaRemovidos(Arquivo* bin, Header* h);

        void gvl_inserirNovoRemovido(Arquivo* bin, Header* h, Registro* r, long ptrPos, int getTime);

        void gvl_ordenarRegistrosRemovidos(Arquivo* bin, Header* h, int l, int r);

        void gvl_escreverRegistroRemovidos(Arquivo* bin, Header* h);

        void gvl_exibirListaRemovidos(Arquivo* bin, Header* h);

    /**
     * MANIPULAÇÃO DA LISTA DE INDICES
     */
        /**
         * @int gvl_criarVetorIndices(Arquivo* bin, Header* h, Index** indices, HeaderIndex* hi);
         * Gera um HeaderIndex e um vetor de indices para um arquivo que ainda não
         * possui um arquivo .index.
         * 
         * Retorna 1 em caso de erro.
         */
        int gvl_criarVetorIndices(Arquivo* bin, Header* h, Index** indices, HeaderIndex* hi);

        /**
         * @int gvl_buscarRegistros2(Arquivo* bin, Header* h, Index** indices, HeaderIndex* hi, char* valor);
         * Possui a mesma função que a função @gvl_buscarRegistro() porém sem realizar
         * uma busca sequencial em todo arquivo mas utilizando index e acesso direto.
         * 
         * Retorna a quantidade de registros buscados.
         */
        int gvl_buscarRegistros2(Arquivo* bin, Header* h, Index** indices, HeaderIndex* hi, char* valor);

        /**
         * @int gvl_removerRegistros2(Arquivo* bin, Header* h, Index** indices, HeaderIndex* hi, char* valor);
         * Possui a mesma função que a função @gvl_removerRegistros() porém sem realizar
         * uma busca sequencial em todo arquivo mas utilizando index e acesso direto.
         * 
         * Retorna a quantidade de registros buscados.
         */
        int gvl_removerRegistros2(Arquivo* bin, Header* h, Index** indices, HeaderIndex* hi, char* valor);

        /**
         * @int gvl_inserirNovoRegistro2(Arquivo* bin, Header* h, Index** indices, HeaderIndex* hi, Registro* r);
         * Possui a mesma função que a função @gvl_inserirNovoRegistro() porém além de
         * adicionar o registro no arquivo também o adiciona na lista de indices.
         * 
         * Obs.: o arquivo de indices não é ordenado após a inserção.
         * 
         * Retorna a quantidade de registros buscados.
         */
        int gvl_inserirNovoRegistro2(Arquivo* bin, Header* h, Index** indices, HeaderIndex* hi, Registro* r);
    
    /**
     * MANIPULAÇÕES DA ÁRVORE-B
     */ 
        /**
         * @int gvl_criarBTree(Arquivo* bin, Header* h, Arquivo* binBT);
         * Gera uma estrutura de Index Árvore B no arquivo binBT.
         * 
         * Retorna 1 em caso de erro.
         */
        int gvl_criarBTree(Arquivo* bin, Header* h, Arquivo* binBT);

        /**
         * @int gvl_buscarRegistros3(Arquivo* bin, Header* h, Arquivo* binBT, HeaderArvoreB* hbt, int valor);
         * Dado um id de usuário, um arquivo de dados e um arquivo indice de árvore binária. Busca o registro
         * e exibe caso o encontre. 
         * 
         * Retorna o número de níveis percorridos na árvore ou BTREE_ERROR caso não encontre o arquivo.
         */
        int gvl_buscarRegistros3(Arquivo* bin, Header* h, Arquivo* binBT, HeaderArvoreB* hbt, int valor);

    /** 
     * FUNÇÕES AUXILIARES / MISCELÂNIA
     */
        /**
         * @void gvl_explode(char* str, char delimiter, char* vet[5]);
         * Separa uma dada string @str em um vetor de strings por meio
         * de um @delimiter.
         * 
         * Ex: "ola, como vai, você" => {'ola', 'como vai', 'voce', null, null}
         */
        void gvl_explode(char* str, char delimiter, char* vet[5]);

#endif