all:
	gcc -o exec fabrica.c main.c -std=c99
run:
	./exec 5 3 2 1 carro 2 boneca 3 urso 4 carro 5 boneca
debug:
	gcc -o exec fabrica.c main.c -std=c99
	valgrind --leak-check=full ./exec 5 2 2 1001 boneca1 1002 carro 1003 boneca2 1004 bola 1005 cueca