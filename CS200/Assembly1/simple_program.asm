#CS200-01
#Homework One - Simple Program
#Richard McCormick
#rlm443

.data
	ask1: .asciiz "Enter first number: "
	ask2: .asciiz "Enter second number: "
	ask3: .asciiz "Enter third number: "
	resl: .asciiz "The result is: "

.text
main:
	li $v0, 4 	#get ready to print a string (1)
	la $a0, ask1 	#load argument register with first prompt
	syscall 	#execute (print prompt)

	li $v0, 5 	#get ready to read a string (1)
	syscall 	#execute (read answer1)
	move $t1, $v0 	#take string, store in register 1
	
	li $v0, 4	#get ready to print a string (2)
	la $a0, ask2	#load prompt two into arg register
	syscall		#execute (print prompt2)

	li $v0, 5	#get ready to read answer (2)
	syscall		#execute (read answer2)
	move $t2, $v0	#store answer in register 2

	li $v0, 4	#get ready to print a string (3)
	la $a0, ask3	#load arg register with final prompt
	syscall		#execute (print prompt3)

	li $v0, 5	#read final answer (3)
	syscall		#execute (read answer3)
	move $t4, $v0	#load register 4 with answer 3

	sub $t3, $t1, $t2	#subtract num2 from num1, store in register 3
	add $t5, $t4, $t3	#add the result in register 3 to num3, store in register 5

	li $v0, 4	#get ready to print string
	la $a0, resl	#load arg with result string
	syscall		#execute (print result string)

	li $v0, 1	#get ready to print an integer
	move $a0, $t5	#load arg register with answer in register 5
	syscall		#execute (print answer as integer)

	li $v0, 10	#get ready to end program
	syscall		#execute