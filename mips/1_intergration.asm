.data
x:	.word	-858993460
y:	.word	-858993460

.text
j main
compare:
	sw	$ra,0($sp)
	sw	$fp,-4($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,12
	li	$t1,2
	la	$t2,x
	sw	$t1,0($t2)
	lw	$t1,8($fp)
	lw	$t2,4($fp)
	ble	$t1,$t2,L1
	li	$t1,10
	la	$t2,x
	sw	$t1,0($t2)
	li	$v1,7
	#return
	add	$sp,$fp,$0
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	lw	$fp,-8($sp)
	jr	$ra
	j	L2
L1:
	li	$t1,20
	la	$t2,y
	sw	$t1,0($t2)
	li	$v1,2
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
	subi	$sp,$sp,40
	li	$t1,5
	sw	$t1,-20($fp)
	lw	$t1,-20($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-24($fp)
	lw	$t1,-24($fp)
	li	$t2,10
	add	$t3,$t1,$t2
	sw	$t3,-8($fp)
	li	$t1,6
	sw	$t1,-32($fp)
	lw	$t1,-32($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-12($fp)
	lw	$t1,-8($fp)
	lw	$t2,-12($fp)
	add	$t3,$t1,$t2
	sw	$t3,-8($fp)
	subi	$sp,$sp,4
	li	$t1,1
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	li	$t1,10
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	jal	compare
	addi	$sp,$sp,8
	sw	$v1,-44($fp)
	lw	$t1,-44($fp)
	sw	$t1,-16($fp)
	lw	$a0,-16($fp)
	li	$v0,1
	syscall
	la	$t1,x
	lw	$a0,0($t1)
	li	$v0,1
	syscall
	la	$t1,y
	lw	$a0,0($t1)
	li	$v0,1
	syscall
	#return main
