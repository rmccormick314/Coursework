.data
space: .asciiz " "
msg_min: .asciiz "The min is: "
msg_max: .asciiz "The max is: "

intArray: .word 5, 7, 12, 3, 4, 9, 6, 11, 2, 10 #Array of 10 elements
num: .word 10					#Number of elements

.text
main:   la $a0, intArray       			#Initializes array
    	lw $a1, num       			#$a1=10  --number elements
    	
    	li $t2, 0				#Sets max = 0
    	li $t3, 100				#Sets min = 100
    	
    	jal traverseArray  			#Calls traverseArray
    	li $v0, 10      			#Exits program   
    	syscall 
    	
    	
traverseArray:
    li $t0, 0       				#Accumulator = 0
    li $t1, 0       				#Index = 0
    
loop:    bge $t0, $a1, final 			#If  $t0 >= $a1 then go to final
    lw $a0, intArray($t1) 				#$a0 = intArray[i]
    
    blt $a0, $t3, new_min			#If intArray[i] < min
    j check_max
    new_min: move $t3, $a0			#Min = intArray[i]
    j update_counter
    
    check_max:
    bgt $a0, $t2, new_max			#If intArray[i] > max
    j update_counter
    
    new_max: move $t2, $a0			#Max = intArray[i]
    
    update_counter:
    addi $t1, $t1, 4    		#Every 4 bytes there is an integer in the array
    addi $t0, $t0, 1    		#Accumulator ++
    b loop       			#Go to loop
final:  			

	la $a0, msg_max   	#Load a max message
    	li $v0, 4       	#Print string               
    	syscall

	li $v0, 1		#Prints integer
	move $a0, $t2		#Loads the max to be printed
	syscall

	la $a0, space   	#load a space:  " "
    	li $v0, 4       	#print string               
    	syscall
	
	la $a0, msg_min   	#Loads min message
    	li $v0, 4       	#Prints string               
    	syscall

	li $v0, 1		#Prints integer
	move $a0, $t3		#Loads the min to be printed
	syscall			#Executes the print

    	jr $ra      		#return