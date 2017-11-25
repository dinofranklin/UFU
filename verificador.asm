.text

main:
	#Escaneia o numero.
	li $v0, 4
	la $a0, strask
	syscall
	
	li $v0, 5
	syscall
	move $t0, $v0
	
	#t0 contem o numero e t1 contem o acumulador da multiplicacao.
	#Faz a conta de verificacao com os pesos 8320676
	li $t1, 0
	
	div $t0, $t0, 10
	mfhi $t2
	mul $t2, $t2, 6 #Peso da multiplicacao
	add $t1, $t1, $t2
	
	div $t0, $t0, 10
	mfhi $t2
	mul $t2, $t2, 7 #Peso da multiplicacao
	add $t1, $t1, $t2
	
	div $t0, $t0, 10
	mfhi $t2
	mul $t2, $t2, 6 #Peso da multiplicacao
	add $t1, $t1, $t2
	
	div $t0, $t0, 10
	mfhi $t2
	mul $t2, $t2, 0 #Peso da multiplicacao
	add $t1, $t1, $t2
	
	div $t0, $t0, 10
	mfhi $t2
	mul $t2, $t2, 2 #Peso da multiplicacao
	add $t1, $t1, $t2
	
	div $t0, $t0, 10
	mfhi $t2
	mul $t2, $t2, 3 #Peso da multiplicacao
	add $t1, $t1, $t2
	
	div $t0, $t0, 10
	mfhi $t2
	mul $t2, $t2, 8 #Peso da multiplicacao
	add $t1, $t1, $t2
	
	#Divisao por 11 para calcular o digito vericador.
	div $t1, $t1, 11
	mfhi $t2
	li $t3, 11
	
	#Subtrai o resultado de 11.
	sub $t2, $t3, $t2
	
	li $v0, 1
	add $a0, $t2, $zero
	syscall

.data

strask: .asciiz "Digite um numero de 7 digitos: "
strans: .asciiz "O digito verificador da sequencia eh: "