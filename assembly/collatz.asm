#Nome: Arthur Borges Duarte.
#Matricula: 11711BCC014.

.text
	main:
		#Escaneia o numero.
		li $v0, 4
		la $a0, strask
		syscall
		
		li, $v0, 5
		syscall
		move $t0, $v0
		
		#Testa se o numero informado eh maior do que zero.
		bgtz $t0, collatz
		
		#Caso nao seja, chama a main novamente.
		li $v0, 4
		la $a0, strerr
		syscall
		j main
	
	#Usada para calcular e imprimir a sequencia de collatz.
	collatz:
		#Pula para o procedimento para imprimir o numero e faz o link para retornar.
		bgezal $t0, imprimenum
		
		#Calcula o resto da divisao por dois e chama o procedimento.
		div $t2, $t0, 2
		mfhi $t1
		
		#Multiplica-se o resto por -1.
		mul $t1, $t1, -1
		
		#Caso seja -1 o numero eh impar.
		bltzal $t1, impar	
		#Do contrário o numero eh par.
		bgezal $t1, par
		
		#Se o novo numero for igual a 1 o programa termina, senao collatz eh chamado novamente.
		bgt $t0, 1, collatz
		
		jal imprimenum
		li $v0, 10
		syscall
	
	#Faz o procedimento para o numero par (*2).
	par:		
		div $t0, $t0, 2
		jr $ra
	
	#Faz o procedimento para o numero impar (*3 + 1).
	impar:
		mul $t0, $t0, 3
		add $t0, $t0, 1
		jr $ra
	
	imprimenum:
		#Imprime o numero.
		li $v0, 1
		addi $a0, $t0, 0
		syscall
		
		#Imprime o separador.
		li $v0, 4
		la $a0, strsep
		syscall
		
		jr $ra
		
.data

strask: .asciiz "Digite um numero natural diferente de 0: "
strsep: .asciiz "; "
strerr: .asciiz "Digite um numero valido (>=0)\n"
strtes: .asciiz "  -> Seu numero eh esse\n"
