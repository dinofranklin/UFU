.text

main:
	
	#Escaneando os dois numeros:
	li $v0, 4
	la $a0, str1
	syscall

	li $v0, 5
	syscall
	move $t1, $v0
	
	li $v0, 4
	la $a0, str2
	syscall
	
	li $v0, 5
	syscall
	move $t2, $v0
	
	#Multiplica os numeros e imprime o resultado:
	mul $t0, $t1, $t2
	
	li $v0, 1
	move $a0, $t1
	syscall
	
	li $v0, 4
	la $a0, auxmult
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	li $v0, 4
	la $a0, auxequal
	syscall
	
	li $v0, 1
	move $a0, $t0
	syscall
	
	li $v0, 11
	li $a0, '\n'
	syscall 
	
	#Divide os numeros e imprime o resultado inteiro:
	div $t0, $t1, $t2
	
	li $v0, 4
	la $a0, strdiv
	syscall
	
	li $v0, 1
	move $a0, $t1
	syscall
	
	li $v0, 4
	la $a0, auxdiv
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	li $v0, 4
	la $a0, auxequal
	syscall
	
	li $v0, 1
	move $a0, $t0
	syscall
	
	li $v0, 11
	li $a0, '\n'
	syscall 
	
	#Encontra e imprime o resto da divisao:
	li $v0, 4
	la $a0, strmod
	syscall
	
	li $v0, 1
	move $a0, $t1
	syscall
	
	li $v0, 4
	la $a0, auxdiv
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	li $v0, 4
	la $a0, auxequal
	syscall
	
	li $v0, 1
	mfhi $a0
	syscall
	
.data

str1: .asciiz "Num1 = "
str2: .asciiz "Num2 = "
strdiv: .asciiz "Parte inteira de "
strmod: .asciiz "Resto inteiro de "
auxmult: .asciiz " x "
auxdiv: .asciiz " / "
auxequal: .asciiz " = "
