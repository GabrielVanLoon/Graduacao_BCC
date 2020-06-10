all:
	gcc -o exec trabalho_02_alg/analise.c trabalho_02_alg/tads/lista_ordenada.c trabalho_02_alg/tads/listaord_sentinela.c trabalho_02_alg/tads/abb.c trabalho_02_alg/tads/buscabin.c trabalho_02_alg/tads/listacirc_freq.c trabalho_02_alg/tads/avl.c trabalho_02_alg/main.c -std=c99 
run:
	./exec
prof:
	gcc -o exec trabalho_02_alg/analise.c trabalho_02_alg/tads/lista_ordenada.c trabalho_02_alg/tads/listaord_sentinela.c trabalho_02_alg/tads/abb.c trabalho_02_alg/tads/buscabin.c trabalho_02_alg/tads/listacirc_freq.c trabalho_02_alg/tads/avl.c trabalho_02_alg/main.c -std=c99  -pg
	./exec
	gprof exec gmon.out > saida_gprof.txt
	python gprof2dot.py saida_gprof.txt > saida_gprof.dot
graph:
	dot -Tpng -o saida_grafo.png saida_gprof.dot
clear:
	rm exec gmon.out saida_gprof.txt saida_gprof.dot