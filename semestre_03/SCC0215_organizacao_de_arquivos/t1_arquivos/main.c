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

int main(void){
 
    Arquivo     bin, csv;
    Header      cabecalho;
    Registro    regAux;
    
    int     opcao;
    char    nomeArquivoCSV[64];
    char    nomeArquivoBin[64] = "arquivoTrab1.bin";

    int     qtdRegistros;
    char    campoBusca[64];
    char    valorBusca[64];

    // Lendo a opção do usuário
    scanf(" %d", &opcao);

    switch(opcao){

        /** 
         * Ler arquivo CSV e gerar arquivo binário com registros.
         */
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
            char tagCampoBusca = '0';

            if(strcmp(campoBusca, "idServidor") == 0)           tagCampoBusca = 'i';
            else if(strcmp(campoBusca, "nomeServidor") == 0)    tagCampoBusca = 'n';
            else if(strcmp(campoBusca, "cargoServidor") == 0)   tagCampoBusca = 'c';
            else if(strcmp(campoBusca, "telefoneServidor") == 0) tagCampoBusca = 't';
            else if(strcmp(campoBusca, "salarioServidor") == 0) tagCampoBusca = 's';
            
            if(tagCampoBusca == 'i') onlyFirst = 1;

            qtdRegistros =  gvl_buscarRegistros(&bin, &cabecalho, tagCampoBusca, valorBusca, onlyFirst);

            if(qtdRegistros > 0)
                printf("Número de páginas de disco acessadas: %d", bin.bf.contadorAcessos);

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);

            break;
    }


    return 0;
}



/**
Arquivo arq;
char   strLinha[1024];
gvl_abrirArquivo(&arq, "_dados.csv", "r+");
int i = 0;
while(gvl_lerLinha(&arq, strLinha, 1024) != EOF){
    printf("Linha nº %d: ", ++i);
    printf("%s", strLinha);
}
printf("\n\nQtd. Acessos ao disco: %d", arq.bf.contadorAcessos);
gvl_fecharArquivo(&arq);
*/