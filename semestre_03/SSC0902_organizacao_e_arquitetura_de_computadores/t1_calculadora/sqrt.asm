# TRABALHO DE ORGANIZAÇÃO E ARQUITETURA DE COMPUTADORES
# Título:	Calculadora em Assembly MIPS
# Profª.:	Sarita
# Data:		março/2019
#
# Membros:	Débora Buzon da Silva
#		Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
#		Mathias Fernandes
#		Tamiris Tinelli

# Esta implementado nesse arquivo as funções:
# - Raiz Quadrada

.data
	.align 0
	# Resultados
	str_resultado:	.asciiz "\tResultado: "
	str_resto:	.asciiz "\tResto: "
	
	# Quebra de linha
	str_endl:	.asciiz " \n"
	
	str_wait:	.asciiz "\n\tpressione ENTER para continuar...\n"
	 
	
# MACROS ----- ------------------------------------------------------------
	.macro print_str(%str_label)
		li $v0, 4
		la $a0, %str_label
		syscall
	.end_macro
	
	.macro print_float(%reg)
		li $v0, 2
		mov.s $f12, %reg
		syscall
	.end_macro
	
	.macro wait()
		print_str(str_wait)
		li $v0, 12		# Programa aguarda o usuario apertar algum botao para prosseguir
		syscall
	.end_macro
	
.text

# Raiz quadrada -------------------------------------------------------------------------
.globl op_sqrt
op_sqrt:
	addi $sp, $sp, -4		# Empilha o $ra, pois vai chamar outra funcao dentro
	sw   $ra, 0($sp)

	
	jal ler_1float			# Lendo o valor e faz a raiz quadrada
	sqrt.s $f5, $f0			# f5 = sqrt(f0)
	
	print_str(str_resultado)	# Exibindo o resultado
	print_float($f5)
	print_str(str_endl)
	wait()
	
	lw   $ra, 0($sp)		# Desempilha a funcao e retorna
	addi $sp, $sp, 4
	jr $ra
