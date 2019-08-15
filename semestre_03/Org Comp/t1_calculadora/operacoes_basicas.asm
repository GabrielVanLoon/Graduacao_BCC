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
# - Soma.
# - Subtracao
# - Divisao
# - Multiplicacao

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
	
	.macro print_int(%reg)
		li $v0, 1
		add $a0, $zero, %reg
		syscall
	.end_macro
	
	.macro wait()
		print_str(str_wait)
		li $v0, 12		# Programa aguarda o usuario apertar algum botao para prosseguir
		syscall
	.end_macro
	
.text

# SOMA -------------------------------------------------------------------------
.globl op_soma
op_soma:
	addi $sp, $sp, -4		# Empilha o $ra, pois vai chamar outra funcao dentro
	sw   $ra, 0($sp)

	jal ler_2param			# Chama a funcao para carregar os parametros em a0 e a1
	add $t5, $v0, $v1		# Realiza a soma: t5 = v0 + v1
	
	print_str(str_resultado)	# Exibindo o resultado
	print_int($t5)
	print_str(str_endl)
	wait()
	
	lw   $ra, 0($sp)		# Desempilha a funcao e retorna
	addi $sp, $sp, 4
	jr $ra
	
# SUBTRACAO -------------------------------------------------------------------------
.globl op_sub
op_sub:
	addi $sp, $sp, -4	# Empilha o $ra, pois vai chamar outra funcao dentro
	sw   $ra, 0($sp)

	jal ler_2param		# Chama a funcao para carregar os parametros em a0 e a1
	sub $t5, $v0, $v1	# Realiza: t5 = v0 - v1
	
	print_str(str_resultado)	# Exibindo o resultado
	print_int($t5)
	print_str(str_endl)
	wait()
	
	lw   $ra, 0($sp)	# Desempilha a funcao e retorna
	addi $sp, $sp, 4
	jr $ra
	
	
# MULTILICACAO -------------------------------------------------------------------------
.globl op_mult
op_mult:
	addi $sp, $sp, -4	# Empilha o $ra, pois vai chamar outra funcao dentro
	sw   $ra, 0($sp)

	jal ler_2param		# Chama a funcao para carregar os parametros em a0 e a1
	mul $t5, $v0, $v1	# Realiza: t5 = v0 * v1
	
	print_str(str_resultado)	# Exibindo o resultado
	print_int($t5)
	print_str(str_endl)
	wait()
	
	
	lw   $ra, 0($sp)	# Desempilha a funcao e retorna
	addi $sp, $sp, 4
	jr $ra
	
# DVIVISAO --------------------------------------------------------------------------
.globl op_div
op_div:
	addi $sp, $sp, -4		# Empilha o $ra, pois vai chamar outra funcao dentro
	sw   $ra, 0($sp)

	jal ler_2param			# Chama a funcao para carregar os parametros em a0 e a1
	div $v0, $v1			# Realiza: t5 = v0 * v1
	mflo $t5			# t5 = Resultado
	mfhi $t6			# t6 = resto
	
	print_str(str_resultado)	# Exibindo o resultado
	print_int($t5)
	print_str(str_endl)
	
	print_str(str_resto)		# Exibindo o resto
	print_int($t6)
	print_str(str_endl)
	wait()
	
	lw   $ra, 0($sp)		# Desempilha a funcao e retorna
	addi $sp, $sp, 4
	jr $ra

	

