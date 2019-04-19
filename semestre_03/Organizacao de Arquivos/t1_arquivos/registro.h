/**
 * Trabalho de Organização de arquivos
 * Título: T1 - Geração e Leitura de Arquivos Binários
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

    /** Manipulação de registros em grande quantidade
     * 
     */ 
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