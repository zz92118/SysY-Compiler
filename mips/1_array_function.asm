.data
x:	.word	-858993460

.text
j main
compare:
	sw	$ra,0($sp)
	sw	$fp,-4($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,12
	lw	$t1,-4($fp)
	lw	$t2,0($fp)
	ble	$t1,$t2,L1
	li	$t1,10
	la	$t2,x
	sw	$t1,0($t2)
	li	$v1,10
	#return
	add	$sp,$fp,$0
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	lw	$fp,-8($sp)
	jr	$ra
	j	L2
L1:
	li	$t1,20
	la	$t2,x
	sw	$t1,0($t2)
	li	$v1,20
	#return
	add	$sp,$fp,$0
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	lw	$fp,-8($sp)
	jr	$ra
L2:
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,124
	li	$t1,2
	sw	$t1,-8($fp)
	li	$t1,3
	sw	$t1,-12($fp)
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,0
	sw	$t2,0($t3)
	li	$t1,1
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,1
	sw	$t2,0($t3)
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,2
	sw	$t2,0($t3)
	li	$t1,3
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,3
	sw	$t2,0($t3)
	li	$t1,4
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,4
	sw	$t2,0($t3)
	li	$t1,5
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,5
	sw	$t2,0($t3)
	li	$t1,6
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,6
	sw	$t2,0($t3)
	li	$t1,7
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,7
	sw	$t2,0($t3)
	li	$t1,8
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,8
	sw	$t2,0($t3)
	li	$t1,9
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	li	$t2,9
	sw	$t2,0($t3)
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-84($fp)
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,-56($fp)
	sub	$t3,$t2,$t1
	lw	$t2,-84($fp)
	sw	$t2,0($t3)
	li	$t1,3
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-88($fp)
	li	$t1,1
	sll	$t1,$t1,2

	la	$t2,-56($fp)
	sub	$t3,$t2,$t1
	lw	$t2,-88($fp)
	sw	$t2,0($t3)
	li	$t1,4
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-92($fp)
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,-56($fp)
	sub	$t3,$t2,$t1
	lw	$t2,-92($fp)
	sw	$t2,0($t3)
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,-68($fp)
	sub	$t3,$t2,$t1
	li	$t2,0
	sw	$t2,0($t3)
	li	$t1,10
	li	$t2,10
	mul	$t3,$t1,$t2
	sw	$t3,-96($fp)
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,-56($fp)
	sub	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-100($fp)
	lw	$t1,-96($fp)
	lw	$t2,-100($fp)
	add	$t3,$t1,$t2
	sw	$t3,-104($fp)
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,-68($fp)
	sub	$t3,$t2,$t1
	lw	$t2,-104($fp)
	sw	$t2,0($t3)
	lw	$t1,-12($fp)
	lw	$t2,-8($fp)
	add	$t3,$t1,$t2
	sw	$t3,-108($fp)
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	lw	$t2,-108($fp)
	sw	$t2,0($t3)
	lw	$t1,-8($fp)
	lw	$t2,-12($fp)
	mul	$t3,$t1,$t2
	sw	$t3,-112($fp)
	lw	$t1,-112($fp)
	lw	$t2,-8($fp)
	add	$t3,$t1,$t2
	sw	$t3,-116($fp)
	li	$t1,1
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	lw	$t2,-116($fp)
	sw	$t2,0($t3)
	li	$t1,110
	sw	$t1,-12($fp)
	li	$t1,9
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-120($fp)
	li	$t1,8
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-124($fp)
	subi	$sp,$sp,4
	lw	$t1,-120($fp)
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	lw	$t1,-124($fp)
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	jal	compare
	addi	$sp,$sp,8
	sw	$v1,-128($fp)
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,-16($fp)
	sub	$t3,$t2,$t1
	lw	$t2,-128($fp)
	sw	$t2,0($t3)
	#return main
