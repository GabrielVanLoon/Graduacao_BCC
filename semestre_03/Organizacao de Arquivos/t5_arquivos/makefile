build:
	gcc -c IOprocessor.c arvoreB.c
	rm *.o
all:
	gcc -o exec IOprocessor.c index.c arvoreB.c registro.c main.c -lm
run:
	./exec

verify: 
	hexdump -Cv binarios/binario-3.btree          > temp1.txt 
	hexdump -Cv binariosBackup/binario-3.btree    > temp2.txt
	meld    temp1.txt temp2.txt

