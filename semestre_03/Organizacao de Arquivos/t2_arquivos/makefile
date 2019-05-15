build:
	gcc -c IOprocessor.c registro.c
all:
	gcc -o exec IOprocessor.c registro.c main.c
run:
	./exec

verify:
	hexdump -Cv arquivoTrab1.bin > temp1.txt
	hexdump -Cv _target.bin      > temp2.txt
	meld    temp1.txt temp2.txt

case: 
	hexdump -Cv binarios/binario-7.bin        > temp1.txt 
	hexdump -Cv binarios/binario-7-depois.bin > temp2.txt
	meld    temp1.txt temp2.txt

case10: 
	hexdump -Cv output.out > temp1.txt 
	hexdump -Cv casos/10.out > temp2.txt
	meld    temp1.txt temp2.txt