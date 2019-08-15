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
# - Fatorial 

	.data
	.align 0
	
str_dig:	.asciiz "\n\tDigite um numero: "
str_fat:	.asciiz "\tO fatorial de "
str_eh: 	.asciiz " eh "
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
 	
# FATORIAL ------------------------------------------------------------------
	.globl op_fatorial
op_fatorial:
	addi $sp, $sp, -4
	sw   $ra, 0($sp)
	
	print_str(str_dig)	# Lendo o valor do parametro e salvando em $a0

 	li $v0, 5
 	syscall 	
 	move $a0, $v0 		# Passa o numero lido para o argumento da funcao
 				
 	jal fat			# Chama a função recursiva que realiza os cálculos
 	
 	move $t1, $v0  		# salva o retorno em $t1
 	move $t0, $a0   	# salva o numero lido em $t0
 	
 	print_str(str_fat)	
 	
 	print_int($t0)
 	
 	print_str(str_eh)
 	
 	print_int($t1)
 	
 	print_str(str_endl)
 	
 	wait()
 	
	lw   $ra, 0($sp)		# Desempilha a funcao e retorna ao menu
	addi $sp, $sp, 4
	jr $ra

# FAT_RECURSIVO ------------------------------------------------------------------
fat: 
	addi $sp, $sp, -8 		# empilha
	sw   $a0, 0($sp)
	sw   $ra, 4($sp)
	
	addi $t3, $zero, 1 		# comparacao
	addi $v0, $zero, 1 		# fatorial de retorno
	
loop:   ble $a0, $t3, end_loop
	
	mul  $v0, $v0, $a0
	addi $a0, $a0, -1
	
	j loop

end_loop:
	lw $ra, 4($sp) # desempilha
	lw $a0, 0($sp)
	
	addi $sp, $sp, 8
	
	jr $ra   
