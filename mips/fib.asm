.data
ret:	.word	-858993460

.text
j main
Fibon1:
	sw	$ra,0($sp)
	sw	$fp,-4($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,32
	lw	$t1,4($fp)
	li	$t2,1
	bne	$t1,$t2,L1
	li	$v1,1
	#return
	add	$sp,$fp,$0
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	lw	$fp,-8($sp)
	jr	$ra
	j	L2
L1:
L2:
	lw	$t1,4($fp)
	li	$t2,2
	bne	$t1,$t2,L3
	li	$v1,1
	#return
	add	$sp,$fp,$0
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	lw	$fp,-8($sp)
	jr	$ra
	j	L4
L3:
	lw	$t1,4($fp)
	li	$t2,1
	sub	$t3,$t1,$t2
	sw	$t3,-16($fp)
	subi	$sp,$sp,4
	lw	$t1,-16($fp)
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	jal	Fibon1
	addi	$sp,$sp,4
	sw	$v1,-20($fp)
	lw	$t1,4($fp)
	li	$t2,2
	sub	$t3,$t1,$t2
	sw	$t3,-24($fp)
	subi	$sp,$sp,4
	lw	$t1,-24($fp)
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	jal	Fibon1
	addi	$sp,$sp,4
	sw	$v1,-28($fp)
	lw	$t1,-20($fp)
	lw	$t2,-28($fp)
	add	$t3,$t1,$t2
	sw	$t3,-32($fp)
	lw	$v1,-32($fp)
	#return
	add	$sp,$fp,$0
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	lw	$fp,-8($sp)
	jr	$ra
L4:
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,8
	li	$t1,6
	sw	$t1,-8($fp)
	subi	$sp,$sp,4
	li	$t1,6
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	jal	Fibon1
	addi	$sp,$sp,4
	sw	$v1,-12($fp)
	lw	$t1,-12($fp)
	la	$t2,ret
	sw	$t1,0($t2)
	la	$t1,ret
	lw	$a0,0($t1)
	li	$v0,1
	syscall
	#return main
