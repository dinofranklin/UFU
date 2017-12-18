.data
	strque: .asciiz "Digite o numero para calcular o fatorial: "
	strans: .asciiz "O fatorial eh: "
	
.text

main:
	#Le o numero para calcular o fatorial.
	li $v0, 4
	la $a0, strque
	syscall
	
	li $v0, 5
	syscall
	move $t1, $v0
	
	#Move o valor para a0 (argumento) e chama a funcao fatorial.	
	
	move $a0, $t1
	jal fat
	
	#Move o valor de retorno da funcao (v0) para t2.
	move $t2, $v0
	
	
	#Imprime o resultado calculado.
	
	li $v0, 4
	la $a0, strans
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
		
	#Termina o programa
	li $v0, 10
	syscall
	
#Calcula o fatorial do numero.
fat:
	
	#Pega espaço na pilha e guarda o endereço de chamada e o valor.
	subu $sp, $sp, 8
	sw $ra, ($sp)
	sw $s0, 4($sp)
	
	#Caso o valor seja 0 então retornamos 1 - Caso base.
	li $v0, 1
	beq $a0, 0, retorna
	
	#Guarda o valor de a0 (argumento) em s0, depois diminui 1 de a0 e calcula o fatorial do mesmo.
	move $s0, $a0
	sub $a0, $a0, 1
	jal fat
	
	#Faz a multiplicação.
	mul $v0, $v0, $s0


#Retorna o valor para a funcao.
retorna:
	
	#Pega o endereco do topo da pilha.
	lw $ra, ($sp)
	
	#Pega o valor guardado no topo da pilha.
	lw $s0, 4($sp)
	
	#Adiciona o espaço retirado da pilha.
	addu $sp $sp 8
	
	#Faz o jump pra função que chamou.
	jr $ra
	