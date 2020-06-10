all:
	gcc -o exec analise.c tads/lista_ordenada.c tads/listaord_sentinela.c tads/abb.c tads/buscabin.c tads/listacirc_freq.c tads/pilha.c tads/avl.c main.c -std=c99 -O2
run:
	./exec
debug:
	gcc -o exec analise.c tads/lista_ordenada.c tads/listaord_sentinela.c tads/abb.c tads/buscabin.c tads/listacirc_freq.c tads/pilha.c tads/avl.c main.c -std=c99 -g
	gdb exec
