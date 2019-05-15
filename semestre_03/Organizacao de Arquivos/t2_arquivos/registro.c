#include "registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/** Manipulação de Registros de Cabeçalho
 */ 
    Header gvl_textoParaCabecalho(char* str, size_t size){
        Header h;
        memset(&h, GVL_LIXO_MEM, sizeof(Header));

        // Divide da linha de str pelo delimitador/vírgulas
        // Carrega as tags e descrições com os dados.
        char     c[5] = {'i', 's', 't', 'n', 'c'};
        char*  des[5] = { h.desCampo1, h.desCampo2, h.desCampo3, h.desCampo4, h.desCampo5};  
        char*  tag[5] = { &(h.tagCampo1), &(h.tagCampo2), &(h.tagCampo3), &(h.tagCampo4), &(h.tagCampo5)};

        char* ptr = strtok(str, ",");
        for(int i = 0; i < 5; i++){
            if(ptr == NULL) break;
            *tag[i] = c[i];
            strcpy(des[i], ptr);
            ptr = strtok(NULL, ",");
        }

        // Lidando com \r\n do windows
        int cargoLen = strlen(h.desCampo5);
        for(int i = cargoLen; i >= 0; i--){
            if( 'a' <= h.desCampo5[i] && h.desCampo5[i] <= 'z') break;
            if( 'A' <= h.desCampo5[i] && h.desCampo5[i] <= 'Z') break;
            if( ' ' == h.desCampo5[i]) break;

            h.desCampo5[i] = GVL_LIXO_MEM;
            cargoLen--;
        }
        h.desCampo5[++cargoLen] = '\0';

        // Inserindo os dados de controle do cabeçalho
        h.status    =  '1';
        h.topoLista = -1;

        return h;
    }

    int gvl_escreverCabecalho(Arquivo* bin, Header* h){
        if(bin == NULL || h == NULL)
            return 1;

        char*  des[5] = { h->desCampo1, h->desCampo2, h->desCampo3, h->desCampo4, h->desCampo5};  
        char*  tag[5] = { &(h->tagCampo1), &(h->tagCampo2), &(h->tagCampo3), &(h->tagCampo4), &(h->tagCampo5)};

        // printf("%d\n\n", gvl_escreverArquivo(bin, &(h->status), sizeof(char)));
        gvl_seek(bin, 0, SEEK_SET);
        gvl_escreverArquivo(bin, &(h->status),    sizeof(char));
        gvl_escreverArquivo(bin, &(h->topoLista), sizeof(long));
        
        for(int i = 0; i < 5; i++){
            gvl_escreverArquivo(bin, tag[i], sizeof(char));
            gvl_escreverArquivo(bin, des[i], sizeof(char)*40);
        }

        return 0;
    }

    Header gvl_carregarCabecalho(Arquivo* bin){
        Header h;
        memset(&h, GVL_LIXO_MEM, sizeof(h));

        if(bin == NULL || bin->fp == NULL)
            return h;

        // Lendo o cabeçalho na primeira página de disco.
        gvl_seek(bin, 0, SEEK_SET);

        gvl_lerArquivo(bin, &(h.status), sizeof(char));
        gvl_lerArquivo(bin, &(h.topoLista), sizeof(long));

        char*  des[5] = { h.desCampo1, h.desCampo2, h.desCampo3, h.desCampo4, h.desCampo5};  
        char*  tag[5] = { &(h.tagCampo1), &(h.tagCampo2), &(h.tagCampo3), &(h.tagCampo4), &(h.tagCampo5)};

        for(int i = 0; i < 5; i++){
            gvl_lerArquivo(bin, tag[i], sizeof(char));
            gvl_lerArquivo(bin, des[i], sizeof(char)*40);
        }

        gvl_seek(bin, GVL_TAM_PAGINA, SEEK_SET);
        return h;
    }

    int gvl_setStatusCabecalho(Arquivo* bin, Header* h, char flag){
        if(bin == NULL || bin->fp == NULL || h == NULL)
            return 1;


        long auxPtr = bin->posicaoPtr;
        
        gvl_seek(bin, 0, SEEK_SET);
        if(gvl_escreverArquivo(bin, &flag, sizeof(char))) return 1;
        gvl_flushBuffer(bin);
        gvl_seek(bin, auxPtr, SEEK_SET);

        h->status = flag;
        return 0;
    }

/** Manipulação de Registros de Dados
 */
    Registro gvl_textoParaRegistro(char* str, size_t size){
        
        Registro r;
        memset(&r, GVL_LIXO_MEM, sizeof(Registro));

        // Realizando o split da linha 
        char* vet[5];
        gvl_explode(str, ',', vet);

        if(vet[0] != NULL)  
            r.idServidor = atoi(vet[0]);
        else 
            r.idServidor = -1;

        if(vet[1] != NULL)
            r.salarioServidor = atof(vet[1]);
        else 
            r.salarioServidor = -1;
        
        if(vet[2] != NULL)
            strcpy(r.telefoneServidor, vet[2]);
        else
            r.telefoneServidor[0] = '\0';
        
        for(int i = 0; i < 3; i++) 
            if(vet[i] != NULL) free(vet[i]);

        r.nomeServidor  = vet[3];
        r.cargoServidor = vet[4];

        r.removido = '-';
        r.encadeamentoLista = -1;
        
        // EncadeamentoLista (8 bytes) + idServidor (4 bytes) + salarioServidor (8  bytes) + telefoneServidor  (14  bytes) 
        r.tamanhoRegistro = 8 + 4 + 8 + 14;
        // Indicador de tamanho do campo (4 bytes) + tagCampo4 (1 byte) + nomeServidor (tamanho variável, incluindo o '\0') 
        
        if(r.nomeServidor != NULL)
            r.tamanhoRegistro += 4 + 1 + strlen(r.nomeServidor) + 1;
        
        if(r.cargoServidor != NULL)
            r.tamanhoRegistro += 4 + 1 + strlen(r.cargoServidor) + 1;
    
        return r;
    }

    int gvl_escreverRegistro(Arquivo* bin, Header* h, Registro* r){
        if(bin == NULL || r == NULL || h == NULL)
            return 1;
        
        // Inserindo dados de tamanho fixo
        gvl_escreverArquivo(bin, &(r->removido),          sizeof(char));

        gvl_escreverArquivo(bin, &(r->tamanhoRegistro),   sizeof(int));
        gvl_escreverArquivo(bin, &(r->encadeamentoLista), sizeof(long));
        gvl_escreverArquivo(bin, &(r->idServidor),        sizeof(int));
        gvl_escreverArquivo(bin, &(r->salarioServidor),   sizeof(double));
        gvl_escreverArquivo(bin, &(r->telefoneServidor),  sizeof(char)*14);

        // Inserindo dados de tamanho variável
        if(r->nomeServidor != NULL){
            int nomeLen = strlen(r->nomeServidor) + 2;
            gvl_escreverArquivo(bin, &nomeLen,          sizeof(int));
            gvl_escreverArquivo(bin, &(h->tagCampo4),   sizeof(char));
            gvl_escreverArquivo(bin, r->nomeServidor,   sizeof(char) * (nomeLen - 1));
        }

        if(r->cargoServidor != NULL){
            int cargoLen = strlen(r->cargoServidor) + 2;
            gvl_escreverArquivo(bin, &cargoLen,          sizeof(int));
            gvl_escreverArquivo(bin, &(h->tagCampo5),    sizeof(char));
            gvl_escreverArquivo(bin, r->cargoServidor,   sizeof(char) * (cargoLen - 1));
        }

        // Caso seja um arquivo de fim de página, faz o fill com lixo e memória
        char lixoMem = GVL_LIXO_MEM;
        int qtdLixo  = r->tamanhoRegistro - 34;
        qtdLixo     -= (r->nomeServidor ==  NULL) ? 0 : 6 + strlen(r->nomeServidor);
        qtdLixo     -= (r->cargoServidor == NULL) ? 0 : 6 + strlen(r->cargoServidor);

        if(qtdLixo != 0)
            // printf("%d possui %d lixo\n", r->idServidor, qtdLixo);

        for(int i = 0; i < qtdLixo; i++){
            gvl_escreverArquivo(bin, &lixoMem, sizeof(char));
        }

        return 0;
    }

    Registro gvl_carregarRegistro(Arquivo* bin){
        Registro r;
        memset(&r, GVL_LIXO_MEM, sizeof(Registro));
        r.nomeServidor = r.cargoServidor = NULL;

        if(bin == NULL || bin->fp == NULL)
            return r;

        // Lendo dados de tamanho fixo00
        if(gvl_lerArquivo(bin, &(r.removido), sizeof(char)))
            return r;
        if(gvl_lerArquivo(bin, &(r.tamanhoRegistro), sizeof(int)))
            return r;
        if(gvl_lerArquivo(bin, &(r.encadeamentoLista), sizeof(long)))
            return r;
        if(gvl_lerArquivo(bin, &(r.idServidor), sizeof(int)))
            return r;
        if(gvl_lerArquivo(bin, &(r.salarioServidor), sizeof(double)))
            return r;
        if(gvl_lerArquivo(bin, &(r.telefoneServidor), sizeof(char)*14))
            return r;
        
        if(r.telefoneServidor[0] != '\0') r.telefoneServidor[14] = '\0';

        // Se bytesRestantes > 0 então possui campos variáveis.
        int bytesRestantes = r.tamanhoRegistro - 34;

        
        while(bytesRestantes){
            char tag, byte;
            int  lenght;

            // Verificando se eh um dado ou apenas fill de dados vazio no fim da página
            gvl_lerArquivo(bin, &byte, sizeof(char));
            if(byte == GVL_LIXO_MEM){
                gvl_seek(bin, bytesRestantes-1, SEEK_CUR);
                break;
            } else
                gvl_seek(bin, -1, SEEK_CUR); // volta ptr 1 byte pra tras
            

            bytesRestantes -= (sizeof(char) + sizeof(int));
            if( gvl_lerArquivo(bin, &lenght, sizeof(int)) || gvl_lerArquivo(bin, &tag, sizeof(char)))
                return r;
                
            char* valor = malloc((lenght-1)*sizeof(char));

            bytesRestantes -= (lenght - 1);
            gvl_lerArquivo(bin, valor, (lenght-1)*sizeof(char));

            if(tag == 'n' && r.nomeServidor == NULL)
                r.nomeServidor = valor;
            else if(tag == 'c' && r.cargoServidor == NULL)
                r.cargoServidor = valor;
            else
                free(valor);
        }

        return r;
    }

    Registro gvl_alterarRegistro(Registro* r, char tagCampo, char* valor){
        Registro nr = *r; // nr novo registro
        int novoTamanho;

        if(r->nomeServidor != NULL){
            nr.nomeServidor = malloc(strlen(r->nomeServidor)+1);
            strcpy(nr.nomeServidor, r->nomeServidor);
        }

        if(r->cargoServidor != NULL){
            nr.cargoServidor = malloc(strlen(r->cargoServidor)+1);
            strcpy(nr.cargoServidor, r->cargoServidor);
        }

        if(strcmp(valor, "NULO") == 0){
            switch (tagCampo){
                case 'i':
                    nr.idServidor = -1;
                    break;
                case 's':
                    nr.salarioServidor = -1;
                    break;
                case 't':
                    memset(&nr.telefoneServidor, GVL_LIXO_MEM, 15*sizeof(char));
                    nr.telefoneServidor[0] = '\0';
                    break;
                case 'n':
                    nr.nomeServidor = NULL;
                    break;
                case 'c':
                    nr.cargoServidor = NULL;
                    break;
            }

        } else {
            switch (tagCampo){
                case 'i':
                    sscanf(valor, "%d", &nr.idServidor);
                    break;
                case 's':
                    sscanf(valor, "%lf", &nr.salarioServidor);
                    break;
                case 't':
                    strcpy(nr.telefoneServidor, valor);
                    break;
                case 'n':
                    nr.nomeServidor = malloc(strlen(valor)*sizeof(char));
                    strcpy(nr.nomeServidor, valor);
                    break;
                case 'c':
                    nr.cargoServidor = malloc(strlen(valor)*sizeof(char));
                    strcpy(nr.cargoServidor, valor);
                    break;
            }
        }

        novoTamanho = 34;
        novoTamanho += (nr.nomeServidor  != NULL) ? strlen(nr.nomeServidor) + 6 : 0;
        novoTamanho += (nr.cargoServidor != NULL) ? strlen(nr.cargoServidor) + 6 : 0;

        if(novoTamanho > nr.tamanhoRegistro)
            nr.tamanhoRegistro = novoTamanho;

        return nr;
    }

    int gvl_inserirNovoRegistro(Arquivo* bin, Header* h, Registro* r){
        if(bin == NULL || bin->fp == NULL || r == NULL || h == NULL)
            return 1;
        
        // Carregando a lista de removidos
        if(tamListaRemovidos == 0 && h->topoLista != -1)
            gvl_carregarListaRemovidos(bin, h);

        gvl_seek(bin, 0, SEEK_END);
        long posicaoInsercao = bin->posicaoPtr;

        // veriricando se pode aproveitar o espaço de algum registro removido
        if(tamListaRemovidos > 0){
            for(int i = 0; i < tamListaRemovidos; i++){
                
                // Esse espaço já foi utilizado por outra inserção
                if(listaRemovidos[i].tamanhoRegistro == -1)
                    continue;
                
                // Best-fit: primeiro registro que consegue conter o novo registro
                if(r->tamanhoRegistro <= listaRemovidos[i].tamanhoRegistro){
                    posicaoInsercao    = listaRemovidos[i].filePos;
                    r->tamanhoRegistro = listaRemovidos[i].tamanhoRegistro;

                    listaRemovidos[i].tamanhoRegistro = -1; // Remove da lista de removidos
                    break;
                }
            }
        }

        // printf("Escrevendo na posicao... %ld\n", posicaoInsercao);
        gvl_seek(bin, posicaoInsercao, SEEK_SET);
        gvl_escreverRegistro(bin, h, r);

        return 0;
    }

    void gvl_destruirRegistro(Registro* r){
        if(r == NULL) return;
        if(r->nomeServidor != NULL){
            free(r->nomeServidor);
            r->nomeServidor = NULL;
        }
        if(r->cargoServidor != NULL){
            free(r->cargoServidor);
            r->cargoServidor = NULL;
        }
    }
    
    int gvl_comparaId(Registro* r, char* valor){
        if(r == NULL || valor == NULL) return 0;  
        if(r->idServidor == atoi(valor)) return 1;
        return 0;
    }

    int gvl_comparaNome(Registro* r, char* valor){
        if(r == NULL || valor == NULL || r->nomeServidor == NULL) return 0;
        if(strcmp(r->nomeServidor, valor) == 0) return 1;
        return 0;
    }

    int gvl_comparaCargo(Registro* r, char* valor){
        if(r == NULL || valor == NULL || r->cargoServidor == NULL) return 0;
        if(strcmp(r->cargoServidor, valor) == 0) return 1;
        return 0;
    }

    int gvl_comparaTelefone(Registro* r, char* valor){
        if(r == NULL || valor == NULL || strlen(r->telefoneServidor) != 14) return 0;  
        if(strcmp(r->telefoneServidor, valor) == 0) return 1;
        return 0;
    }

    int gvl_comparaSalario(Registro* r, char* valor){
        if(r == NULL || valor == NULL || r->salarioServidor == -1) return 0;
        if(r->salarioServidor == atof(valor)) return 1;
        return 0;
    }

    int gvl_comparaCampo(Registro* r, char tagCampo, char *valor){
        // Fazendo a busca e verificando se o registro possui o dado desejado
        if(tagCampo == 'i')     return gvl_comparaId(r, valor);
        else if(tagCampo == 'n') return gvl_comparaNome(r, valor);
        else if(tagCampo == 'c') return gvl_comparaCargo(r, valor);
        else if(tagCampo == 's') return gvl_comparaSalario(r, valor);
        else if(tagCampo == 't') return gvl_comparaTelefone(r, valor);
        else return 0;
    }

    int gvl_ehCampoNulo(Registro* r, char tagCampo){
        // Fazendo a busca e verificando se o campo desejado é nulo
        if(tagCampo == 'i') 
            return (r->idServidor == -1) ? 1 : 0;
        else if(tagCampo == 'n') 
            return (r->nomeServidor == NULL) ? 1 : 0;
        else if(tagCampo == 'c') 
            return (r->cargoServidor == NULL) ? 1 : 0;
        else if(tagCampo == 's') 
            return (r->salarioServidor == -1) ? 1 : 0;
        else if(tagCampo == 't') 
            return (strlen(r->telefoneServidor) != 14) ? 1 : 0;
        else 
            return 0;
    }

/** Manipulação de registros em lotes
 * 
 */
    int gvl_gerarBinFromCSV(Arquivo* csv, Arquivo* bin){
        Header      head;
        Registro    regAtual, regAnterior;
        size_t      tamLinha = 2048;
        char        strLinha[tamLinha];

        /**
         * Lendo a primeira linha do CSV que corresponde ao cabeçalho.
         * Os dados do cabeçalho devem ocupar a primeira página do disco.
         */ 
            memset(strLinha, GVL_LIXO_MEM, tamLinha);
            if(gvl_lerLinha(csv, strLinha, tamLinha))
                return 1; // Erro na leitura.

            head = gvl_textoParaCabecalho(strLinha, tamLinha);
            if(head.status == GVL_LIXO_MEM)
                return 1;  // Erro ao gerar cabeçalho.
            
            gvl_escreverCabecalho(bin, &head);
            // dando o fill na página de cabeçalho.
            bin->bf.tamanhoPagina[0] = GVL_TAM_PAGINA;

        /**
         * Agora iremos iterar por todo o CSV de tal forma que cada linha
         * irá representar um novo registro.
         * Os registros de dados começam da segunda pagina em diante.
         */    
            gvl_seek(bin, GVL_TAM_PAGINA, SEEK_SET);

            gvl_lerLinha(csv, strLinha, tamLinha);
            regAnterior = gvl_textoParaRegistro(strLinha, tamLinha);

            int  cont = 1, max = 5;
            while( (!gvl_lerLinha(csv, strLinha, tamLinha))){
                
                if(strLinha[0] == GVL_LIXO_MEM ) 
                    break;

                //printf("Lendo registro nº %d\n", cont++);
                //printf("tamLinha: %ld\n", strlen(strLinha));
                //printf("linha: %s\n\n", strLinha);
                regAtual = gvl_textoParaRegistro(strLinha, tamLinha);
                
                /**
                 *  Se houver espaço suficiente na página de disco para salvar o registro
                 *  anterior + registro atual, então salva o anterior e prossegue.
                 *  Senão, faz o anterior ocupar até o restante da página de disco. 
                 */
                long paginaRestante = GVL_TAM_PAGINA - (bin->posicaoPtr % GVL_TAM_PAGINA);
                
                long tamRegistroAnterior = regAnterior.tamanhoRegistro + 5;
                long tamRegistroAtual    = regAtual.tamanhoRegistro + 5;
                long somaRegistros       = tamRegistroAnterior + tamRegistroAtual;

                if(paginaRestante < somaRegistros){
                    //printf("ptr atual %ld, qtd restate: %ld \n", bin->posicaoPtr, paginaRestante - regAnterior.tamanhoRegistro + 5);
                    //printf("%s tamanho: $ld\n", regAnterior->nomeServidor, regAnterior.tamanhoRegistro + 5);
                    regAnterior.tamanhoRegistro += paginaRestante - tamRegistroAnterior;
                }
                    

                gvl_escreverRegistro(bin, &head, &regAnterior);
                
                if(regAnterior.cargoServidor != NULL) free(regAnterior.cargoServidor);
                if(regAnterior.nomeServidor != NULL)  free(regAnterior.nomeServidor);
                    
                regAnterior = regAtual;
            }

            gvl_escreverRegistro(bin, &head, &regAnterior);
    }

    int gvl_listarRegistros(Arquivo* bin){
        if(bin == NULL || bin->fp == NULL)
            return 0;

        Registro aux;
        int qtdRegistros = 0;

        // Aponando para o primeiro registro de dados
        gvl_seek(bin, GVL_TAM_PAGINA, SEEK_SET);

        do{ 
            aux = gvl_carregarRegistro(bin);
            
            if(aux.removido == GVL_LIXO_MEM){
                gvl_destruirRegistro(&aux);
                break;
            }

            if(aux.removido == '*'){
                gvl_destruirRegistro(&aux);
                continue;
            }

            // printf("Registro nº %d: \n", qtdRegistros+1);
            printf("%d", aux.idServidor);
            if(aux.salarioServidor != -1)   printf(" %.2lf", aux.salarioServidor);
            else                            printf("         ");
            if(aux.telefoneServidor[0] != '\0') printf(" %14s", aux.telefoneServidor);
            else                                printf("               ");
            if(aux.nomeServidor  != NULL)    printf(" %ld %s", strlen(aux.nomeServidor), aux.nomeServidor);
            if(aux.cargoServidor != NULL)   printf(" %ld %s", strlen(aux.cargoServidor), aux.cargoServidor);
            printf("\n");

            gvl_destruirRegistro(&aux);
            qtdRegistros++;

        } while(1);

        if(qtdRegistros == 0)
            printf("Registro inexistente.\n");

        return qtdRegistros;
    }

    int gvl_buscarRegistros(Arquivo* bin, Header* h, char tagCampo, char* valor, int onlyFirst){
        if(bin == NULL || bin->fp == NULL)
            return 0;

        // Verificando se o campo de busca é valido.
        if( tagCampo != h->tagCampo1 && tagCampo != h->tagCampo2 && tagCampo != h->tagCampo3
            && tagCampo != h->tagCampo4 && tagCampo != h->tagCampo5)
            return 0;

        Registro aux;
        int qtdRegistros = 0;

        // Aponando para o primeiro registro de dados
        gvl_seek(bin, GVL_TAM_PAGINA, SEEK_SET);

        do{ 
            aux = gvl_carregarRegistro(bin);
            
            // Caso não haja mais arquivos para ler ou o atual tenha sido removido.
            if(aux.removido == '*') {
                gvl_destruirRegistro(&aux);
                continue;
            }

            if(aux.removido == GVL_LIXO_MEM) {
                gvl_destruirRegistro(&aux);
                break;
            }

            // Verificando se o campo buscado existe no dado
            if(!gvl_comparaCampo(&aux, tagCampo, valor)){
                gvl_destruirRegistro(&aux);
                continue;
            }

            // printf("Registro nº %d: \n", qtdRegistros+1);
            printf("%s: %d\n", h->desCampo1, aux.idServidor);
            
            if(aux.salarioServidor != -1)   printf("%s: %.2lf\n", h->desCampo2, aux.salarioServidor);
            else                            printf("%s: valor nao declarado\n", h->desCampo2);
            
            if(aux.telefoneServidor[0] != '\0') printf("%s: %14s\n", h->desCampo3, aux.telefoneServidor);
            else                                printf("%s: valor nao declarado\n", h->desCampo3);
            
            if(aux.nomeServidor  != NULL)   printf("%s: %s\n", h->desCampo4, aux.nomeServidor);
            else                            printf("%s: valor nao declarado\n", h->desCampo4); 
            
            if(aux.cargoServidor  != NULL)  printf("%s: %s\n", h->desCampo5, aux.cargoServidor);
            else                            printf("%s: valor nao declarado\n", h->desCampo5); 
            
            printf("\n");

            gvl_destruirRegistro(&aux);
            qtdRegistros++;

            if(onlyFirst) break;

        } while(1);

        if(qtdRegistros == 0)
            printf("Registro inexistente.\n");

        return qtdRegistros;
    }

    int gvl_removerRegistros(Arquivo* bin, Header* h, char tagCampo, char* valor, int onlyFirst){
        if(bin == NULL || bin->fp == NULL)
            return 0;

        // Verificando se o campo de busca é valido.
        if( tagCampo != h->tagCampo1 && tagCampo != h->tagCampo2 && tagCampo != h->tagCampo3
            && tagCampo != h->tagCampo4 && tagCampo != h->tagCampo5)
            return 0;

        // Verificando se a lista de removidos já foi carregada
        if(h->topoLista != -1 && tamListaRemovidos == 0)
            gvl_carregarListaRemovidos(bin, h);

        Registro aux;
        int qtdRegistros     = 0;
        long posicaoRegistro = 0;

        // Apontando para o primeiro registro de dados
        gvl_seek(bin, GVL_TAM_PAGINA, SEEK_SET);

        do{ 
            posicaoRegistro = bin->posicaoPtr;
            aux             = gvl_carregarRegistro(bin);
            
            // Esse registro já foi removido
            if(aux.removido == '*') {
                gvl_destruirRegistro(&aux);
                continue;
            }

            // Não há mais registros para ler
            if(aux.removido == GVL_LIXO_MEM) {
                gvl_destruirRegistro(&aux);
                break;
            }

            // Se a busca for por campo nulo e o campo existe
            if(strcmp(valor, "NULO") == 0){
                
                if(!gvl_ehCampoNulo(&aux, tagCampo)){
                    gvl_destruirRegistro(&aux);
                    continue;
                }
                
            // Verificando se o campo buscado existe no dado
            } else if(!gvl_comparaCampo(&aux, tagCampo, valor)){
                gvl_destruirRegistro(&aux);
                continue;
            }

            // O registro foi encontrado, então precisamos removê-lo
            Registro r;
            memset(&r, GVL_LIXO_MEM, sizeof(Registro));
            r.removido = '*';
            r.encadeamentoLista = -1; // TODO
            r.tamanhoRegistro   = aux.tamanhoRegistro;
            r.nomeServidor      = r.cargoServidor = NULL;

            // Escrevendo o registro que foi removido logicamente
            gvl_seek(bin, posicaoRegistro, SEEK_SET);
            gvl_escreverRegistro(bin, h, &r);

            // Inserindo o elemento na lista de removidos
            gvl_inserirNovoRemovido(bin, h, &r, posicaoRegistro, 1);

            // Removendo registro alocado e contando qtd de registros removidos
            gvl_destruirRegistro(&aux);
            qtdRegistros++;

            if(onlyFirst) break;

        } while(1);

        return qtdRegistros;
    }

    int gvl_atualizarRegistros(Arquivo* bin, Header* h, char tagBusca, char* valorBusca, char tagAtualiza, char* valorAtualiza, int onlyFirst){
        if(bin == NULL || bin->fp == NULL)
            return 0;

        // Verificando se a lista de removidos já foi carregada
        if(h->topoLista != -1 && tamListaRemovidos == 0)
            gvl_carregarListaRemovidos(bin, h);

        Registro aux;
        int  qtdRegistros     = 0;
        long posicaoRegistro = 0;

        // Apontando para o primeiro registro de dados
        gvl_seek(bin, GVL_TAM_PAGINA, SEEK_SET);

        do{ 
            posicaoRegistro = bin->posicaoPtr;
            aux             = gvl_carregarRegistro(bin);

            // Esse registro já foi removido
            if(aux.removido == '*') {
                gvl_destruirRegistro(&aux);
                continue;
            }

            // Não há mais registros para ler
            if(aux.removido == GVL_LIXO_MEM) {
                gvl_destruirRegistro(&aux);
                break;
            }

            // Se a busca for por campo nulo e o campo existe
            if(strcmp(valorBusca, "NULO") == 0){
                
                if(!gvl_ehCampoNulo(&aux, tagBusca)){
                    gvl_destruirRegistro(&aux);
                    continue;
                }
                
            // Verificando se o campo buscado existe no dado
            } else if(!gvl_comparaCampo(&aux, tagBusca, valorBusca)){
                gvl_destruirRegistro(&aux);
                continue;
            }

            // Verificando se o valor para atualizar já não é igual ao que deveria
            if(gvl_comparaCampo(&aux, tagAtualiza, valorAtualiza)){
                gvl_destruirRegistro(&aux);
                continue;
            }

            // Achamos o registro agora precisamos reescrevê-lo
            Registro regNovo = gvl_alterarRegistro(&aux, tagAtualiza, valorAtualiza);

            // Caso a modificação não tenha alterado o tamanho do registro basta reescrevê-lo
            if(regNovo.tamanhoRegistro == aux.tamanhoRegistro){
                gvl_seek(bin, posicaoRegistro, SEEK_SET);
                gvl_escreverRegistro(bin, h,   &regNovo);

            // Caso não caiba, precisa apagar o registro atual e em seguida inserir o novo registro
            } else {
                long auxPos = bin->posicaoPtr;
                gvl_inserirNovoRegistro(bin, h, &regNovo);
                gvl_inserirNovoRemovido(bin, h, &aux, posicaoRegistro, 1);
                gvl_ordenarRegistrosRemovidos(bin, h, 0, tamListaRemovidos-1);
                gvl_seek(bin, auxPos, SEEK_SET);
            }

            gvl_destruirRegistro(&aux);
            gvl_destruirRegistro(&regNovo);
            qtdRegistros++;      

            if(onlyFirst) break;

        } while(1);

        return qtdRegistros;
    }

/** Manipulação da lista de registros removidos
 */

    void gvl_carregarListaRemovidos(Arquivo* bin, Header* h){
        if(bin == NULL || bin->fp == NULL || h == NULL)
            return;
        
        // printf("Carregando lista...\n");

        listaRemovidos      = NULL;
        tamListaRemovidos   = 0;

        // Nao há nenhum elemento removido
        if(h->topoLista == -1)
            return;

        // Aponando para o primeiro registro removido
        Registro aux;
        long posicaoRegistro = 0;
        gvl_seek(bin, h->topoLista, SEEK_SET);

        do{ 
            posicaoRegistro = bin->posicaoPtr;
            aux             = gvl_carregarRegistro(bin);
            
            // Não há mais registros para ler
            if(aux.removido == GVL_LIXO_MEM) {
                gvl_destruirRegistro(&aux);
                break;
            }

            // Caso o registro não tenha sido removido
            if(aux.removido != '*') {
                gvl_destruirRegistro(&aux);
                continue;
            }
            
            gvl_inserirNovoRemovido(bin, h, &aux, posicaoRegistro, 0);

            posicaoRegistro = aux.encadeamentoLista;

            gvl_destruirRegistro(&aux);

            if(posicaoRegistro == -1)
                break;
            
            gvl_seek(bin, posicaoRegistro, SEEK_SET);

        } while(1);
    }

    void gvl_limparListaRemovidos(Arquivo* bin, Header* h){
        if(listaRemovidos != NULL)
            free(listaRemovidos);
        listaRemovidos    = NULL;
        tamListaRemovidos = 0;
    }

    void gvl_inserirNovoRemovido(Arquivo* bin, Header* h, Registro* r, long ptrPos, int getTime){
        
        tamListaRemovidos += 1;
        if(tamListaRemovidos == 0)
            listaRemovidos = malloc(1*sizeof(RegRemovido));
        else 
            listaRemovidos = realloc(listaRemovidos, (tamListaRemovidos) * sizeof(RegRemovido));
        
        listaRemovidos[tamListaRemovidos-1].filePos = ptrPos;
        listaRemovidos[tamListaRemovidos-1].tamanhoRegistro = r->tamanhoRegistro;
        listaRemovidos[tamListaRemovidos-1].tempoRemocao = (getTime) ? ++tempoRemovidos : -tamListaRemovidos;
    }
    
    void _gvl_mergeRegistrosRemovidos(int l, int m, int r){
        int i, j, k;
        int tamLeft  = m - l + 1;
        int tamRight = r - m;

        // Arrays temporários
        RegRemovido L[tamLeft], R[tamRight];

        // Copiando os arrays
        for(i = 0; i < tamLeft; i++)
            L[i] = listaRemovidos[l+i];
        for(j = 0; j < tamRight; j++)
            R[j] = listaRemovidos[m+1+j];

        // Fazendo o merge dos dois arrays
        i = j = 0;
        k = l;
        while(i < tamLeft && j < tamRight){
            if(L[i].tamanhoRegistro < R[j].tamanhoRegistro){
                listaRemovidos[k++] = L[i++];
            
            } else if(L[i].tamanhoRegistro > R[j].tamanhoRegistro) {
                listaRemovidos[k++] = R[j++];
            
            } else {
                if(L[i].tempoRemocao >= R[j].tempoRemocao)
                    listaRemovidos[k++] = L[i++];
                else
                    listaRemovidos[k++] = R[j++];
            }
        }

        while(i < tamLeft)
            listaRemovidos[k++] = L[i++];
        
        while(j < tamRight)
            listaRemovidos[k++] = R[j++];
    }

    void gvl_ordenarRegistrosRemovidos(Arquivo* bin, Header* h, int l, int r){
        if(bin == NULL  || bin->fp == NULL || h == NULL || listaRemovidos == NULL || tamListaRemovidos == 0)
            return;

        // printf("Merge: [%d, %d]\n", l, r);

        if(l < r){
            int m = (l+r)/2;

            gvl_ordenarRegistrosRemovidos(bin, h, l,   m);
            gvl_ordenarRegistrosRemovidos(bin, h, m+1, r);
            
            _gvl_mergeRegistrosRemovidos(l, m, r);
        }
    }

    void gvl_escreverRegistroRemovidos(Arquivo* bin, Header* h){
        if(bin == NULL  || bin->fp == NULL || h == NULL || listaRemovidos == NULL || tamListaRemovidos == 0)
            return;

        int      indexIni = 0;
        Registro aux;

        memset(&aux, GVL_LIXO_MEM, sizeof(Registro));
        aux.removido = '*';
        aux.nomeServidor = aux.cargoServidor = NULL;

        // Atualizando a lista de removidos no disco
        for(int i = 0; i < tamListaRemovidos; i++){
            // Ignorando os removidos que foram preenchidos
            if(listaRemovidos[i].tamanhoRegistro == -1){
                indexIni = i+1;
                continue;
            }

            aux.tamanhoRegistro   = listaRemovidos[i].tamanhoRegistro;
            aux.encadeamentoLista = (i+1 < tamListaRemovidos) ? listaRemovidos[i+1].filePos : -1; 

            gvl_seek(bin, listaRemovidos[i].filePos, SEEK_SET);
            gvl_escreverRegistro(bin, h, &aux);
        }

        // Atualizando o topo da lista no cabeçalho
        h->topoLista = (indexIni < tamListaRemovidos) ? listaRemovidos[indexIni].filePos : -1;
        gvl_escreverCabecalho(bin, h);
        
    }

    void gvl_exibirListaRemovidos(Arquivo* bin, Header* h){
        if(bin == NULL  || bin->fp == NULL || h == NULL || listaRemovidos == NULL || tamListaRemovidos == 0)
            return;

        for(int i = 0; i < tamListaRemovidos; i++)
            // printf("[%d] Posicao: %ld\t\tTamanho: %d\n", i+1, listaRemovidos[i].filePos, listaRemovidos[i].tamanhoRegistro);
            printf("[%d] Posicao: %ld\t\tTamanho: %d\t\tTempo: %d\n", i+1, listaRemovidos[i].filePos, listaRemovidos[i].tamanhoRegistro, listaRemovidos[i].tempoRemocao);
    }

/** Funções auxiliares para manipulação dos dados
 */
    void gvl_explode(char* str, char delimiter, char* vet[5]){

        int   ini = 0, end = 0, i = 0;
        
        for(int i = 0; i < 5; i++){
            //while(str[end] != '\0' && str[end] != '\n' && str[end] != '\r' &&  str[end] != delimiter)
            while(isprint(str[end]) && str[end] != delimiter)
                end++;

            int len = end-ini;
            
            if(len > 0){
                vet[i]   = malloc((len+1) * sizeof(char));
                str[end] = '\0';
                strcpy(vet[i], str+ini);
                str[end] = delimiter;
            } else{
                vet[i] = NULL;
            }
            
            ini = end+1;
            end = end+1;
        }
    }
