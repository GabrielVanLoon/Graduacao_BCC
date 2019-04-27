# Scanf, Armazenamento de Dados e outras bruxarias
Um resumão para você, bixão das programações, nunca mais sofrer na hora de ler valores no seu terminal.

## Tópicos da Aula
 - Scanf, o que é? Como vive? Do que se alimenta?
 - A importância dos tipos de dados no C.
 - Um pouco sobre a memória e o endereçamento de variáveis.
 - Botando a mão na massa! Os especificadores de formatos!
 - Buffer de dados e processamento de I/O
 - Utilizando máscaras para leitura de dados
 - Bônus: utilidades interessantes do scanf.

# Scanf, o que é? Como vive? Do que se alimenta?
	
Podemos facilmente definir o scanf, junto com o printf, como as principais ferramentas para leitura e escrita de dados na linguagem C (ambas presentes na biblioteca <stdio.h>). 

**O uso dessa função** é bastante simples para você, usuário final, pois a mesma encapsula todo o pipeline de processamento de dados lidos no terminal, restando como sua principal tarefa aprender a utilizar corretamente os especificadores que a mesma define (mostraremos como fazer isso nos tópicos adiantes).

Porém, apesar de seu uso ser simples, um bom entendimento de seu funcionamento pode facilitar e evitar muitas dores de cabeça que ocorrem frequentemente (e que iremos citar a seguir). Além disso, esses detalhes mais técnicos podem te ajudar a entender temas como o comportamento de variáveis na memória RAM e leitura de arquivos (uma das matérias que vocês verão próximos ao fim do semestre).

Por fim, antes de entrar em detalhes sobre a função em si, vamos relembrar algumas coisas sobre tipos de dados em C e também sobre endereços de memória!

# A importância dos tipos de dados no C
Caso você não lembre, C é uma linguagem de programação com tipagem forte e estática. Em outras palavras, é obrigatório declarar no programa qual será o tipo de dado que determinada variável irá manipular, sendo impossível alterar o tipo da variável no decorrer do programa.

Qual a importância da tipagem de dados? É muito simples, o tipo de dado irá definir algumas características da variável, como por exemplo:

 - **Tamanho da variável:** Quantos bytes de memória uma variável daquele tipo consome.
 - **Valores:** O tipo de dado define o intervalo de valores que aquele dado representa. Um tipo `char`, por exemplo, consegue representar até 2^8^ valores (vide tabela ASCII), enquanto um `int` consegue representar 2^32^ valores distintos.
 - **Operações:** O tipo de dado também define quais operações o programador poderá realizar com a variável. Valores numéricos, por exemplo, podem realizar operações aritméticas. Contudo, não podemos simplesmente somar dois vetores.

Sabemos, portanto, que mesmo que uma variável do tipo `float` e uma do tipo `int` ocupem o mesmo tamanho de bits na memória, a linguagem C irá interpretar e armazenar seus valores de maneira totalmente distintas na memória RAM. Faça o teste você mesmo:

```c
    float a =  4.0;
    int* ptrA = (int*) &a;
    printf("Lendo float como se fosse uma variável int: %d \n", *ptrA);
```







