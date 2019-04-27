#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){

    /**
     * Um caso muito especifico é o de querer ignorar algum valor vindo do terminal.
     * Podemos pensar, por exemplo, em ignorar o segundo numero em uma sequencia de 3 numeros.
     * Para isso podemos usar o operador *.
     * 
     * Veja um exemplo a seguir:
     */
        int num2, num3;
        scanf("%*d %d %d", &num2, &num3);
        printf("Numeros lidos: %d %d\n", num2, num3);

    /** 
     * Esse operador pode ser muito interessante quando você possui uma ideia do formato
     * de entrada que ira receber e quer capturar apenas alguns dos valores da mesma.
     *
     * Ref.: https://medium.com/@zoha131/fun-with-scanf-in-c-3d7a8d310229
     */ 



    return 0;
}