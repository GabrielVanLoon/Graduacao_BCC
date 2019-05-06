/**
 * Trabalho de Organização de arquivos
 * Título: T1 - Geração e Leitura de Arquivos Binários
 * Autor:  Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
 * Prof.:  Dra. Cristina Dutra de Aguiar Ciferri
 * Data:   abril/2019
 * 
 * OBJETIVOS DO TRABALHO
 * Implementar as técnicas de organização de campos e registros
 * de dados vistos em aula, assim como explorar os conceitos de 
 * páginas de disco.
 * 
 * DESCRIÇÃO DO TRABALHO
 * O trabalho apresenta 3 funcionalidades distintitas que são 
 * selecionadas no início do programa. São elas:
 * 
 * 1 -  Ler os dados de um arquivo CSV e gerar um arquivo binário 
 *      que siga os princípios de armazenamento visto em aula.
 * 2 -  Ler o arquivo binário gerado e exibir na tela todos os dados.
 * 3 -  Realizar a busca de registros no arquivo binário por meio de
 *      algum dos campos do mesmo.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include "IOprocessor.h"
#include "registro.h"

/**
 * Protótipos de funções
 */
    char getTagCampo(const char* campoBusca);
    Registro lerNovoRegistro();

int main(void){
 
    Arquivo     bin, csv;
    Header      cabecalho;
    Registro    regAux;
    
    int     opcao;
    char    nomeArquivoCSV[64];
    char    nomeArquivoBin[64] = "arquivoTrab1.bin";

    int     qtdRegistros, qtdRemocoes, qtdInsercoes;
    char    campoBusca[64];
    char    valorBusca[64];



    // Lendo a opção do usuário
    scanf(" %d", &opcao);

    switch(opcao){

        // Ler arquivo CSV e gerar arquivo binário com registros.
        case 1:
            scanf(" %60s", nomeArquivoCSV);

            if(gvl_abrirArquivo(&csv, nomeArquivoCSV, "r")){
                printf("Falha no carregamento do arquivo.\n");
                break;
            }

            if(gvl_abrirArquivo(&bin, nomeArquivoBin, "w+")){
                printf("Falha no carregamento do arquivo.\n");
                break;
            }

            gvl_gerarBinFromCSV(&csv, &bin);

            gvl_fecharArquivo(&csv);
            gvl_fecharArquivo(&bin);
            
            printf("arquivoTrab1.bin");
            break;

        // Exibir todos os registros salvos no arquivo binário.
        case 2:
            scanf(" %60s", nomeArquivoBin);

            if(gvl_abrirArquivo(&bin, nomeArquivoBin, "r+")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho = gvl_carregarCabecalho(&bin);

            if(cabecalho.status != '1' || gvl_setStatusCabecalho(&bin, &cabecalho, '0')){
                printf("Falha no processamento do arquivo.\n");
                break;
            } 
            
            qtdRegistros = gvl_listarRegistros(&bin);

            if(qtdRegistros > 0)
                printf("Número de páginas de disco acessadas: %d", bin.bf.contadorAcessos);

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);

            break;

        // Buscar usuários por meio de algum dos campos do registro.
        case 3:

            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", campoBusca);
            scanf(" %60[^\n\r]s", valorBusca);

            if(gvl_abrirArquivo(&bin, nomeArquivoBin, "r+")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho = gvl_carregarCabecalho(&bin);

            if(cabecalho.status != '1' || gvl_setStatusCabecalho(&bin, &cabecalho, '0')){
                printf("Falha no processamento do arquivo.\n");
                break;
            } 
            
            int  onlyFirst = 0;
            char tagCampoBusca = getTagCampo(campoBusca);;

            if(tagCampoBusca == 'i') 
                onlyFirst = 1;

            qtdRegistros =  gvl_buscarRegistros(&bin, &cabecalho, tagCampoBusca, valorBusca, onlyFirst);

            if(qtdRegistros > 0)
                printf("Número de páginas de disco acessadas: %d", bin.bf.contadorAcessos);

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);

            break;

        // Remover um registro lógicamente do arquivo
        case 4:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %d",   &qtdRemocoes);

            if(gvl_abrirArquivo(&bin, nomeArquivoBin, "r+")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho = gvl_carregarCabecalho(&bin);

            if(cabecalho.status != '1' || gvl_setStatusCabecalho(&bin, &cabecalho, '0')){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            for(int i = 0; i < qtdRemocoes; i++){
                scanf(" %60s", campoBusca);
                tagCampoBusca = getTagCampo(campoBusca);
                char t;

                if(tagCampoBusca == 'n' || tagCampoBusca == 'c')
                    scanf(" %*c%60[^\n\r\"]%*c", valorBusca);
                else 
                    scanf(" %60[^\n\r]", valorBusca);

                onlyFirst = (tagCampoBusca == 'i') ? 1 : 0;

                int c = gvl_removerRegistros(&bin, &cabecalho, tagCampoBusca, valorBusca, onlyFirst);
                printf("Campo [%s] Tag[%c] Busca[%s] removeu %d\n", campoBusca, tagCampoBusca, valorBusca, c);
            }
            
            // Após realizar as exclusões precisa atualizar a lista de removidos
            gvl_ordenarRegistrosRemovidos(&bin, &cabecalho, 0, tamListaRemovidos-1);
            // gvl_exibirListaRemovidos(&bin, &cabecalho); 
            gvl_escreverRegistroRemovidos(&bin, &cabecalho);
            gvl_limparListaRemovidos(&bin, &cabecalho);        

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);

            break;
        
        // Inserindo novos registros
        case 5:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %d",   &qtdInsercoes);

            if(gvl_abrirArquivo(&bin, nomeArquivoBin, "r+")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho = gvl_carregarCabecalho(&bin);

            if(cabecalho.status != '1' || gvl_setStatusCabecalho(&bin, &cabecalho, '0')){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            for(int i = 0; i < qtdInsercoes; i++){
               regAux = lerNovoRegistro();
               gvl_inserirNovoRegistro(&bin, &cabecalho, &regAux);
               gvl_destruirRegistro(&regAux);
            }

            gvl_ordenarRegistrosRemovidos(&bin, &cabecalho, 0, tamListaRemovidos-1);
            // gvl_exibirListaRemovidos(&bin, &cabecalho); 
            gvl_escreverRegistroRemovidos(&bin, &cabecalho);
            gvl_limparListaRemovidos(&bin, &cabecalho);        

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');
            gvl_fecharArquivo(&bin);
            break;

        case 6:
            scanf(" %60s", nomeArquivoBin);

             if(gvl_abrirArquivo(&bin, nomeArquivoBin, "r+")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho = gvl_carregarCabecalho(&bin);

            if(cabecalho.status != '1' || gvl_setStatusCabecalho(&bin, &cabecalho, '0')){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            gvl_carregarListaRemovidos(&bin, &cabecalho);
            gvl_exibirListaRemovidos(&bin, &cabecalho);

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');
            gvl_fecharArquivo(&bin);

            break;

    }

    return 0;
}

char getTagCampo(const char* campoBusca){
    if(strcmp(campoBusca, "idServidor") == 0)            return 'i';
    else if(strcmp(campoBusca, "nomeServidor") == 0)     return 'n';
    else if(strcmp(campoBusca, "cargoServidor") == 0)    return 'c';
    else if(strcmp(campoBusca, "telefoneServidor") == 0) return 't';
    else if(strcmp(campoBusca, "salarioServidor") == 0)  return 's';
    return ' ';
}

Registro lerNovoRegistro(){
    char     valor[60], c;
    Registro r;
    
    memset(&r, GVL_LIXO_MEM, sizeof(Registro));
    r.removido          = '-';
    r.encadeamentoLista = -1;
    
    /**
     * Campos de tamanho fixo
     */
    scanf(" %d", &r.idServidor);

    scanf(" %60s", valor);
    if(strcmp(valor, "NULO") != 0)
        sscanf(valor, "%lf", &r.salarioServidor);
    else 
        r.salarioServidor = -1;

    scanf(" %60s", valor);
    if(strcmp(valor, "NULO") != 0)
        sscanf(valor, "%s", r.telefoneServidor);
    else 
        r.telefoneServidor[0] = '\0';

    /**
     * Campos de tamanho variavel
     */
    scanf(" %c", &c);
    if(c == 'N'){
        scanf(" %60s", valor);
        r.nomeServidor = NULL;
    } else {
        scanf(" %[^\"]%*c", valor);
        r.nomeServidor = malloc(strlen(valor)*sizeof(char));
        strcpy(r.nomeServidor, valor);
    }

    scanf(" %c", &c);
    if(c == 'N'){
        scanf(" %60s", valor);
        r.cargoServidor = NULL;
    } else {
        scanf(" %[^\"]%*c", valor);
        r.cargoServidor = malloc(strlen(valor)*sizeof(char));
        strcpy(r.cargoServidor, valor);
    }

    /**
     * Calculando o tamanho
     */
    
    r.tamanhoRegistro = 8 + 4 + 8 + 14;
    
    if(r.nomeServidor != NULL)
        r.tamanhoRegistro += 4 + 1 + strlen(r.nomeServidor) + 1;
        
    if(r.cargoServidor != NULL)
        r.tamanhoRegistro += 4 + 1 + strlen(r.cargoServidor) + 1;

    /**
     * Exibindo registro

    printf("%d", r.idServidor);
    if(r.salarioServidor != -1)   printf(" %.2lf", r.salarioServidor);
    else                            printf("         ");
    if(r.telefoneServidor[0] != '\0') printf(" %14s", r.telefoneServidor);
    else                                printf("               ");
    if(r.nomeServidor  != NULL)    printf(" %ld %s", strlen(r.nomeServidor), r.nomeServidor);
    if(r.cargoServidor != NULL)   printf(" %ld %s", strlen(r.cargoServidor), r.cargoServidor);
    printf("\n");
    */

    return r;
}