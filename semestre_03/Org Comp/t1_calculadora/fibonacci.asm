# TRABALHO DE ORGANIZAÇÃO E ARQUITETURA DE COMPUTADORES
# Título:	Calculadora em Assembly MIPS
# Profª.:	Sarita
# Data:		março/2019
#
# Membros:	Débora Buzon da Silva
#		Gabriel Van Loon Bode da Costa Dourado Fuentes Rojas
#		Mathias Fernandes
#		Tamiris Tinelli

# Estão nesse arquivo:
# - Fibonacci de (a, b)

	.data
	.align 0
	
str_range:	.asciiz "\n\tDigite o intervalo (a, b) a ser mostrado... \n"
str_valA:	.asciiz "\tInsira o valor de a: "
str_valB:	.asciiz "\tInsira o valor de b: "
str_space:	.asciiz " "
str_tab:	.asciiz "\tSequencia: "
str_endl: 	.asciiz "\n"

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
	
# FIBONACCI -----------------------------------------------------------------
	.globl op_fibonacci
op_fibonacci:
	addi $sp, $sp, -4	# Empilhando o caminho de retorno
	sw   $ra, 0($sp)
	
	print_str(str_range)	# Lendo os valores do intervalo
	
	print_str(str_valA)		
	li $v0, 5		# t0 <- a (Valor a do Intervalo)
	syscall
	move $t0, $v0	
	
	bgt $t0, $zero, valA_valido	# Tratando valores negativos 
		addi $t0, $zero, 0  
	valA_valido:
	
	print_str(str_valB)
	li $v0, 5		# t1 <- b (Valor b do intervalo)
	syscall
	move $t1, $v0 	
	
	bgez $t1, valB_valido	# Tratando valores negativos 
		addi $t1, $zero, -1  
	valB_valido:
	
	print_str(str_tab)	# Tab antes do resultado
	
	move $a0, $t1		# A funçao fib(x) retorna o valor do Xº elemento do fibonacci
	move $a1, $t0		# e retorna esse valor em $v0.
	move $a2, $t1		
	jal fib			
				
	print_str(str_endl)	
	wait()		
	
	lw   $ra, 0($sp)	# Desempilhando a função
	addi $sp, $sp, 4
	jr $ra
	
	
# FIBONACCI RECURSIVA -----------------------------------------------------------------
fib:
	addi $sp, $sp, -16	# Empilhando os parametros da funcao ou registradores
	sw $ra,  0($sp)		# que serão modificados pela função abaixo:
	sw $a0,  4($sp)		# a0 -> i-ésimo item do fibonacci
	sw $a1,  8($sp)		# a1 -> valor 'a'
	sw $a2, 12($sp)		# a2 -> valor 'b'
			
	addi $v0, $zero, 0 	# valor de retorno base
	addi $v1, $zero, 1 	# valor de retorno base
	
	addi $t3, $zero, 1	# comparacao brench
	ble  $a0, $t3, end_fib	# Caso de parada: i <= 1º elemento 	
	
		addi $a0, $a0, -1 	# seta args da chamada recursiva para n-1
		jal fib
		addi $a0, $a0, 1	# resenta o valor de i para o n atual
		
		add  $t5, $v0, $v1	# calcula o i-ésimo elemento com v0 e v1	
		move $v0, $v1		# sendo que:
		move $v1, $t5 		# $v0 -> fib(i-2)
					# $v1 -> fib(i-1)
					 
end_fib:
	
	blt $a0, $a1, nao_printa	# Printa o valor se, e somento se, (a <= i <= b)
	bgt $a0, $a2, nao_printa	
		
		move $t5, $v0	# salva os valores de $v1 e $v0 pois vamos usar nos syscalss
		move $t6, $v1
		
		print_int($v1)		
		print_str(str_space)
		
		move $v0, $t5	# restaura $v0 e $v1
		move $v1, $t6
		
nao_printa:
	
	lw $ra,  0($sp)		# Restaurando os parametros da funcao
	lw $a0,  4($sp)		
	lw $a1,  8($sp)		
	lw $a2, 12($sp)		
	
	addi $sp, $sp, 16
	jr $ra
