build:
	gcc -c IOprocessor.c registro.c
all:
	gcc -o exec IOprocessor.c registro.c main.c
run:
	./exec

verify: 
	hexdump -Cv binarios/binario-8-saida.bin          > temp1.txt 
	hexdump -Cv binariosBackup/binario-8-saida.bin    > temp2.txt
	meld    temp1.txt temp2.txt
