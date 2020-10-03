all:
	gcc -o exec hash_table.c main.c -std=c99 -lm
run:
	./exec
debug:
	gcc -o exec hash_table.c main.c -std=c99 -lm
	valgrind ./exec 