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
# - Menu de seleção da operação.
# - Funções gerais para entrada e saída de dados
# - Configurações para lidar com Throws Exceptions

# Configurações gerais do projeto
# - $a0 à $a3 usados para passar parâmetros
# - $v0 e $v1 usados para passar resultados
# - $t0 à $t4 usados como iteradores de loops
# - $t5 à $t9 usados como auxiliares para salvar dados

# Para ativar a linker de multiplos arquivos:
# 1º - Abra o MARS
# 2º - No menu superior vá em Settings
# 3º - Marque a opção "Assemble all files in directory"
# 4º - Faça o Assemble (F3) sempre no seu arquivo main

.data
	.align 0
	# Strings usadas na estrutura do Menu
	str_linha:	.asciiz "\t******************************************\n"
	str_menu:	.asciiz	"\t*   MENU DA CALCULADORA                  *\n"
	str_opt1:	.asciiz	"\t*   1 - Soma          (a+b)              *\n"
	str_opt2:	.asciiz	"\t*   2 - Subtracao     (a-b)              *\n"
	str_opt3:	.asciiz	"\t*   3 - Multiplicacao (a*b)              *\n"
	str_opt4:	.asciiz	"\t*   4 - Divisao       (a/b)              *\n"
	str_opt5:	.asciiz	"\t*   5 - Potencia      (a^b)              *\n"
	str_opt6:	.asciiz	"\t*   6 - Raiz quadrada (sqrt(a))          *\n"
	str_opt7:	.asciiz	"\t*   7 - Fatorial      (a!)               *\n"
	str_opt8:	.asciiz	"\t*   8 - Fibonacci     (a,b)              *\n"
	str_opt9:	.asciiz	"\t*   9 - Ver tabuada                      *\n"
	str_opt10:	.asciiz	"\t*  10 - Calcular IMC                     *\n"
	str_opt0:	.asciiz	"\t*   0 - Sair da calculadora              *\n"
	
	str_escolhe:	.asciiz "\n\tDigite o numero da operacao desejada: "
	str_opt_ne:	.asciiz "\n\tCodigo de operacao incorreto, por favor selecione novamente....\n"
	
	# String usada na leitura de dois parametros
	str_param1:	.asciiz	"\n\tInsira o primeiro valor: "
	str_param2:	.asciiz "\tInsira o segundo valor: "
	
	# String usada na leitura de parametro unico
	str_param:	.asciiz "\n\tInsira um valor: "
	
	# String usada no calculo do IMC
	str_peso:	.asciiz "\n\tInsira o seu peso: "
	str_altura:	.asciiz "\tInsira a sua altura: "
	
	# Strings de erros nas leituras
	str_invalid:	.asciiz "\n\tValor inválido, por favor insira os dados novamente.\n"


# MACRO print_str() ------------------------------------------------------------
	.macro print_str(%str_label)
		li $v0, 4
		la $a0, %str_label
		syscall
	.end_macro

.text
.globl menu

# MENU --------------------------------------------------------------------------
menu: 
	print_str(str_linha)
	print_str(str_menu)		# Mostrando o menu para o usuario
	print_str(str_linha)
	print_str(str_opt1)
	print_str(str_opt2)
	print_str(str_opt3)
	print_str(str_opt4)
	print_str(str_opt5)
	print_str(str_opt6)
	print_str(str_opt7)
	print_str(str_opt8)
	print_str(str_opt9)
	print_str(str_opt10)
	print_str(str_opt0)
	print_str(str_linha)
	

menu_ler_op:
	print_str(str_escolhe)		# Lendo a opcao do teclado e salvando em $t5
	li $v0, 5			
	syscall
	move $t5, $v0
	
	addi $t1, $zero, 1		# t1 será o reg. auxiliar para fazer as comparacoes
case1:	bne  $t5, $t1, case2		# Implementa um switch(t1){ Case 1, Case 2 ... Case 10, Case 0, Default } 
		jal op_soma
		j menu
	
case2:	addi $t1, $t1, 1
	bne  $t5, $t1, case3
		jal op_sub
		j menu
		
case3:	addi $t1, $t1, 1
	bne  $t5, $t1, case4
		jal op_mult
		j menu

case4:	addi $t1, $t1, 1
	bne  $t5, $t1, case5
		jal op_div
		j menu

case5:	addi $t1, $t1, 1
	bne  $t5, $t1, case6
		jal op_potencia
		j menu

case6:	addi $t1, $t1, 1
	bne  $t5, $t1, case7
		jal op_sqrt
		j menu

case7:	addi $t1, $t1, 1
	bne  $t5, $t1, case8
		jal op_fatorial
		j menu

case8:	addi $t1, $t1, 1
	bne  $t5, $t1, case9
		jal op_fibonacci
		j menu

case9:	addi $t1, $t1, 1
	bne  $t5, $t1, case10
		jal op_tabuada
		j menu

case10:	addi $t1, $t1, 1
	bne  $t5, $t1, case0
		jal op_imc
		j menu

case0:	beq  $t5, $zero, op_fechar
	
	print_str(str_opt_ne)			# Caso o usuario insira um codigo de operacao Nao Existente [NE]
	j menu_ler_op
	
	
	
# FIM DO PROGRAMA --------------------------------------------------------------
op_fechar:
	li $v0, 10
	syscall
	

# LER 2 INTEIROS ---------------------------------------------------------------
.globl ler_2param
ler_2param:
	print_str(str_param1)
	li $v0, 5	# Lê o primeiro valor e salva temporariamente em t5
	syscall
	move $t5, $v0
	
	print_str(str_param2)
	li $v0, 5	# Lê o segundo valor e ajusta para que:
	syscall		# v0 <- Primeiro input
	move $v1, $v0	# v1 <- Segundo input
	move $v0, $t5
	
	jr $ra
	
	
# LER 1 INTEIRO ----------------------------------------------------------------
.globl ler_1param
ler_1param:
	print_str(str_param)	# Lê o inteiro, salva em v0 e retorna a funcao
	li $v0, 5
	syscall
	
	jr $ra

# LER 1 FLOAT - ----------------------------------------------------------------
.globl ler_1float
ler_1float:
	print_str(str_param)	# Lê o float e salva em $f0
	li $v0, 6
	syscall
	
	jr $ra
	
	
# LIDANDO COM ERROS DE EXCEPTION -----------------------------------------------

.ktext 0x80000180
	print_str(str_erro1)	# Exibe as mensagens de erro
	print_str(str_erro2)
	print_str(str_erro3)
	
	li $v0, 12		# Leitura de char apenas para o usuario ler o erro
	syscall
   
	mfc0 $k0, $14   	# Move para o registrador k0 o endereco da instrucao que causou o erro salvo em $14		
   	la   $k0, menu 		# Nao localizou, volta para o menu
   	mtc0 $k0, $14   		# Salva o endereco de retorno que esta em $k0 em $14
   	eret           		# Seta o valor do PC para o valor salvo em $14
.kdata	
	str_erro1:	.asciiz	"\n\tEssa nao...Ocorreu um erro no processo atual!\n"
	str_erro2:	.asciiz "\tVerifique se os dados pedidos foram inseridos corretamente e refaça a operação\n"
	str_erro3:	.asciiz "\tPressione ENTER para voltar ao menu.\n"

	
	


	
		
			
				
						









