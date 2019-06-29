#include "arvoreB.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/** Manipulação do Cabeçalho da árvore B.
 */ 
    HeaderArvoreB gvl_criarCabecalhoArvoreB(char status){
        HeaderArvoreB hbt;
        hbt.raiz   = -1;
        hbt.status = status;
        return hbt;
    }

    HeaderArvoreB gvl_carregarCabecalhoArvoreB(Arquivo *bin){
        HeaderArvoreB hbt;
        memset(&hbt, GVL_LIXO_MEM, sizeof(HeaderArvoreB));

        if(bin == NULL || bin->fp == NULL)
            return hbt;

        gvl_seek(bin, 0, SEEK_SET);
        gvl_lerArquivo(bin, &(hbt.status),       sizeof(char));
        gvl_lerArquivo(bin, &(hbt.raiz), sizeof(int));

        return hbt;
    }

    int gvl_escreverCabecalhoArvoreB(Arquivo* bin, HeaderArvoreB* hbt){
       if(bin == NULL || bin->fp == NULL)
            return 1;

        gvl_seek(bin, 0, SEEK_SET);
        gvl_escreverArquivo(bin, &(hbt->status),       sizeof(char));
        gvl_escreverArquivo(bin, &(hbt->raiz), sizeof(int));
        
        // Economiza o fato de ter que fazer o fill com lixo
        bin->bf.tamanhoPagina[0] = BTREE_TAM_PAGINA;
        gvl_flushBuffer(bin);

        return 0;
    }

    int gvl_setStatusCabecalhoArvoreB(Arquivo* bin, HeaderArvoreB* hbt, char flag){
        if(bin == NULL || bin->fp == NULL || hbt == NULL)
            return 1;

        gvl_seek(bin, 0, SEEK_SET);
        if( gvl_escreverArquivo(bin, &flag, sizeof(char)) )
            return 1;

        hbt->status = flag;
        return 0;
    }

    int gvl_calcularNovoIndex(Arquivo* bin){
        if(bin == NULL)
            return -1;

        gvl_flushBuffer(bin);
        fseek(bin->fp, 0, SEEK_END);

        int index = ceil(ftell(bin->fp)/BTREE_TAM_PAGINA);
        return (index-1);
    }

/** Manipulação dos Nós da Árvore B
 */
    NoArvoreB gvl_novoNoArvoreB(int ehFolha){
        NoArvoreB no;
        memset(&no, -1, sizeof(NoArvoreB));
        no.qtdChaves = 0;
        no.ehFolha   = ehFolha;
        return no;
    }

    int gvl_lerNoArvoreB(Arquivo* bin, HeaderArvoreB* hbt, NoArvoreB* noBT, int indexPagina){
        if(bin == NULL || bin->fp == NULL || hbt == NULL || noBT == NULL || indexPagina < 0)
            return 1;

        // Direciona o ponteiro do arquivo para a página desejada e faz as leituras
        // gvl_seek(bin, BTREE_TAM_PAGINA*(indexPagina+1), SEEK_SET);
        // gvl_lerArquivo(bin, &(noBT->ehFolha),   sizeof(char));
        // gvl_lerArquivo(bin, &(noBT->qtdChaves), sizeof(int));

        // for(int i = 0; i < BTREE_ORDEM; i++){
        //     gvl_lerArquivo(bin, &(noBT->pointers[i]), sizeof(int));
        //     if(i < BTREE_ORDEM-1){
        //         gvl_lerArquivo(bin, &(noBT->keys[i].val), sizeof(int));
        //         gvl_lerArquivo(bin, &(noBT->keys[i].ptr), sizeof(long));
        //     }
        // }

        fseek(bin->fp, BTREE_TAM_PAGINA*(indexPagina+1), SEEK_SET);
        fread(&(noBT->ehFolha),  sizeof(char), 1, bin->fp);
        fread(&(noBT->qtdChaves), sizeof(int), 1, bin->fp);
        for(int i = 0; i < BTREE_ORDEM; i++){
            fread(&(noBT->pointers[i]), sizeof(int), 1, bin->fp);
            if(i < BTREE_ORDEM-1){
                fread(&(noBT->keys[i].val), sizeof(int),  1, bin->fp);
                fread(&(noBT->keys[i].ptr), sizeof(long), 1, bin->fp);
            }
        }

        noBT->index = indexPagina;
        return 0;
    }

    int gvl_lerPrimeiraChave(Arquivo* bin, HeaderArvoreB* hbt, Chave* key, int indexPagina){
        if(bin == NULL || bin->fp == NULL || hbt == NULL || indexPagina < 0)
            return 1;

        // Direciona o ponteiro do arquivo para a página desejada e faz as leituras
        long seek_offset = BTREE_TAM_PAGINA*(indexPagina+1);
        seek_offset     += sizeof(char) + sizeof(int) + sizeof(int);
        
        gvl_seek(bin, seek_offset, SEEK_SET);
        gvl_lerArquivo(bin, &(key->val), sizeof(int));
        gvl_lerArquivo(bin, &(key->ptr), sizeof(long));

        return 0;
    }

    int gvl_escreverNoArvoreB(Arquivo* bin, HeaderArvoreB* hbt, NoArvoreB* noBT, int indexPagina){
        if(bin == NULL || bin->fp == NULL || hbt == NULL || noBT == NULL || indexPagina < 0)
            return 1;

        // Direciona o ponteiro do arquivo para a página desejada e faz as leituras
        gvl_seek(bin, BTREE_TAM_PAGINA*(indexPagina+1), SEEK_SET);
        gvl_escreverArquivo(bin, &(noBT->ehFolha),   sizeof(char));
        gvl_escreverArquivo(bin, &(noBT->qtdChaves), sizeof(int));

        for(int i = 0; i < BTREE_ORDEM; i++){
            gvl_escreverArquivo(bin, &(noBT->pointers[i]), sizeof(int));
            if(i < BTREE_ORDEM-1){
                gvl_escreverArquivo(bin, &(noBT->keys[i].val), sizeof(int));
                gvl_escreverArquivo(bin, &(noBT->keys[i].ptr), sizeof(long));
            }
        }

        gvl_flushBuffer(bin);
        return 0;
    }

    int gvl_inserirChave(NoArvoreB* noBT, Chave key){
        if(noBT == NULL)
            return 1;

        // Lembrando que na Árvore B só há inserções em Nós Folhas, então
        // não é necessário se preocupar em ordenar os ponteiros pois são
        // todos nulos.
        Chave cur     = key;
        Chave temp;
    
        for(int i = 0; i < noBT->qtdChaves; i++){
            if(cur.val < noBT->keys[i].val) {
                temp          = noBT->keys[i];
                noBT->keys[i] = cur;
                cur           = temp;
            }
        }

        noBT->keys[noBT->qtdChaves] = cur;
        noBT->qtdChaves += 1;
       
        return 0;
    }

    int gvl_splitarNo(Arquivo* bin, Chave overflow, int ptrOverflow, NoArvoreB* noLeft, Chave* promovida, NoArvoreB* noRight){
        if(noLeft == NULL || noRight == NULL || promovida == NULL)
            return 1;

        Chave  aux[BTREE_ORDEM];
        int auxPtr[BTREE_ORDEM+1];

        memset(aux, -1, sizeof(aux));
        memset(auxPtr, -1, sizeof(auxPtr));

        int i = 0, j = 0, k = 0, inseriu = 0, indexTemp;
        Chave keyAux;
        keyAux.ptr = -1;

        (*noRight)     = gvl_novoNoArvoreB('1');
        noRight->index = gvl_calcularNovoIndex(bin);

        /**
         * 1º Etapa
         * Carrega os valores no vetor auxiliar e limpa ambas os nós
         */
        j = 0;
        for(i = 0; i < BTREE_ORDEM; i++){
            if(!inseriu && (overflow.val < noLeft->keys[j].val || noLeft->keys[j].val == -1 || j >= BTREE_ORDEM-1)){
                aux[i] = overflow;
                inseriu  = 1; 
            } else {
                aux[i] = noLeft->keys[j++];
            }
        }

        j = 0;
        for(i = 0; i < BTREE_ORDEM+1; i++){
            if(overflow.val != aux[j].val){
                auxPtr[i] = noLeft->pointers[j++];
            } else {
                auxPtr[i++] = noLeft->pointers[j++];
                auxPtr[i]   = ptrOverflow;
                
            }
        } 

        // Prints de conferência
        // for(i = 0; i < BTREE_ORDEM; i++){
        //    printf("{%d} (%d) ", auxPtr[i], aux[i].val);
        // } printf("{%d}\n\n", auxPtr[i]);

        // Reiniciando as variáveis dos nós para reinserir distribuidamente.
        indexTemp     = noLeft->index;
        (*noLeft)     = gvl_novoNoArvoreB(noLeft->ehFolha);
        noLeft->index = indexTemp;

        /**
         * 2ª Etapa - Redistribuindo as chaves entre os 2 nós 
         */
        i = 0;
        j = 0;
        k = 0; 
        for( ;i < (BTREE_ORDEM-1)/2; ){
            noLeft->keys[j]       = aux[i];
            noLeft->pointers[j]   = auxPtr[k];
            noLeft->qtdChaves    += 1;
            i++;
            j++;
            k++;
        }
        noLeft->pointers[j++] = auxPtr[k++];

        (*promovida) = aux[i++];

        j = 0;
        for(  ;i < BTREE_ORDEM; ){
            noRight->keys[j]     = aux[i];
            noRight->pointers[j] = auxPtr[k];
            noRight->qtdChaves   += 1;
            i++;
            j++;
            k++;
        }
        noRight->pointers[j++] = auxPtr[k++];

        // Apenas validando se o novo Nó é folha ou não
        for(i = 0; i < BTREE_ORDEM; i++){
            if(noRight->pointers[i++] != -1)
                noRight->ehFolha = '0';
        }

        return 0;
    }

    int gvl_buscarChave(NoArvoreB* noBT, int value, Chave* result){
        if(noBT == NULL)
            return 0;

        for(int i = 0; i < BTREE_ORDEM-1; i++){
            if(noBT->keys[i].val == value){
                (*result) = noBT->keys[i];
                return 1;
            }
        }

        return 0;
    }

    int gvl_buscarPonteiro(NoArvoreB* noBT, int value, int* ptr){
        if(noBT == NULL)
            return 1;

        int i = 0;
        while(i < noBT->qtdChaves &&  value > noBT->keys[i].val ){
            i++;
        }
        (*ptr) = noBT->pointers[i];
        return 0;
    }

    void gvl_printarNo(NoArvoreB* noBT){
        printf("%c[%d com %d]\t",  noBT->ehFolha, noBT->index, noBT->qtdChaves);
        for(int i = 0; i < BTREE_ORDEM-1; i++){
            printf("{%d} (%d,%ld), ", noBT->pointers[i], noBT->keys[i].val, noBT->keys[i].ptr % GVL_TAM_PAGINA);
        }
        printf("{%d}\n", noBT->pointers[BTREE_ORDEM-1]);
    }

/** Manipulação da Árvore pelo usuário
 */
    int _gvl_inserirChaveChild(Arquivo* bin, HeaderArvoreB* hbt, int indexPagina, Chave key, Chave* promovida, int* indexRight){
        if(bin == NULL || hbt == NULL)
            return BTREE_ERROR;
        
        NoArvoreB noAtual;
        gvl_lerNoArvoreB(bin, hbt, &noAtual, indexPagina);

        // gvl_printarNo(&noAtual);

        // Variáveis de controle para a operação de split ou caso 
        // haja alguma promoção  de um nó filho.
        int       filhoChamado;
        NoArvoreB noRight;
        Chave     chavePromovida;
        Chave     chaveAux;

        /**
         * Caso trivial - Chave já existe
         * - Não faz nada mas retorna erro;
         */
        if(gvl_buscarChave(&noAtual, key.val, &chaveAux)){
            return BTREE_ERROR;        

        /**
         * 1º Caso - O nó é folha e possui espaço
         * - Insere a chave nesse nó e atualiza no disco.
         */
        } else if(noAtual.ehFolha == '1' && noAtual.qtdChaves < BTREE_ORDEM-1){
            gvl_inserirChave(&noAtual, key);
            gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);
            
            // Funcionando...
            // gvl_printarNo(&noAtual);

            return BTREE_NAO_POSSUI_PROMO;

        /**
         * 2º Caso - o Nó é folha mas está lotado
         * - Prepara as variáveis para o split e promoção.
         * - Escreve os nós atualizados.
         */
        } else if(noAtual.ehFolha == '1' && noAtual.qtdChaves >= BTREE_ORDEM-1){
            //printf("\nSPLIT DOS PONTEIROS DE UMA FOLHA\n");
            gvl_splitarNo(bin, key, -1, &noAtual, &chavePromovida, &noRight);

            // Atualizando os nós
            gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);

            noRight.index = gvl_calcularNovoIndex(bin);
            gvl_escreverNoArvoreB(bin, hbt, &noRight, noRight.index);

            (*promovida)  = chavePromovida;
            (*indexRight) = noRight.index;
            
            
            // gvl_printarNo(&noAtual);
            // printf("Promovendo (%d) [%d]\n", chavePromovida.val, noRight.index);
            // gvl_printarNo(&noRight);
            // printf("\n\n");

            return BTREE_POSSUI_PROMOCAO;
        }

        /**
         * 3º caso - o Nó não é folha
         * - Joga a inserção pro filho e verifica se houve alguma chave expandida.
         * - Caso haja faz uma inserção normalmente.
         * - Há repetição do código anterior, mas deixar juntos deixaria confuso....
         */
        if(noAtual.ehFolha == '0'){

            if(gvl_buscarPonteiro(&noAtual, key.val, &filhoChamado) || filhoChamado == -1){
                printf("Algo inesperado aconteceu cód. 1...\n");
                return BTREE_ERROR;
            }

            // printf("Chamando filho %d... \n", filhoChamado);
            int ret = _gvl_inserirChaveChild(bin, hbt, filhoChamado, key, &chavePromovida, &(noRight.index));
        
            if(ret == BTREE_ERROR){
                printf("Algo inesperado aconteceu cód. 2...\n");
                return BTREE_ERROR;
            
            } else if( ret == BTREE_NAO_POSSUI_PROMO) {
                return BTREE_NAO_POSSUI_PROMO;
            } 

            // Se passou por aqui então houve promoção
            if(noAtual.qtdChaves < BTREE_ORDEM-1){
                
                int posFilhoChamado = -1;
                for(int i = 0; i < BTREE_ORDEM; i++){
                    if(noAtual.pointers[i] == filhoChamado)
                        posFilhoChamado = i;
                } 
                
                // Precisa shiftar todos os nós maiores para inserir o novo nó promovido
                // Carrega também os ponteiros à esquerda dos nós.
                for(int i = BTREE_ORDEM-2; i >= posFilhoChamado; i--){
                    noAtual.keys[i] = noAtual.keys[i-1];
                }
                for(int i = BTREE_ORDEM-1; i > posFilhoChamado; i--){
                    noAtual.pointers[i] = noAtual.pointers[i-1];
                }

                noAtual.keys[posFilhoChamado]       = chavePromovida;
                noAtual.pointers[posFilhoChamado+1] = noRight.index;
                noAtual.qtdChaves                  +=1;

                // Atualiza o nó atual no disco
                gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);
                //printf("Recebeu promoção (%d) [%d]\n", chavePromovida.val, noRight.index);
                //gvl_printarNo(&noAtual);
                //printf("\n");

                return BTREE_NAO_POSSUI_PROMO;

            } else if(noAtual.qtdChaves >= BTREE_ORDEM-1){
                
                //printf("\n \033[36m SPLIT DOS PONTEIROS DE UMA PAI (Não Raiz) \033[0;0m \n");
                gvl_splitarNo(bin, chavePromovida, noRight.index, &noAtual, &chavePromovida, &noRight);

                // Atualizando os nós
                gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);

                noRight.index      = gvl_calcularNovoIndex(bin);
                gvl_escreverNoArvoreB(bin, hbt, &noRight, noRight.index);

                (*promovida)  = chavePromovida;
                (*indexRight) = noRight.index;

                gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);
                
                // gvl_printarNo(&noAtual);
                // printf("Promovendo (%d) [%d]\n", chavePromovida.val, noRight.index);
                // gvl_printarNo(&noRight);
                // printf("\n");

                return BTREE_POSSUI_PROMOCAO;
            }
        }

        return BTREE_NAO_POSSUI_PROMO;
    }

    int _gvl_inserirChaveRaiz(Arquivo* bin, HeaderArvoreB* hbt, Chave key){
        if(bin == NULL || hbt == NULL)
            return BTREE_ERROR;
        
        NoArvoreB noAtual;
        
        if(hbt->raiz == -1){
            noAtual = gvl_novoNoArvoreB('1');
            noAtual.index = 0;
            hbt->raiz     = 0;
        } else {
            gvl_lerNoArvoreB(bin, hbt, &noAtual, hbt->raiz);
        }

        // gvl_printarNo(&noAtual);

        // Variáveis de controle para a operação de split ou caso 
        // haja alguma promoção  de um nó filho.
        int       filhoChamado;
        NoArvoreB noRight;
        Chave     chavePromovida;
        Chave     chaveAux;

        /**
         * Caso trivial - Chave já existe
         * - Não faz nada e retorna erro;
         */
        if(gvl_buscarChave(&noAtual, key.val, &chaveAux) == 1){
            return BTREE_ERROR;        

        /**
         * 1º Caso - O nó é folha e possui espaço
         * - Insere a chave nesse nó e atualiza no disco.
         */
        } else if(noAtual.ehFolha == '1' && noAtual.qtdChaves < BTREE_ORDEM-1){
            gvl_inserirChave(&noAtual, key);
            gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);

            // Funcionando
            // gvl_printarNo(&noAtual);
            return BTREE_NAO_POSSUI_PROMO;

        /**
         * 2º Caso - o Nó é folha mas está lotado
         * - Prepara as variáveis para o split e promoção.
         * - Cria um novo nó para ser a nova raíz e atualiza o hbt
         */
        } else if(noAtual.ehFolha == '1' && noAtual.qtdChaves >= BTREE_ORDEM-1){
            //printf("\nSPLIT DOS PONTEIROS DE UMA RAIZ\n");
            gvl_splitarNo(bin, key, -1, &noAtual, &chavePromovida, &noRight);

            NoArvoreB novaRaiz = gvl_novoNoArvoreB('0');
            novaRaiz.qtdChaves = 1;
            novaRaiz.keys[0]   = chavePromovida;
            novaRaiz.pointers[0] = noAtual.index;
            novaRaiz.pointers[1] = noRight.index;
            
            // Atualizando os nós e o ponteiro para a raíz
            gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);

            noRight.index      = gvl_calcularNovoIndex(bin);
            gvl_escreverNoArvoreB(bin, hbt, &noRight, noRight.index);

            novaRaiz.index       = gvl_calcularNovoIndex(bin);
            gvl_escreverNoArvoreB(bin, hbt, &novaRaiz, novaRaiz.index);
            hbt->raiz = novaRaiz.index;

            // gvl_printarNo(&noAtual);
            // gvl_printarNo(&novaRaiz);
            // gvl_printarNo(&noRight);
            return BTREE_NAO_POSSUI_PROMO;
        }

        /**
         * 3º caso - o Nó não é folha
         * - Joga a inserção pro filho e verifica se houve alguma chave expandida.
         * - Caso haja faz uma inserção normalmente.
         * - Há repetição do código anterior, mas deixar juntos deixaria confuso....
         */
        if(noAtual.ehFolha == '0'){

            if(gvl_buscarPonteiro(&noAtual, key.val, &filhoChamado)){
                printf("Algo inesperado aconteceu cód. 1...\n");
                return BTREE_ERROR;
            }

            // printf("Chamando filho %d...\n", filhoChamado);

            int ret = _gvl_inserirChaveChild(bin, hbt, filhoChamado, key, &chavePromovida, &(noRight.index));
        
            if(ret == BTREE_ERROR){
                printf("Algo inesperado aconteceu cód. 2...\n");
                return BTREE_ERROR;
            
            } else if( ret == BTREE_NAO_POSSUI_PROMO) {
                return BTREE_NAO_POSSUI_PROMO;
            } 

        // Se passou por aqui então houve promoção
            if(noAtual.qtdChaves < BTREE_ORDEM-1){
                
                int posFilhoChamado = -1;
                for(int i = 0; i < BTREE_ORDEM; i++){
                    if(noAtual.pointers[i] == filhoChamado)
                        posFilhoChamado = i;
                } 

                // Precisa shiftar todos os nós maiores para inserir o novo nó promovido
                // Carrega também os ponteiros à esquerda dos nós.
                for(int i = BTREE_ORDEM-2; i >= posFilhoChamado; i--){
                    noAtual.keys[i] = noAtual.keys[i-1];
                }
                for(int i = BTREE_ORDEM-1; i > posFilhoChamado; i--){
                    noAtual.pointers[i] = noAtual.pointers[i-1];
                }

                noAtual.keys[posFilhoChamado]       = chavePromovida;
                noAtual.pointers[posFilhoChamado+1] = noRight.index;
                noAtual.qtdChaves               +=1;

                // Atualiza o nó atual no disco
                gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);
                // printf("Recebeu promoção (%d) [%d]\n", chavePromovida.val, noRight.index);
                // gvl_printarNo(&noAtual);

                return BTREE_NAO_POSSUI_PROMO;

            } else if(noAtual.qtdChaves >= BTREE_ORDEM-1){
                
                // A chave à ser inserida é a promovida pelo filho, e ela tem um nó apontando para a direita.
                // printf("\n \033[36m SPLIT DOS PONTEIROS DE UMA RAIZ 2 \033[0;0m \n");
                // printf("Recebeu promoção (%d) [%d]\n", chavePromovida.val, noRight.index);
                gvl_splitarNo(bin, chavePromovida, noRight.index, &noAtual, &chavePromovida, &noRight);
                
                // printf("Promoveu (%d) [%d]\n", chavePromovida.val, noRight.index);

                // Atualizando os nós e o ponteiro para a raíz
                gvl_escreverNoArvoreB(bin, hbt, &noAtual, noAtual.index);

                noRight.index      = gvl_calcularNovoIndex(bin);
                gvl_escreverNoArvoreB(bin, hbt, &noRight, noRight.index);

                NoArvoreB novaRaiz = gvl_novoNoArvoreB('0');
                novaRaiz.qtdChaves   = 1;
                novaRaiz.keys[0]     = chavePromovida;
                novaRaiz.pointers[0] = noAtual.index;
                novaRaiz.pointers[1] = noRight.index;
                novaRaiz.index       = gvl_calcularNovoIndex(bin);

                gvl_escreverNoArvoreB(bin, hbt, &novaRaiz, novaRaiz.index);
                hbt->raiz = novaRaiz.index;

                // printf("PROMOÇÃO NA RAÍZ COM SPLIT...\n");
                // gvl_printarNo(&noAtual);
                // gvl_printarNo(&novaRaiz);
                // gvl_printarNo(&noRight);

                return BTREE_NAO_POSSUI_PROMO;
            }
        }

        return BTREE_NAO_POSSUI_PROMO;
    }

    int gvl_inserirChaveArvoreB(Arquivo* bin, HeaderArvoreB* hbt, int valor, long offset){
        if(bin == NULL || hbt == NULL)
            return 1;
        
        Chave key;
        key.val = valor;
        key.ptr = offset;

        if( _gvl_inserirChaveRaiz(bin, hbt, key) == BTREE_ERROR)
            return 1;

        return 0;
    }

    int _gvl_buscarChaveArvoreB(Arquivo* bin, HeaderArvoreB* hbt, int valor, long* offset, int indexPagina, int nivel){
        
        NoArvoreB noAtual;
        Chave     resultado;
        int       filhoChamado;
        gvl_lerNoArvoreB(bin, hbt, &noAtual, indexPagina);

        if(gvl_buscarChave(&noAtual, valor, &resultado )){
            (*offset) = resultado.ptr;
            return nivel;
        }

        if(noAtual.ehFolha == '1'){
            return BTREE_ERROR;
        } 

        gvl_buscarPonteiro(&noAtual, valor, &filhoChamado);
        return _gvl_buscarChaveArvoreB(bin, hbt, valor, offset, filhoChamado, nivel+1);
    }


    int gvl_buscarChaveArvoreB(Arquivo* bin, HeaderArvoreB* hbt, int valor, long* offset){
        if(bin == NULL || bin->fp == NULL || hbt == NULL || hbt->raiz == -1)
            return BTREE_ERROR;

        return _gvl_buscarChaveArvoreB(bin, hbt, valor, offset, hbt->raiz, 1);
    }


