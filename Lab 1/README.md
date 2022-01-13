# Lab 1
*Note: Mixture of swedish and english*
## Assignment 1

Start Code:
```assembly
addi	$s0,$s0,1
li	    $t0,0x5b
```

Which lines of code had to be changed? Why?
```assembly
addi	$s0,$s0,3
li	    $t0,0x5D
```

Ändrade 1 till en 3 för att skippa vad tredje karaktär. Vi ändrade även på t0 så att den skulle hoppa ut på rätt tillfälle.

## Assignment 2
```
hexasc:
	add $t0, $zero, $zero
	li $t0, 0x0f
	and $a0, $t0, $a0
    
	la $v0, ($a0)
	slti $t1, $a0, 10
	beq $t1, 1, number
	beq $t1, 0, letter
    
number:
	addi $v0, $v0, 0x30numret
	jr $ra
letter:
	addi $v0, $v0, 0x37
	jr $ra
```

1.	Your subroutine hexasc is called with an integer-value as an argument in register $a0, and returns a return-value in register $v0. If the argument is 17, what is the return-value? Why?

Resultatet blir ett genom att vi lägger ihop talet 17 med 0f med hjälp av AND. Detta ger att vi får ut 0001 vilket är 1.

2.	If your solution contains a conditional-branch instruction: which input values cause the instruction to actually branch to another location? This is called a taken branch.

Med hjälp av ett villkor så kan vi lätt bestämma om det vi vill får ut är mellan 0-9 eller 10-15 vilket sedan konverteras till ascii så att vi får ut bokstäverna a-f 

## Assignment 3
```
time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1
	la $s1, $a1
    la $s0, $a0	

	#Add null-byte to the end of $a0
	la $t5, 0x00
	sb $t5, 5($s0)
	
	#First iteration store last digit in adress 5($a0)
	la $a0, ($s1)
	jal hexasc
	nop
	sb $v0, 4($s0)
	 
	#Second iteration store second to last digit in adress 4($a0)

	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	sb $v0, 3($s0)
	
	#Add ':' to middle
	la $t5, 0x3a
	sb $t5, 2($s0)
	
	#Fourth iteration store Second digit in address 1($a0)
	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	sb $v0, 1($s0)
	
	#Fifth iteration store first digit in address 0($a0)
	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	
	sb $v0, 0($s0)

	POP $s1
	POP $s0
	POP $ra
	jr $ra
	nop
```


1.	Which registers are saved and restored by your subroutine? Why?

The registers that are saved are $ra, $s1 and $s0. This is because when the subroutine is called with the jal function the register $ra stores the address of the next instruction from where jal was called. Because time2string subroutine also uses a subroutine it means that the address that $ra holds will be overwritten if not pushed to the stack. The reason for why $s0 is saved and restored is because the subroutine hexasc uses the register $a0. Since $a0 is used widely in the program it’s value gets copied over to $s0 it gets popped from the stack in order to get the original value of $s0 without hexasc conflicting with it.

2.	Which registers are used but not saved? Why are these not saved?

The temporary registers are used but never saved. This is because there are temporary registers made for temporary holding a certain value/address etc.


3.	Assume the time is 16:53. Which lines of your code handle the '5'?

All the lines of code from the beginning of the second iteration until the Add ‘:’ code block takes over.

## Assignment 4
```
delay:
	la $t1, ($a0)

whileloop:
	slt $t2, $zero, $t1
	beq $t2, 0, done

	nop
	addi $t1, $t1, -1
	add $t3, $t3, $zero
	addi $t4, $t4, 4711
	beq $t2, 1, forloop
	nop

forloop:
	slt $t5, $t3, $t4
	beq $t5, 0, whileloop 
	nop
	addi $t3, $t3, 1
	j forloop
	nop
	
done:
	jr $ra
	nop
```


1.	If the argument value in register $a0 is zero, which instructions in your subroutine are executed? How many times each? Why?

If the instruction $a0 is set to zero when calling the subroutine delay the instructions that are called are the following:
```
delay:
	la $t1, ($a0)

whileloop:
	slt $t2, $zero, $t1
	beq $t2, 0, donedone
    nop

done:
	jr $ra
	nop
```

This is because as long as $a0 is more than $zero, it will jump into the while loop but since $a0 is either zero or a negative number it means that $a0 is not more than $zero => it will never go into the for-loop and only entering while-loop, once.

2.	Repeat the previous question for a negative number: -1.

Same as above

## Assignment 8:
```
time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1
	la $s1, ($a1)
	la $s0, ($a0)	
	
	#First iteration
	la $a0, ($s1)
	jal hexasc
	nop
	
	#Prepare to change '9' to 'NINE'
	li $t8, 0x39 #'9' in ascii
	li $t7, 0x454e494e # 'E' 'N' 'I' 'N'
	
	#Prepare null byte 
	li $t5, 0x00
	
	bne  $t8, $v0, notAscNine #if $t8 != $v0 go to notAscNine
	nop
	
	sb $t5, 8($s0)
	sw $t7, 4($s0)
	j secondIter
	nop
	
notAscNine:
	sb $t5, 5($s0)
	sb $v0, 4($s0)
	 
secondIter:
	#Second iteration store second to last digit in adress 4($a0)
	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	sb $v0, 3($s0)
	
	#Add ':' to middle
	la $t5, 0x3a
	sb $t5, 2($s0)
	
	#Fourth iteration store Second digit in adress 1($s0)
	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	sb $v0, 1($s0)
	
	#Fifth iteration store first digit in adress 0($s0)
	srl $s1, $s1, 4
	la $a0, ($s1)
	jal hexasc
	nop
	
	sb $v0, 0($s0)

	POP $s1
	POP $s0
	POP $ra
	jr $ra
	nop
```