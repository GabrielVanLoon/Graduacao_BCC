.data
	.align 0
	str_entreTam:	.asciiz "Entre com o tamanho do vetor: "
	str_digNum:	.asciiz "Digite um numero: "
	
	
.text
.globl main
main:
	li $v0, 4		# "Digite o tam do array"
	la $a0, str_entreTam	
	syscall
	
	li $v0, 5		#Lendo o numero e salvando em s0
	syscall			
	add $s0, $zero, $v0
	
	addi $t0, $zero, 4	# calcula espaço para alocar e salva em t1
	mult $t0, $s0
	mfhi $t1
	
	addi $v0, $zero, 9	# Aloca a memoria em salva em s1 o endereço inicial
	add  $a0, $zero, $t1
	syscall
	add $s1, $zero, $v0
	
	addi $t0, $zero, 0 	# Contador do loop
	add  $t1, $zero, $s1	# Endereço para salvar o numero
loop:	beq $t0, $s0, end_loop	# Loop para ler o vetor
		
		li $v0, 5	# Lendo e salvando o numero na memoria alocada
		syscall
		sw $v0, ($t1)
		
		addi $t1, $t1, 4
		addi $t0, $t0, 1
		j loop
end_loop:

	addi $t0, $zero, 0 	# Contador do loop
	add  $t1, $zero, $s1	# Endereço para salvar o numero
print:	beq $t0, $s0, end_print	# Loop para ler o vetor
		
		li $v0, 1	# printando
		lw $a0, ($t1)
		syscall
		
		addi $t1, $t1, 4
		addi $t0, $t0, 1
		j print
end_print:

	addi $t0, $zero, 0 	# Contador do loop
	add  $t1, $zero, $s1	# Endereço para salvar o numero
sorti:	beq $t0, $s0, endi
		
		lw $t8, 0($t1)	# t8 = vet[i]
		
		addi $t2, $t0, 1 # j = i+1
		addi $t3, $t1, 4 # n[j]
	sortj: 	beq $t2, $s0, endj
		
		lw  $t9, 0($t3)		# #t9 = vet[j]
		sub $t5, $t9, $t8	# t5 = t9 - t8
		
		bgez $t5, nao_swap
			sw $t8, 0($t3)		# t9 < t8, realiza o swap na memoria
			sw $t9, 0($t1)
			add $t8, $zero, $t9	# atualiza o registrador t8
		nao_swap:
			
		addi $t2, $t2, 1 # j
		addi $t3, $t3, 4 # n[j]
		j sortj
	endj:	
	
	addi $t0, $t0, 1 	
	addi $t1, $t1, 4
	j sorti
endi:

	addi $t0, $zero, 0 	# Contador do loop
	add  $t1, $zero, $s1	# Endereço para salvar o numero
print2:	beq $t0, $s0, end_print2	# Loop para ler o vetor
		
		li $v0, 1	# printando
		lw $a0, ($t1)
		syscall
		
		addi $t1, $t1, 4
		addi $t0, $t0, 1
		j print2
end_print2:

	addi $v0, $zero, 10	# Finaliza o programa
	syscall
		
