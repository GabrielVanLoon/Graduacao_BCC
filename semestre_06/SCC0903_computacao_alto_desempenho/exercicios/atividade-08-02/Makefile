all:
	mpicc -fopenmp findwords.c -o exec -Wall 
run:
	mpirun -np 8 exec entrada1012.txt
	