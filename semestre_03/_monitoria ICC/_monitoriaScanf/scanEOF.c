#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(void){

    /**
     * O QUE É EOF (End of File)?
     * 
     * EOF é um valor retornado por funções em C que avisam que
     * alguma função de leitura de dados alcançou o fim dos arquivos.
     * 
     * Essa flag é utilizada principalmente quando estamos lidando com arquivos
     * em C e, como vocês ainda não tiveram esse conteúdo, não vou alongar explicando
     * as situações que ela ocorre. 
     * 
     * o EOF é frequentemente utilizado para criar loops de leitura de dados 
     * em que não se sabe ao certo quantos valores serão lidos.
     * 
     * Veja o exemplo abaixo:
     * 
     */
        int valor, soma = 0;;
        printf("Digite um valor (Ctrl+D para sair): ");
        while( scanf("%d", &valor) != EOF ){
            soma += valor;
            printf("Valor digitado: %d\nDigite o proximo valor: ", valor);
        }
        printf("Soma total: %d\n\n", soma);
    /**
     * Observação: A função scanf retorna a quantidade de argumentos que foram
     * lidos com sucesso antes que o valor EOF fosse encontrado.
     *  
     * TESTE NO CÓDIGO ABAIXO: 
     * Entre com os valores de os valores de 'a' e 'b'. Pressione enter
     * para enviar os dados e em seguida pressione ctrl+D e veja o retorno de scanF.
     */
        int a = 0, b = 0, c = 0, qtdArgs = 0;
        qtdArgs = scanf("%d %d %d", &a, &b, &c);
        printf("Qtd. argumeNtos lidos: %d\n\n", qtdArgs);


    return 0;
}