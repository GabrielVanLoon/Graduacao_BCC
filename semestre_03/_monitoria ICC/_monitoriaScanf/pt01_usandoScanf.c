#include <stdlib.h>
#include <stdio.h>

int main(void){ 


    /** int scanf(char* str, args ... );
     * 
     * É a principal função para leitura de dados do stdin.
     * Vamos mostrar abaixo o uso básico das máscaras mais frequentes.
     */

        /**
         * ESPECIFICADORES DE VALORES INTEIROS
         * 
         * %d   -   int
         * %ld  -   long int
         * %lld -   long long int
         * %ud  -   unsigned int
         * %lu  -   unsigned long int
         * %llu -   unsigned long long int
         */

        int varInt = 0;
        printf("Entre com um valor inteiro: ");
        scanf("%d", &varInt);
        printf("Valor lido: %d.\n\n", varInt);

        unsigned long long int varULL = 0;
        printf("Entre com um valor inteiro: ");
        scanf("%llu", &varULL);
        printf("Valor lido: %llu.\n\n", varULL);

        /**
         * Obs.: O compilador GCC é inteligente e irá te avisar caso esteja utilizando 
         * o especificador errado, para ler suas variáveis.
         * Portanto, fique atento aos Warnings de compilação.
         */ 
        
        // printf("Entre com um valor inteiro: ");
        // scanf("%d", &varULL); // -> O compilador irá acusar erro no especificador. 
        // printf("Valor lido: %d.\n\n", varULL);

        /**
         * LEITURA DE VALORES INTEIROS EM OUTRAS BASES
         * 
         * A linguagem C possui alguns facilitadores para aqueles que
         * precisam lidar com Input/Output de dados em formato octal e hexadecimal.
         * 
         * Com as máscaras abaixo, o scanf irá ler um número na base desejada e armazenar
         * seu valor em uma variável do tipo int. Dessa forma, caso você tenha que fazer conversões
         * do tipo octal -> decimal, decimal -> hexadecimal, octal -> hexadecimal o C irá
         * cuidar de todo o trabalho pesado.
         * 
         * %o   -   unsigned int (Formato Octal)
         * %x   -   unsigned int (Formato Octal)
         * %lx  -   unsigned long int (Formato Octal)
         * ...
         * 
         * Obs.: É preciso haver um cuidado na hora de lidar com os especificadores
         * %x e %o, porque ai atribuir o valor lido à um tipo não unsigned o compilador 
         * não irá emitir erros.
         */
            unsigned int varOctal = 0;
            printf("Entre com um valor octal: ");
            scanf("%o", &varOctal);
            printf("Valor lido na base 8:  %o.\n", varOctal);
            printf("Valor lido na base 16: %x.\n", varOctal);
            printf("Valor lido na base 10: %d.\n\n", varOctal);

            long int varHexa = 0;
            printf("Entre com um valor Hexa: ");
            scanf("%lx", &varHexa);
            printf("Valor lido na base 16:  %lx.\n", varHexa);
            printf("Valor lido na base 10: %ld.\n\n", varHexa);

        /**
         * ALINHAMENTO DE DADOS UTILIZANDO SCANF 
         */
            int a = 132, b = 15239, c = 5;
            printf("%d %d %d\n", a, b, c);
            printf("%5d %5d %5d\n", a, b, c);    // Alinha sem inserir nada
            printf("%05d %05d %05d\n", a, b, c); // Alinha inserindo zeros
            printf("%-5d %-5d %-5d\n\n", a, b, c); // Alinha à esquerda.

        /**
         * BRINCANDO COM AS VARIAVEIS, ESPECIFICADORES E ARITMÉTICA DE PONTEIRO
         */

            // Salva dois bytes no segundo e terceiro bloco de byte de var
            int var = 0;
            scanf("%hi", (short*) (((char*)(&var))+3) );
            printf("\n%d\n", var);

    return 0;
}