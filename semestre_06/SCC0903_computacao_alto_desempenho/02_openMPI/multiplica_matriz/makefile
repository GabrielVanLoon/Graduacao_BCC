all:
	mpicc mpi_omp.c -o exec -Wall -fopenmp -lm
run:
	mpirun -np 2 exec