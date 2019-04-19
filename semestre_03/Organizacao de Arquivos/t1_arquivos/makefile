build:
	gcc -c IOprocessor.c registro.c
all:
	gcc -o exec IOprocessor.c registro.c main.c
run:
	./exec
verify:
	hexdump -Cv arquivoTrab1.bin > temporario1.txt
	hexdump -Cv target.bin  > temporario2.txt
	meld temporario1.txt temporario2.txt
output:
	meld output.out casos-de-teste-e-arquivos/3.out