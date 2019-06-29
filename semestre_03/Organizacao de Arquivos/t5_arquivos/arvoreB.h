/**
 * Trabalho de Organização de arquivos
 * Autor:  Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
 *         Tamiris Fernandes Tinelli
 * Prof.:  Dra. Cristina Dutra de Aguiar Ciferri
 * Data:   jun/2019
 * 
 * @library arvoreB.h
 * 
 * DESCRIÇÃO
 * 
 * Essa biblioteca tem como objetivo implementar um index com estrutura
 * Arvore B conforme especificado nas aulas e no trabalho 5 da disciplina de
 * organização de arquivos.
 */

#ifndef GVL_ARVORE_B
    #define GVL_ARVORE_B

    /**
     * Bibliotecas e Constantes Importantes
     */
        #include "IOprocessor.h"

        #define BTREE_ORDEM      7 // 6 chaves e 7 ponteiros
        
        #define BTREE_TAM_PAGINA 105

        #define BTREE_ERROR           -1
        #define BTREE_POSSUI_PROMOCAO  2
        #define BTREE_NAO_POSSUI_PROMO 3   

    
     /**
     * @struct Chave
     * 
     * Representa o elemento mais simples que constitui os Nós de uma árvore B
     * 
     * ATRIBUTOS
     * @int   val - salva o valor do registro que será indexado 
     *                      (no caso desse trabalho o @idServidor)
     * @long  ptr - salva o byteOffset do registro.
     */ 
        typedef struct _chave{
            int  val; // chave -> valor indexado
            long ptr; // Ponteiro para o byte-offset
        } Chave;

    /**
     * @struct NoArvoreB
     * 
     * Representa um Nó de árvore B, cujo tamanho é o mesmo da pag. de disco
     * definida na constante e com ordem também definida na constante.
     * 
     * ATRIBUTOS
     * @int   index                     - Salva o index do nó.
     * @char  ehFolha                   - '1' se sim, '0' se não  
     * @int   qtdChaves                 - Quantidade de chaves existentes no nó
     * @Chave keys[BTREE_ORDEM-1]       - Chaves do nó
     * @int   pointers[BTREE_ORDEM]     - ponteiros que apontam para os index dos nós filhos. 
     */ 
        typedef struct _NoBtree {
            int   index;
            char  ehFolha;
            int   qtdChaves;
            Chave keys[BTREE_ORDEM-1];
            int   pointers[BTREE_ORDEM];
        } NoArvoreB;

    /**
     * @struct HeaderArvoreB
     * 
     * Registro de cabeçalho do Index de Árvore B. É salvo na primeira
     * página de disco do binário.
     * 
     * ATRIBUTOS
     * @char    status - '1' se OK ou '0' se corrompido.
     * @int     raiz   -  index do nó raíz ou -1 caso não haja nenhuma raíz ainda.
     */ 
        typedef struct _regCabecalhoBtree{
            char    status;
            int     raiz;
        } HeaderArvoreB;

    /**
     * MANIPULAÇÃO DO REGISTRO DE CABEÇALHO
     */ 
        /**
         * @HeaderArvoreB gvl_criarCabecalhoArvoreB(char status);
         * 
         * Cria uma struct do tipo HeaderArvoreB com as configurações zeradas pronta 
         * para o uso.
         */
        HeaderArvoreB gvl_criarCabecalhoArvoreB(char status);

        /**
         * @int gvl_escreverCabecalhoArvoreB(Arquivo* bin, HeaderArvoreB* hbt);
         * 
         * Escreve as informações do HeaderArvoreB na primeira página de disco.
         */
        int gvl_escreverCabecalhoArvoreB(Arquivo* bin, HeaderArvoreB* hbt);


        /**
         * @int gvl_escreverCabecalhoArvoreB(Arquivo* bin, HeaderArvoreB* hbt);
         * 
         * Lê as informações do HeaderArvoreB na primeira página de disco e retorna
         * para o usuário.
         */
        HeaderArvoreB gvl_carregarCabecalhoArvoreB(Arquivo *bin);

    /**
     * MANIPULAÇÃO DOS NÓS DA ÁRVORE  B
     */ 
        /**
         * @int gvl_lerNoArvoreB(Arquivo* bin, HeaderArvoreB* hbt, NoArvoreB* noBT, int indexPagina);
         * 
         * Lê os dados da página/nó da árvore com o indexPagina desejado e salva as informações no
         * @noBT. 
         * 
         * Caso haja algum erro na leitura retorna 1;
         */
        int gvl_lerNoArvoreB(Arquivo* bin, HeaderArvoreB* hbt, NoArvoreB* noBT, int indexPagina);

        /**
         * @void gvl_printarNo(NoArvoreB* noBT);
         * 
         * Exibe nas telas as informações do @noBT.
         */
        void gvl_printarNo(NoArvoreB* noBT);

    /**
     * MANIPULAÇÃO DA ARVORE B
     */ 
        /**
         * @int gvl_inserirChaveArvoreB(Arquivo* bin, HeaderArvoreB* hbt, int valor, long offset);
         * 
         * Insere uma nova chave no index de Árvore B. retorna 1 caso o registro já exista ou
         * ocorra algum erro na inserção.
         */
        int gvl_inserirChaveArvoreB(Arquivo* bin, HeaderArvoreB* hbt, int valor, long offset);
        
        /**
         * @int gvl_buscarChaveArvoreB(Arquivo* bin, HeaderArvoreB* hbt, int valor, long* offset);
         * 
         * Busca o byte offset de um registro na Árvore por meio de seu valor e salva em @offset.
         * Além disso retorna o número de níveis percorridos para encontrar a chave.
         * 
         * Retorna BTREE_ERROR caso ocorra algum erro ou não encontre o registro.
         */
        int gvl_buscarChaveArvoreB(Arquivo* bin, HeaderArvoreB* hbt, int valor, long* offset);

#endif