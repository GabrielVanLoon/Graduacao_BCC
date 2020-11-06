# Compila a versão serial do programa
base:
	gcc -o exec atividade_02_serial.c -fopenmp -lm

# Compila a versão paralela final do programa
all:
	gcc -o exec atividade_02_v3.c -fopenmp -lm

# Executa o programa
run:
	./exec 

# Compila o Utilitário gerador de testes
all-teste:
	g++ -o testes/teste_generator testes/teste_generator.cpp

# Executa o utilitário gerador de testes que recebe {N, M, Min, Max}
run-teste:
	./testes/teste_generator

# Utilitário para resetar o arquivo principal no cluster
#reset-file:
#	echo "" > atividade_02_v1.c
#	nano atividade_02_v1.c
