.data
a:	.space	20

.text
j main
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,80
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	li	$t2,9
	sw	$t2,0($t3)
	li	$t1,1
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	li	$t2,3
	sw	$t2,0($t3)
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	li	$t2,4
	sw	$t2,0($t3)
	li	$t1,3
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	li	$t2,2
	sw	$t2,0($t3)
	li	$t1,4
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	li	$t2,7
	sw	$t2,0($t3)
	li	$t1,0
	sw	$t1,-8($fp)
	lw	$t1,-8($fp)
	sw	$t1,-12($fp)
	li	$t1,0
	li	$t2,4
	bge	$t1,$t2,L1
L2:
	li	$t1,0
	sw	$t1,-12($fp)
	li	$t1,0
	li	$t2,4
	bge	$t1,$t2,L3
L4:
	lw	$t1,-12($fp)
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-28($fp)
	lw	$t1,-12($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-32($fp)
	lw	$t1,-32($fp)
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-36($fp)
	lw	$t1,-28($fp)
	lw	$t2,-36($fp)
	bge	$t1,$t2,L5
	lw	$t1,-12($fp)
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-44($fp)
	lw	$t1,-44($fp)
	sw	$t1,-16($fp)
	lw	$t1,-12($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-48($fp)
	lw	$t1,-48($fp)
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-52($fp)
	lw	$t1,-12($fp)
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,-52($fp)
	sw	$t2,0($t3)
	lw	$t1,-48($fp)
	sw	$t1,-56($fp)
	lw	$t1,-56($fp)
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,-16($fp)
	sw	$t2,0($t3)
	j	L6
L5:
L6:
	lw	$t1,-12($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-12($fp)
	lw	$t1,-12($fp)
	li	$t2,4
	blt	$t1,$t2,L4
L3:
	lw	$t1,-8($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-8($fp)
	lw	$t1,-8($fp)
	li	$t2,4
	blt	$t1,$t2,L2
L1:
	li	$t1,0
	sw	$t1,-8($fp)
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-68($fp)
	lw	$a0,-68($fp)
	li	$v0,1
	syscall
	li	$t1,1
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-72($fp)
	lw	$a0,-72($fp)
	li	$v0,1
	syscall
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-76($fp)
	lw	$a0,-76($fp)
	li	$v0,1
	syscall
	li	$t1,3
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-80($fp)
	lw	$a0,-80($fp)
	li	$v0,1
	syscall
	li	$t1,4
	sll	$t1,$t1,2

	la	$t2,a
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-84($fp)
	lw	$a0,-84($fp)
	li	$v0,1
	syscall
	#return main
