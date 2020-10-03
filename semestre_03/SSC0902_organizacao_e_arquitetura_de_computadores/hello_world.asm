# Organização e Arquitetura de Computadores
# Prof.: Sarita
# Autor: Gabriel Van Loon
#
# Projeto: Hello World em Assembly


# .data: 
.data
.align 0
	str_hello:	.asciiz "Hello World!"
	str_dig:	.asciiz "Digite um inteiro: "
 	str_neg:	.asciiz "Valor negativo >> "
 	str_pos:	.asciiz "Valor positivo >> "
 .text
 .globl main
 main:	# EXIBINDO O HELLO WORLD
 	li $v0, 4	# @loadImediatte: Carrega ID do Syscall.
 	la $a0, str_dig	# @loadAdress:    Carrega endereco do inicio da str.
 	syscall		# Syscall 4: print string.
 	
 	# EXIBE MENSAGEM PEDINDO PARA LER NUMERO INTEIRO
 	li $v0, 5	# Syscall 5: Le um numero e salva o valor lido
 	la $a0, str_dig # no proprio registrador $v0.
 	syscall		#
 	move $t5, $v0   # Salva o inteiro lido no registrador temporario $t5
 	
 	# CRIANDO UM JUMP CONDICIONAL
 	slt $t0, $t5, $zero # @setLessThen: Se ($t5 < $zero) faz $t0 <- 1 senao $t0 <- 0
 	li $t1, 1	    # $t1 vai auxiliar na hora da comparacao
 	
 	beq $t0, $t1, print_neg 
 		li $v0, 4	# Caso seja um valor positivo
 		la $a0, str_pos
 		syscall
 		j fim_print	# Caso seja um valor negativo
 	print_neg:
 		li $v0, 4
 		la $a0, str_neg
 		syscall
 	fim_print:		
 	
 	# EXIBINDO O NUMERO DIGITADO
 	li $v0, 1	#Syscall 4: exibir numero inteiro armazenado em $a0
 	move $a0, $t5	
 	syscall	
 	
 	# Syscall 10: ENCERRANDO O PROGRAMA
 	li $v0, 10
 	syscall 
 	
 	
 	
 	                    
 	                    
 	                    
 	                    
 	                    
 	