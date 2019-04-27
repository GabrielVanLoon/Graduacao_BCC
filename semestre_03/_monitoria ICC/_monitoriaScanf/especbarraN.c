#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){

    /**
     * UTILIZANDO O %n PARA SABER O TAMANHO DA STRING LIDA
     * 
     * Ao utilizar na leitura de uma string a seguinte mascara: "%s%n",
     * a função scanf irá salvar na nossa variáveis quantos caracteres
     * foram lidos.
     * 
     * Obs. O valor retornado não inclui o \0 que indica o fim da string.
     * 
     * CUIDADO: a mascara %n deve ser inserida junto ao %s, caso contrário o scanf não
     * irá funcionar corretamente. Ou seja:
     * 
     *      "%s%n"              - Correto
     *      "%50s"              - Correto
     *      "%60[^\r\n]%n"      - Correto
     *      "%60[^\r\n] %n"     - Incorreta, há um espaço entre o %[^\r\n] e o %n
     * 
     * 
     * 
     * Veja um exemplo a seguir: 
     */ 
        char str[60]; int  strSize;
        scanf("%60[^\r\n]%n", str, &strSize);
        printf("Foram lidos %d caracteres.\n", strSize);
        printf("String: %s\n\n", str);
    /**
     * A máscara %n também funciona no printf, porém salva na variável
     * quantos caracteres já foram impressos na tela até aquele determinado 
     * momento.
     */
        int qtdChars1, qtdChars2;
        printf("Ola%n, como vai voce?\n%n", &qtdChars1, &qtdChars2); // exibe "Ola, como vai voce?"
        printf("%d %d\n", qtdChars1, qtdChars2); // exibe "3 20"

    return 0;
}