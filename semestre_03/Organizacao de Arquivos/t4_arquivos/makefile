build:
	gcc -c IOprocessor.c index.c registro.c
all:
	gcc -o exec IOprocessor.c index.c registro.c main.c
run:
	./exec
out:
	meld    temp1.txt casos/15.out

verify: 
	hexdump -Cv binarios/binario-12.bin                 > temp1.txt 
	hexdump -Cv binariosBackup/binario-12-depois.bin    > temp2.txt
	meld    temp1.txt temp2.txt

verify2: 
	hexdump -Cv binarios/binario-12.index                 > temp1.txt 
	hexdump -Cv binariosBackup/binario-12-depois.index    > temp2.txt
	meld    temp1.txt temp2.txt
