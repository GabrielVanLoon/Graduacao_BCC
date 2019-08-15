# TRABALHO DE ORGANIZAÇÃO E ARQUITETURA DE COMPUTADORES
# Título:	Calculadora em Assembly MIPS
# Profª.:	Sarita
# Data:		março/2019
#
# Membros:	Débora Buzon da Silva
#		Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
#		Mathias Fernandes
#		Tamiris Tinelli

# Esta implementado nesse arquivo:
# - Cálculo do IMC
# - Cálculo da potencia de um inteiro


.data		
	.align 0
	# Strings para o IMC
	strpeso: 	.asciiz "\n\tDigite seu peso (kg): "
	stralt: 	.asciiz "\tDigite sua altura (m): "
	strimc: 	.asciiz "\tSeu IMC atual eh "
	
	# Strings para a potencia
	strbase:	.asciiz "\n\tDigite a base: "
	strexp:		.asciiz "\tDigite o expoente: "
	strres:		.asciiz "\tO resultado eh "
	
	str_endl:	.asciiz "\n"
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

# CALCULO IMC ----------------------------------------------------------------
.globl op_imc
op_imc:		
		addi $sp, $sp, -4		# Aloca 4 bytes na pilha.
		sw $ra, ($sp) 			# Salva chamada do procedimento.

		addi $v0, $zero, 4	#imprime a strpeso
		la $a0, strpeso
		syscall

		li $v0, 6		#le o peso - armazena em f1
		syscall
		mov.s $f1, $f0

		addi $v0, $zero, 4	#imprime a stralt
		la $a0, stralt
		syscall

		li $v0, 6		#le a altura - armazena em f2
		syscall
		mov.s $f2, $f0

		mul.s $f2, $f2, $f2	#multiplica altura x altura
		div.s $f0, $f1, $f2	#divide peso por altura quadrada

		addi $v0, $zero, 4	#imprime resposta
		la $a0, strimc
		syscall
		
		addi  $v0, $zero, 2
		mov.s $f12, $f0
		syscall

		addi $v0, $zero, 4	#imprime fim de linha
		la $a0, str_endl
		syscall
		
		wait()
		lw $ra, ($sp)		# desaloca os 4 bytes da pilha.
		addi $sp, $sp, 4		
		jr $ra			# retorna para a chamada.


# POTENCIA ----------------------------------------------------------------
.globl op_potencia
op_potencia:	
		addi $sp, $sp, -4		# Aloca 4 bytes na pilha.
		sw $ra, ($sp) 			# Salva chamada do procedimento.
		
		addi $v0, $zero, 4	#imprime a strbase
		la $a0, strbase
		syscall

		li $v0, 6		#le a base - armazena em f1
		syscall
		mov.s $f1, $f0

		addi $v0, $zero, 4	#imprime a strexp
		la $a0, strexp
		syscall

		li $v0, 5		#le o expoente
		syscall
		move $a0, $v0

		addi $t0, $zero, 1	#faz a conta - resposta em f2
		mov.s $f2, $f1
		
for:
		beq $t0, $a0, sai_loop
		
		mul.s $f2, $f2, $f1
		addi $t0, $t0, 1
		j for
		
sai_loop:
		
		addi $v0, $zero, 4	#imprime resposta
		la $a0, strres
		syscall
		
		addi $v0, $zero, 2
		mov.s $f12, $f2
		syscall
		
		addi $v0, $zero, 4	#imprime fim de linha
		la $a0, str_endl
		syscall
		
		wait()
		lw $ra, ($sp)			# desaloca os 4 bytes da pilha.
		addi $sp, $sp, 4		
		jr $ra				# retorna para a chamada.
