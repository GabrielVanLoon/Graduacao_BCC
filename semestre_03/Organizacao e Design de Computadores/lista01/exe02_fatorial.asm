.data
	.align  0
	str_dig:	.asciiz "Digite um numero >= 0: "
	str_result:	.asciiz "Resultado: "
.text
.globl 	main

main:
	li $v0, 4		# Print(str_digt)
	la $a0, str_dig
	syscall
	
	li  $v0, 5		# Lendo o inteiro em a0
	syscall			
	move $a0, $v0
	
	jal fatorial		# Chama a funcao e salva o retorno
	move $t0, $v0		# em t0
	
	li $v0, 4		# Imprime str_result
	la $a0, str_result
	syscall
	
	li   $v0, 1		# Imprime o resultado
	move $a0, $t0
	syscall
	
	li $v0, 10		# fim do programa
	syscall
	
fatorial:
	addi $sp, $sp, -8
	sw   $ra, 0($sp)
	sw   $a0, 4($sp)
	
	ble $a0, $zero, fat_parada	# Se (n > 0) return n * fatorial(n-1)
		addi $a0, $a0, -1
		jal fatorial
		addi $a0, $a0, +1

		mult $a0, $v0 
		mflo $v0
		j fim_fatorial
		
	fat_parada:			# Se (n==0) return 1
		li $v0, 1
		j  fim_fatorial
		
fim_fatorial:
	lw   $ra, 0($sp)
	lw   $a0, 4($sp)
	addi $sp, $sp, 8
	jr $ra
	
	
	
	