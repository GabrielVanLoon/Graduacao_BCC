#include <stdlib.h>
#include <stdio.h>
#include "IOprocessor.h"


int main(void){
    
    Arquivo arq;
    char   strLinha[1024];

    gvl_abrirArquivo(&arq, "_dados.csv", "r+");

    int i = 0;
    while(gvl_lerLinha(&arq, strLinha, 1024) != EOF){
        //printf("Linha nº %d\n", ++i);
        printf("%s", strLinha);
    }

    printf("\n\nQtd. Acessos ao disco: %d", arq.bf.contadorAcessos);

    //int i = 0;
    //while(!gvl_carregarPagina(&arq, i++)) {   
    //}

    gvl_fecharArquivo(&arq);

    return 0;
}