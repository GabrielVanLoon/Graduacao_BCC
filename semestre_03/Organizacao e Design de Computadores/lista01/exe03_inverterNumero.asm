.data	
	.align 0
	str_dig:	.asciiz "Digite um numero: "
	str_inv:	.asciiz "Número invertido: "
	
.text
.globl main

main:	li $v0, 4		# Printando string
	la $a0, str_dig
	syscall
	
	li $v0, 5		# Lendo o numero e salvando em s0
	syscall
	move $s0, $v0
	
	addi $s1, $zero, 0	# s1 sera onde vamos salvar o numero inverso
	addi $t0, $zero, 10	# t1 = 9 (registrador auxiliar)

loop:	blez  $s0, fim_loop		# Para o loop quando $s0 <= 0
		
		div  $s0, $t0	
		mflo $s0 		# s0 = s0 / 10
		mfhi $t1		# t1 = s0 % 10
		
		add  $s1, $s1, $t1	# s1 = s1 + t1
		mult $s1, $t0		
		mflo $s1 		# s1 = s1 * 10  (Prepara para receber o prox numero)
		
		j loop
fim_loop:
	div  $s1, $t0		# Ajustando a multiplicação remanscente no numero
	mflo $s1
	
	li $v0, 4		# Printando string
	la $a0, str_inv
	syscall
	
	li   $v0, 1		# Printando string
	move $a0, $s1
	syscall
 	
 	li $v0, 10		# Fim do programa
 	syscall
   