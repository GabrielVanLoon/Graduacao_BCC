.data
	.align 0
	str1:		.ascii "Seja muito bem vindo \0"	# Primeira string
	str1_extra:	.space 40			# 20 espaços para aumentar a str1
	str2:		.space 40
	str_dig:	.asciiz "Digine uma string de até 40 caracteres: "
	str_concat:	.asciiz "String concatenada: "
.text
.globl main

main:
	li $v0, 4		# Pedindo para entrar com uma string
	la $a0, str_dig
	syscall
	
	li $v0, 8		# Lendo str2 com no max 40 caracteres
	la $a0, str2
	li $a1, 40
	syscall
	
	la $a0, str1
	la $a1, str2
	jal strcat
	
	li $v0, 4 
	la $a0, str_concat
	syscall
	
	li $v0, 4
	la $a0, str1
	syscall
	
	li $v0, 10		# Fim do programa
	syscall	


strcat:	
	addi $sp, $sp -12	# Empilhando as variaveis
	sw   $ra, 0($sp)	# $ra: registro de retorno
	sw   $a0, 4($sp)	# $a0: ptr str1
	sw   $a1, 8($sp)	# $a1: ptr str2
	
	loop1:			# Atualize a0 até apontar para \0 da str1
		lb  $t0,  0($a0) 
		beq $t0, $zero, fim_loop1
			addi $a0, $a0, 1
			j loop1
	fim_loop1:
	
	loop2:			# Copia str2 no final de str1
		lb  $t0, 0($a1)
		beq $t0, $zero, fim_loop2
			sb   $t0, 0($a0)
			addi $a0, $a0, 1
			addi $a1, $a1, 1 
			j loop2
	fim_loop2:
	sb $zero, 0($a0) 	# Inserindo o novo \0
	
	lw   $ra, 0($sp)	# $ra: registro de retorno
	lw   $a0, 4($sp)	# $a0: ptr str1
	lw   $a1, 8($sp)	# $a1: ptr str2
	addi $sp, $sp +12	# Empilhando as variaveis
	jr $ra
	
	