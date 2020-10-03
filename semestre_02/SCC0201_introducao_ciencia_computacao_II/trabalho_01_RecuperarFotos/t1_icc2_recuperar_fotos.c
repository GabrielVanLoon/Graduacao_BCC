/**
 * Trabalho de Introdução a Ciencia da Computacao II
 * Título: T1 - Recuperador de Fotos de uma Memoria Continua
 * Autor:  Gabriel Van Loon
 * Prof.:  Moacir Ponti
 * Data:   Agosto/2018
 * 
 * DESCRIÇÃO
 * O programa recebe N blocos de memoria de 512 bytes cada, que representam
 * um bloco de memoria no sistema de arquivos FAT, e entao extrai todas
 * as possiveis imagens JPEG que conseguir encontrar.
 * 
 * Os arquivos JPEG possuem sempre, no inicio de seu arquivo, o seguinte padrao 
 * de Bytes "ffd8 ffe_", onde "_" pode assumir qualquer valor.
 * 
 * RETORNO
 * O programa extrai as imagens e as salva na mesma pasta cujo codigo foi 
 * executado, enumerando-as por ordem de extração.
 * Exemplo: 000.jpg, 001.jpg, 002.jpg ..... 999.jpg
 */
# include <stdlib.h>
# include <stdio.h>

const char INICIO_JPEG[4] = {0xff, 0xd8, 0xff, 0xe0};

int main(void){

	/**
	* Variaveis:
	* 	@qtd_imagens: Contador de quantas imagens ja foram extraidas.
	* 	@blocos: Conta quantos blocos ja passaram pelo loop.
	* 	@bloco_memoria: Salva os 512 bytes de cada iteracao do loop
	* 	@imagem_recuperada: Arquivo que sera salvo as imagens encontradas.
	*/	
	int qtd_imagens = 0, blocos = 0;
	char* bloco_memoria = calloc(512, sizeof(char));
	FILE* imagem_recuperada = NULL;

	// Percorrendo os bytes em blocos de 512 bytes
	while(fread(bloco_memoria, 1, 512, stdin) == 512){

		// Verificando se os 4 primeiros bytes correspondem ao padrao do inicio de um JPEG
		if(bloco_memoria[0] == INICIO_JPEG[0] && bloco_memoria[1] == INICIO_JPEG[1] && bloco_memoria[2] == INICIO_JPEG[2] 
			&& bloco_memoria[3] >= INICIO_JPEG[3]) {

				// Gera o novo nome, incrementando o contador
				char nome_img[8];
				sprintf(nome_img, "%03d.jpg", qtd_imagens++);

				// Ajusta o FILE* para apontar para a nova imagem
				imagem_recuperada = fopen(nome_img, "wb+");
		}

		// Se o FILE* ja estiver apontando para alguma imagen, escreve o bloco
		if(imagem_recuperada != NULL)
			fwrite(bloco_memoria, 1, 512, imagem_recuperada);
		

		blocos++;
	}

	// Caso nao tenha sido encontrado nenhuma imagem JPG, informa o erro
	if(qtd_imagens == 0)
		printf("Could not find pictures\n");
	
	// Libera a alocacao dinamica e o ponteiro FILE*
	if(bloco_memoria != NULL) 
		free(bloco_memoria);

	if(imagem_recuperada != NULL) 
		fclose(imagem_recuperada);
	
	return 0;
}
