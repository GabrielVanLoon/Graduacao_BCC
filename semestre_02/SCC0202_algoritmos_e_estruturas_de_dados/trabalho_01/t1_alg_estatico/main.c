/**
 * Trabalho de Algoritmo e Estruturas de Dados
 * Título: T1 - Loja de Brinquedos (Versão Estática Sequêncial)
 * Autor:  Gabriel Van Loon
 * Prof.:  Robson Cordeiro
 * Data:   Outubro/2018
 *
 * Descrição:
 * - O algoritmo desse trabalho simula um robô de uma fábrica de brinquedos 
 *  cujo objetivo é armazenar @n brinquedos em uma esteira de produção e 
 *  inserí-los em caixas.
 * - Os componentes desse processão são modelados com as estruturas de dados 
 *   conforme abaixo:
 *      >> Esteira de Brinquedos := Lista Circular de Brinquedos
 *      >> Caixa de Brinquedos   := Pilha de Brinquedos
 *      >> Esteira de Caixas     := Fila de Pilhas
 *
 * Obs: programa está segmetado em blocos que explicam como o robô irá interagir
 *   com essas três estruturas.
 * 
 * Entrada:
 * - O programa recebe suas entradas por meio de argumentos @argv[] conforme o
 *   modelo abaixo: 
 *   ./exec @n @k @p numSerie[0] modelo[0] ... numSerie[n-1] modelo[n-1]
 * 
 * Variáveis:
 *    @n := Quantidade de brinquedos;
 *    @k := Percorrer a esteira de brinquedos de K em K;
 *    @p := Limite de brinquedos em uma caixa.
 *
 * Saída:
 * - Para cada caixa criada e inserida na Esteira de Caixas, o programa exibe
 *   o nome do brinquedo no topo e a quantidade(@qtd) de brinquedos dentro 
 *   da mesma no seguinte formato:
 *      >> "Caixa nº[1..@n]: brinquedo <numSerie[],modelo[]> - quantidade @qtd.\n"
 */
#include <stdlib.h>
#include <stdio.h>
#include "fabrica.h"

int main(int argc, char* argv[]){

    // Vericando se foi enviado a quantidade mínima de argumentos
	if(argc < 6){
		printf("\n\nArgumentos do programa enviados incorretamente!\n");
		printf("n k p numSerie[0] modelo[0] numSerie[1] modelo[1] ... numSerie[n-1] modelo[n-1]	\n\n");
		return 0;
	}
	
	/* Variáveis: 
	 * n - Qtd. de brinquedos.
	 * k - Percorre a esteira de brinquedos de K em K.
	 * p - Capacidade máxima da caixa.
	 */
	int n, k, p;
	ListaCirc esteiraBrinquedos;
	Pilha     caixa;
	Fila  esteiraCaixas;
	Brinquedo aux;

		// Lendo as variaveis n k p
		sscanf(argv[1], "%d", &n);
		sscanf(argv[2], "%d", &k);
		sscanf(argv[3], "%d", &p);

		// Verificando se o valor N é compativel com
		if((2*n+4) != argc) {
			printf("\n\nQuantidade de brinquedos incorreta, insira os argumentos conforme abaixo!\n");
			printf("n k p numSerie[0] modelo[0] numSerie[1] modelo[1] ... numSerie[n-1] modelo[n-1]	\n\n");
			return 0;
		}

	// Preparando as variaveis do programa
	esteiraBrinquedos = criar_lista();
	caixa             = criar_pilha(p);
	esteiraCaixas     = criar_fila();

	/**
	 * 1ª ETAPA DO PROGRAMA
	 * 
	 * - Todos os brinquedos que foram enviados via parâmetro serão inseridos
	 *   na esteira de brinquedos. 
	 */ 
		for(int i = 0; i < n; i++){
			sscanf(argv[4+(2*i)], "%d", &aux.numSerie);
			sscanf(argv[5+(2*i)], "%20s", aux.nome);
			

			if(inserir_na_lista(&esteiraBrinquedos, aux)){
				printf("Não cabem mais brinquedos na esteira!!\n");
				continue;
			}
		}

		// Caso queira visualizar a esteira descomente abaixo
		// print_lista(&esteiraBrinquedos);

	/**
	 * 2ª ETAPA DO PROGRAMA
	 * 
	 * - Percorre a esteira e remove um brinquedo de K em K posições.
	 * - Os brinquedos removidos são inseridos em uma Caixa de Brinquedo.
	 * - Toda vez que alcança o fim da esteira, retorna ao inicio e decrementa
	 *   o valor do K em uma unidade.
	 * - Quando a caixa de brinquedo atinge a capacidade máxima, insere ela na
	 *   esteira de caixas e estancia uma nova caixa.
	 */ 
		int pos = 1; 
		while(!esta_vazia_lista(&esteiraBrinquedos)){
			
			// Caso queira acompanhar as remocoes da lista descomente essa linha
			// print_lista(&esteiraBrinquedos);

			// Alcançou o fim da fila
			if(remover_da_lista(&esteiraBrinquedos, pos, &aux)){
				k   = (k-1 > 1) ? k-1 : 1;
				pos = 1; 
				continue;
			}

			// Inserindo brinquedo na caixa
			push(&caixa, aux);

			// Se a caixa lotou, insere a caixa na esteira de caixas
			if(esta_cheia_pilha(&caixa)){
				inserir_na_fila(&esteiraCaixas, caixa);

				// Estanciando uma nova caixa
				caixa = criar_pilha(p);
			}

			pos += k-1;
		}

		// Inserindo a ultima caixa caso precisa
		if(!esta_vazia_pilha(&caixa))
			inserir_na_fila(&esteiraCaixas, caixa);

	/**
	 * 3ª ETAPA DO PROGRAMA
	 * 
	 * - Remove as caixas da esteira de Caixas, exibindo quantos e quais brin-
	 *   quedos há em cada uma delas.
	 * - Ao fim de cada caixa também realiza o free da memória.
	 */ 
		int qtdCaixas = 0,qtdBrinquedos;
		while(!esta_vazia_fila(&esteiraCaixas)){

			qtdCaixas++;       // Contabilizando qtd de caixas na esteira.
			qtdBrinquedos = 0; // Contabilizando qtd de brinquedos na caixa.
			remover_da_fila(&esteiraCaixas, &caixa);
			
			aux = top(&caixa);
			printf("Caixa nº%d: brinquedo <%d,%s>", qtdCaixas, aux.numSerie, aux.nome);
			while(!esta_vazia_pilha(&caixa)){
				qtdBrinquedos++;
				
				aux = top(&caixa);
				pop(&caixa);

			}
			printf(" - quantidade %d.\n", qtdBrinquedos);

			remover_pilha(&caixa);
		}
		printf("\n");

	remover_fila(&esteiraCaixas);
	remover_lista(&esteiraBrinquedos);

	return 0;
}