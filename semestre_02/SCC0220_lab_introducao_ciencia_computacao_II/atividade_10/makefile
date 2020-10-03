all:
	gcc -o exec arvore_quart.c main.c -std=c99
run:
	./exec
debug:
	gcc -o exec arvore_quart.c main.c -std=c99
	valgrind --leak-check=full ./exec