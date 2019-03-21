# INSTRUÇÕES IMPORTANTES
# 
# 	MANIPULAÇÃO DA PILHA - COMO EMPILHAR
#	- Reserva "espaço" deslocando o registrador $sp
#	  >> addi $sp, $sp, - <nºpalavras * 4>
#	  Obs. Para alocar espaco subtraia o $sp.
#
#	- Armazena o conteúdo do(s) registrador(es)  / Parametros da função
#	  >> sw $a0, <deslocamento>($sp)
#	     tq. $a0 é o reg que vai ser armazenado
#		 $@storeWord
#
#	- Chamada e retorno do procedimento (função)
#	  >> jal <label>
#	     @jumpAndLink desvia p/ <label> e salva o endereõ de retorno
#	     em $ra (@returnAddress)
#		
#	  >> jr $ra++
#	     @jumpRegister carrega o valor do PC com o conteúdo do $ra
#
#	MANIPULAÇÃO DA PILHA - COMO DESEMPILHAR
#	- Ler o conteúdo da pilha nos registradores
#	  lw $a0, <deslocamento>($sp)
#
#	- Altera a posição do $sp para a ultima piscao da pilha
#	
#
.data
	str_dig:  .asciiz "Digite 1 nº: "
	str_fat:  .asciiz "O fatorial de "
	str_eh:   .asciiz " eh "
	str_erro: .asciiz "Testando ocorrencia de erro\n" 
.text
.globl main

# Macro para facilitar a exibicao de strings
.macro print_str(%str_reg)
	li $v0, 4
	la $a0, %str_reg
	syscall
.end_macro 

main:	#li $v0, 4		# Imprimindo str_dig
	#la $a0, str_dig
	#syscall
	print_str(str_dig)
	
	li $v0, 5		# Lendo o numero (int) em $v0
	syscall
	
	move $a0, $v0		# Salva em $a0 o numero fornecido
	# jal fatorial		# Desvia p/ a função fatorial, que retorna o resultado em $v0
	jal fatorial_recursivo
	move $t1, $v0		# Salva o valor retornado em $t1
	move $t0, $a0		# Salva o valor enviado por parametro em $t0
	
	li $v0, 4		# Exibe "O fatorial de "
	la $a0, str_fat
	syscall
	
	li $v0, 1		# Exibe o numero
	move $a0, $t0
	syscall
	
	li $v0, 4		# Exibe a string " eh "
	la $a0, str_eh
	syscall
	
	li $v0, 1		# Exibe o resultado
	move $a0, $t1
	syscall
	
	li $v0, 10		# Fim do programa
	syscall
	
	
fatorial:
	addi $sp, $sp, -8	# Empilhando o espaço necessário para a funcao
	sw   $a0, 0($sp)	# Salva 1º param. da funcao
	sw   $ra, 4($sp)	# Salva Return Address
	
	addi $v0, $zero, 1      # Resultado a ser calculado 
	addi $t3, $zero, 1	# Valor de parada: $t3 = 1;
	
	loop_fat: ble, $a0, $t3, end_fat	# Loop fatorial: (i = n; i > 1; i--)
		mul  $v0, $v0, $a0
		addi $a0, $a0, -1
		j loop_fat
	end_fat:
	
	lw   $a0, 0($sp)	# Desempilhando o espaço alocado pela função
	lw   $ra, 4($sp)
	addi $sp, $sp, 8
	
	jr $ra			# Voltando para quem chamou a função

fatorial_recursivo:
	addi $sp, $sp -8	# Empilhando o espaço necessário para a funcao
	sw   $a0, 0($sp)	# Salva 1º param. da funcao
	sw   $ra, 4($sp)	# Salva Return Address
	
	# Caso de parada da funcao
	addi $v0, $zero, 1
	beq  $a0, $t1, fim_fatorial_rec
	
	addi $a0, $a0, -1	# return ($a0 * fatorial($a0 - 1));
	jal fatorial_recursivo
	addi $a0, $a0, +1
	mul  $v0, $v0, $a0

fim_fatorial_rec:
	lw   $a0, 0($sp)	# Desempilhando o espaço alocado pela função
	lw   $ra, 4($sp)
	addi $sp, $sp, 8
	
	jr   $ra

# Tratamlento de exceções

.ktext 0x80000180
   move $k0,$v0   # Save $v0 value
   move $k1,$a0   # Save $a0 value
   la   $a0, msg  # address of string to print
   li   $v0, 4    # Print String service
   syscall
   move $v0,$k0   # Restore $v0
   move $a0,$k1   # Restore $a0
   mfc0 $k0,$14   # Coprocessor 0 register $14 has address of trapping instruction
   addi $k0,$k0, -24 # Add 4 to point to next instruction
   mtc0 $k0,$14   # Store new address back into $14
   eret           # Error return; set PC to value in $14
.kdata	
msg:   
   .asciiz "Insira um valor válido.\n"
	










	
	

















