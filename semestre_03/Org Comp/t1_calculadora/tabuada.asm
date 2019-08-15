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
# - Tabuada de um Número inteiro

# tabuada de um numero
.data
	.align 0
	str_tabuada: .asciiz "\t# Tabuada do nº "
	str_divLin: .asciiz "\t--------------------------------\n"
	str_proxLinha: .asciiz "\n"
	str_tab: .asciiz "\t   "
	
	str_x: .asciiz " x "
	str_igual: .asciiz "\t=\t"
	
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

# TABUADA -------------------------------------------------------------------------
	.globl op_tabuada
	
	op_tabuada: 
			addi $sp, $sp, -4		# Aloca 4 bytes na pilha.
			sw $ra, ($sp) 			# Salva chamada do procedimento.

			jal ler_1param			# Faz a leitura de um parametro e salva no $s0.
			add $s0, $zero, $v0
			
			addi $t0, $zero, 1		# i = 1.
			addi $t1, $zero, 11		# j = 11, caso parada.
			
			# header da opcao + numero digitado.
			print_str(str_divLin)
			print_str(str_tabuada)		
			print_int($s0)		
			print_str(str_proxLinha)		
			print_str(str_proxLinha)
			
			# calculo da tabuada	
			fori: beq $t0, $t1, fim_fori		# se i == 11, fim da tabuada.
				mul $t2, $s0, $t0
				
				print_str(str_tab)			# Imprime o tab da linha
				print_int($s0) 				# imprime numero base.
				print_str(str_x)			# imprime sinal 'X'.
				print_int($t0)				# imprime em qual operacao esta.
				print_str(str_igual)			# imprime sinal '='.
				print_int($t2)				# imprime resultado.
				
				addi $t0, $t0, 1			# proxima iteracao i = i + 1.
				print_str(str_proxLinha)		# imprime linha vazia.
				
				j fori				
			
		fim_fori:
			print_str(str_divLin)		# footer da opcao.
			print_str(str_proxLinha)
			wait()	
				
			lw $ra, ($sp)			# desaloca os 4 bytes da pilha.
			addi $sp, $sp, 4		
			jr $ra				# retorna para a chamada.
