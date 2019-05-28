/**
 * Trabalho de Organização de arquivos
 * Título: T4 - Index Secundário Fortemente Ligado
 * Autor:  Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
 *         Tamiris Fernandes Tinelli
 * Prof.:  Dra. Cristina Dutra de Aguiar Ciferri
 * Data:   maio/2019
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
    void lerValorCampo(char tagCampoBusca, char* valorBusca);
    void binarioNaTela2(char *nomeArquivoBinario);

int main(void){
 
    Arquivo     bin, bin2, bin3, binIndex, csv;
    Header      cabecalho, cabecalho2, cabecalho3;
    HeaderIndex cabecalhoIndex;
    Registro    regAux;
    Index*      indices = NULL;
    
    int     opcao;
    char    nomeArquivoCSV[64];
    char    nomeArquivoBin[64]     = "arquivoTrab1.bin";
    char    nomeArquivoBin2[64]    = "arquivoTrab2.bin";
    char    nomeArquivoBin3[64]    = "arquivoTrab2.bin";
    char    nomeArquivoIndice[64]  = "arquivoTrab1.bin";

    int     qtdRegistros, qtdRemocoes, qtdInsercoes, qtdAtualizacoes;
    char    campoBusca[64];
    char    tagCampoBusca;
    char    valorBusca[164];

    char    campoAtualiza[64];
    char    tagCampoAtualiza;
    char    valorAtualiza[164];
    

    // Lendo a opção do usuário
    scanf(" %d", &opcao);

    switch(opcao){

        // CSV para Binario
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

        // Listar registros
        case 2:
            scanf(" %60s", nomeArquivoBin);

            if(gvl_abrirArquivo(&bin, nomeArquivoBin, "r+")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho = gvl_carregarCabecalho(&bin);

            // if(cabecalho.status != '1' || gvl_setStatusCabecalho(&bin, &cabecalho, '0')){
            if(cabecalho.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            } 
            
            qtdRegistros = gvl_listarRegistros(&bin);

            if(qtdRegistros > 0)
                printf("Número de páginas de disco acessadas: %d", bin.bf.contadorAcessos);

            gvl_fecharArquivo(&bin);

            break;

        // Buscar registro
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
            char tagCampoBusca = getTagCampo(campoBusca);

            if(tagCampoBusca == 'i') 
                onlyFirst = 1;

            qtdRegistros =  gvl_buscarRegistros(&bin, &cabecalho, tagCampoBusca, valorBusca, onlyFirst);

            if(qtdRegistros > 0)
                printf("Número de páginas de disco acessadas: %d", bin.bf.contadorAcessos);

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);

            break;

        // Remover registro
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
                
                lerValorCampo(tagCampoBusca, &valorBusca[0]);

                onlyFirst = (tagCampoBusca == 'i') ? 1 : 0;

                int c = gvl_removerRegistros(&bin, &cabecalho, tagCampoBusca, valorBusca, onlyFirst);
                // printf("Campo [%s] Tag[%c] Busca[%s] removeu %d\n", campoBusca, tagCampoBusca, valorBusca, c);
            }
            
            // Após realizar as exclusões precisa atualizar a lista de removidos
            gvl_ordenarRegistrosRemovidos(&bin, &cabecalho, 0, tamListaRemovidos-1);
            // gvl_exibirListaRemovidos(&bin, &cabecalho); 
            gvl_escreverRegistroRemovidos(&bin, &cabecalho);
            gvl_limparListaRemovidos(&bin, &cabecalho);        

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);
            binarioNaTela2(nomeArquivoBin);

            break;
        
        // Inserir registro
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
            binarioNaTela2(nomeArquivoBin);
            break;

        // Atualizar registro
        case 6:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %d",   &qtdAtualizacoes);

            if(gvl_abrirArquivo(&bin, nomeArquivoBin, "r+")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho = gvl_carregarCabecalho(&bin);

            if(cabecalho.status != '1' || gvl_setStatusCabecalho(&bin, &cabecalho, '0')){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            for(int i = 0; i < qtdAtualizacoes; i++){
                scanf(" %60s", campoBusca);
                tagCampoBusca = getTagCampo(campoBusca);
                lerValorCampo(tagCampoBusca, &valorBusca[0]);

                scanf(" %60s", campoAtualiza);
                tagCampoAtualiza = getTagCampo(campoAtualiza);
                lerValorCampo(tagCampoAtualiza, &valorAtualiza[0]);

                onlyFirst = (tagCampoBusca == 'i') ? 1 : 0;

                int c = gvl_atualizarRegistros(&bin, &cabecalho, tagCampoBusca, valorBusca,tagCampoAtualiza, valorAtualiza, onlyFirst);
                //int c = 0;
                //printf("Busca: Campo[%s] Tag[%c] Valor[%s]\n", campoBusca,    tagCampoBusca, valorBusca);
                //printf("Atual: Campo[%s] Tag[%c] Valor[%s]\n", campoAtualiza, tagCampoAtualiza, valorAtualiza);
                // printf("Atualizou %d\n\n", c);
            }
            
            // Após realizar as exclusões precisa atualizar a lista de removidos
            gvl_ordenarRegistrosRemovidos(&bin, &cabecalho, 0, tamListaRemovidos-1);
            // gvl_exibirListaRemovidos(&bin, &cabecalho); 
            gvl_escreverRegistroRemovidos(&bin, &cabecalho);
            gvl_limparListaRemovidos(&bin, &cabecalho);        

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);
            binarioNaTela2(nomeArquivoBin);
            break;

        // Ordenar internamente
        case 7:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", nomeArquivoBin2);

            if( gvl_abrirArquivo(&bin, nomeArquivoBin,   "r+b") ||
                gvl_abrirArquivo(&bin2, nomeArquivoBin2, "wb")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho = gvl_carregarCabecalho(&bin);

            if(cabecalho.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            gvl_ordenarArquivo(&bin, &bin2, &cabecalho);
            
            gvl_fecharArquivo(&bin);
            gvl_fecharArquivo(&bin2);
            binarioNaTela2(nomeArquivoBin2);
            break;
        // File Merging
        case 8:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", nomeArquivoBin2);
            scanf(" %60s", nomeArquivoBin3);

            if( gvl_abrirArquivo(&bin, nomeArquivoBin,   "r+b") ||
                gvl_abrirArquivo(&bin2, nomeArquivoBin2, "r+b") || 
                gvl_abrirArquivo(&bin3, nomeArquivoBin3, "wb")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho  = gvl_carregarCabecalho(&bin);
            cabecalho2 = gvl_carregarCabecalho(&bin2);

            if(cabecalho.status != '1' || cabecalho2.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            gvl_mergingArquivos(&bin, &bin2, &bin3, &cabecalho);

            gvl_fecharArquivo(&bin);
            gvl_fecharArquivo(&bin2);
            gvl_fecharArquivo(&bin3);
            binarioNaTela2(nomeArquivoBin3);
            break;

        // File Matching
        case 9:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", nomeArquivoBin2);
            scanf(" %60s", nomeArquivoBin3);

            if( gvl_abrirArquivo(&bin, nomeArquivoBin,   "r+b") ||
                gvl_abrirArquivo(&bin2, nomeArquivoBin2, "r+b") || 
                gvl_abrirArquivo(&bin3, nomeArquivoBin3, "wb")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho  = gvl_carregarCabecalho(&bin);
            cabecalho2 = gvl_carregarCabecalho(&bin2);

            if(cabecalho.status != '1' || cabecalho2.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            gvl_matchingArquivos(&bin, &bin2, &bin3, &cabecalho);

            gvl_fecharArquivo(&bin);
            gvl_fecharArquivo(&bin2);
            gvl_fecharArquivo(&bin3);
            binarioNaTela2(nomeArquivoBin3);
            break;

        // Gerar Index
        case 10:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", nomeArquivoIndice);

            if( gvl_abrirArquivo(&bin,      nomeArquivoBin,    "r+b") || 
                gvl_abrirArquivo(&binIndex, nomeArquivoIndice, "w+b")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho  = gvl_carregarCabecalho(&bin);
            if( cabecalho.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            if( gvl_criarVetorIndices(&bin, &cabecalho, &indices, &cabecalhoIndex) ||
                gvl_escreverArquivoIndices(&binIndex, &cabecalhoIndex, &indices)){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            gvl_destruirIndices(&indices);

            gvl_fecharArquivo(&bin);
            gvl_fecharArquivo(&binIndex);
            binarioNaTela2(nomeArquivoIndice);
            break;

        // Buscar c/ Index
        case 11:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", nomeArquivoIndice);
            scanf(" %60s", campoBusca);
            scanf(" %60[^\n\r]s", valorBusca);

            if( gvl_abrirArquivo(&bin,      nomeArquivoBin,    "r+b") || 
                gvl_abrirArquivo(&binIndex, nomeArquivoIndice, "r+b")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho      = gvl_carregarCabecalho(&bin);
            cabecalhoIndex = gvl_carregarCabecalhoIndex(&binIndex); 

            if(cabecalho.status != '1' || cabecalhoIndex.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            } 
            
            indices = gvl_carregarArquivoIndices(&binIndex, &cabecalhoIndex);
            
            // Realizando a busca dos registros
            qtdRegistros =  gvl_buscarRegistros2(&bin, &cabecalho, &indices, &cabecalhoIndex, valorBusca);
            
            if(qtdRegistros > 0){
                printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", binIndex.bf.contadorAcessos);
                printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", bin.bf.contadorAcessos);
            }

            gvl_fecharArquivo(&bin);
            gvl_fecharArquivo(&binIndex);
            gvl_destruirIndices(&indices);
            break;

        // Remoção c/ Index
        case 12:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", nomeArquivoIndice);
            scanf(" %d",   &qtdRemocoes);

            if( gvl_abrirArquivo(&bin,      nomeArquivoBin,    "r+b") || 
                gvl_abrirArquivo(&binIndex, nomeArquivoIndice, "r+b")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho      = gvl_carregarCabecalho(&bin);
            cabecalhoIndex = gvl_carregarCabecalhoIndex(&binIndex); 

            if(cabecalho.status != '1' || cabecalhoIndex.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            } 
            
            indices = gvl_carregarArquivoIndices(&binIndex, &cabecalhoIndex);

            // Realizando as remoções
            for(int i = 0; i < qtdRemocoes; i++){
                scanf(" %60s", campoBusca);
                tagCampoBusca = getTagCampo(campoBusca);

                lerValorCampo(tagCampoBusca, &valorBusca[0]);

                int c = gvl_removerRegistros2(&bin, &cabecalho, &indices, &cabecalhoIndex, valorBusca);
                // printf("Campo [%s] Busca[%s] removeu %d\n", campoBusca, valorBusca, c);
            }
            
            // Agora é preciso atualizar o arquivo de indice, para isso vamos fechar o
            // arquivo e reabrir ele com um novo modo e reinserir tudo
            gvl_fecharArquivo(&binIndex);
            gvl_abrirArquivo(&binIndex, nomeArquivoIndice, "wb");
            gvl_escreverArquivoIndices(&binIndex, &cabecalhoIndex, &indices);

            // Após realizar as exclusões precisa atualizar a lista de removidos
            gvl_ordenarRegistrosRemovidos(&bin, &cabecalho, 0, tamListaRemovidos-1);
            gvl_escreverRegistroRemovidos(&bin, &cabecalho);
            gvl_limparListaRemovidos(&bin, &cabecalho);        

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);
            gvl_fecharArquivo(&binIndex);
            gvl_destruirIndices(&indices);
            binarioNaTela2(nomeArquivoIndice);
            break;

        // Inserir c/ Index
        case 13:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", nomeArquivoIndice);
            scanf(" %d",   &qtdInsercoes);

            if( gvl_abrirArquivo(&bin,      nomeArquivoBin,    "r+b") || 
                gvl_abrirArquivo(&binIndex, nomeArquivoIndice, "r+b")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho      = gvl_carregarCabecalho(&bin);
            cabecalhoIndex = gvl_carregarCabecalhoIndex(&binIndex); 

            if(cabecalho.status != '1' || cabecalhoIndex.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            } 
            
            indices = gvl_carregarArquivoIndices(&binIndex, &cabecalhoIndex);

            // Realizando as inserções 
            for(int i = 0; i < qtdInsercoes; i++){
               regAux = lerNovoRegistro();
               gvl_inserirNovoRegistro2(&bin, &cabecalho, &indices, &cabecalhoIndex, &regAux);
               gvl_destruirRegistro(&regAux);
            }

            // Após realizar as inserções precisa atualizar a lista de removidos
            gvl_ordenarRegistrosRemovidos(&bin, &cabecalho, 0, tamListaRemovidos-1);
            gvl_escreverRegistroRemovidos(&bin, &cabecalho);
            gvl_limparListaRemovidos(&bin, &cabecalho);        
            
            // Agora é preciso atualizar o arquivo de indice, para isso vamos fechar o
            // arquivo e reabrir ele com um novo modo e reinserir tudo
            gvl_ordenarIndices(&cabecalhoIndex, &indices);
            gvl_fecharArquivo(&binIndex);
            gvl_abrirArquivo(&binIndex, nomeArquivoIndice, "wb");
            gvl_escreverArquivoIndices(&binIndex, &cabecalhoIndex, &indices);

            gvl_setStatusCabecalho(&bin, &cabecalho, '1');

            gvl_fecharArquivo(&bin);
            gvl_fecharArquivo(&binIndex);
            gvl_destruirIndices(&indices);
            binarioNaTela2(nomeArquivoIndice);
            break;

        // Estatisticas (Com Index VS Sem Index)
        case 14:
            scanf(" %60s", nomeArquivoBin);
            scanf(" %60s", nomeArquivoIndice);
            scanf(" %60s", campoBusca);
            scanf(" %60[^\n\r]s", valorBusca);

            if( gvl_abrirArquivo(&bin,      nomeArquivoBin,    "r+b") || 
                gvl_abrirArquivo(&binIndex, nomeArquivoIndice, "r+b")){
                printf("Falha no processamento do arquivo.\n");
                break;
            }

            cabecalho      = gvl_carregarCabecalho(&bin);
            cabecalhoIndex = gvl_carregarCabecalhoIndex(&binIndex); 

            if(cabecalho.status != '1' || cabecalhoIndex.status != '1'){
                printf("Falha no processamento do arquivo.\n");
                break;
            } 
            
            indices = gvl_carregarArquivoIndices(&binIndex, &cabecalhoIndex);
            
            // Variavel que ira registrar as variações de acesso à disco
            int qtdAcessos;

            // Realizando a busca dos registros
            qtdRegistros =  gvl_buscarRegistros(&bin, &cabecalho, 'n', valorBusca, 0);
            if( qtdRegistros > 0){
                printf("Número de páginas de disco acessadas: %d\n", bin.bf.contadorAcessos);
                
                // reiniciando o contador de acessos
                qtdAcessos             = bin.bf.contadorAcessos;
                bin.bf.contadorAcessos = 1; // Mantém apenas o custo de leitar do header
                gvl_flushBuffer(&bin);

                // Realizando a busca dos registros com index
                printf("*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");
                qtdRegistros =  gvl_buscarRegistros2(&bin, &cabecalho, &indices, &cabecalhoIndex, valorBusca);
                printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", binIndex.bf.contadorAcessos);
                printf("Número de páginas de disco para acessar o arquivo de dados: %d\n\n", bin.bf.contadorAcessos);

                printf("A diferença no número de páginas de disco acessadas: %d\n", qtdAcessos - bin.bf.contadorAcessos);
            }

            gvl_fecharArquivo(&bin);
            gvl_fecharArquivo(&binIndex);
            gvl_destruirIndices(&indices);
            break;

        // Exibir lista de removidos
        case 20: 
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

    /**
     * Campos de tamanho variavel ou string
     */
    scanf(" %c", &c);
    if(c == 'N'){
        scanf(" %60s", valor);
        r.telefoneServidor[0] = '\0';
    } else {
        scanf(" %[^\"]%*c", r.telefoneServidor);
    }

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

void lerValorCampo(char tagCampoBusca, char* valorBusca){
    char strAuxiliar[64];
    char aux;

    if(tagCampoBusca == 'n' || tagCampoBusca == 'c' || tagCampoBusca == 't'){
        scanf(" %c", valorBusca);
        if(valorBusca[0] == '"'){
            scanf("%160[^\n\r\"]%*c", valorBusca);
            getchar();
        } else {
            scanf("%s", valorBusca+1);
        }
    } else 
        scanf(" %s", valorBusca);
}

void binarioNaTela2(char *nomeArquivoBinario) {

	/* Escolha essa função se você já fechou o ponteiro de arquivo 'FILE *'.
	*  Ela vai abrir de novo para leitura e depois fechar. */

	unsigned char *mb;
	unsigned long i;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela2): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar? Se você não fechou ele, pode usar a outra função, binarioNaTela1, ou pode fechar ele antes de chamar essa função!\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0)	printf("\n");
	}
	free(mb);
	fclose(fs);
}