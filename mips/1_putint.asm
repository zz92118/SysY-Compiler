.data
c:	.space	40
a:	.word	1
b:	.word	-858993460

.text
j main
	li	$t1,1
	la	$t2,a
	sw	$t1,0($t2)
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,16
	la	$t1,a
	lw	$t1,0($t1)
	la	$t2,a
	sw	$t1,0($t2)
	li	$t1,1
	la	$t2,b
	sw	$t1,0($t2)
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,c
	add	$t3,$t2,$t1
	li	$t2,1
	sw	$t2,0($t3)
	li	$t1,1
	sll	$t1,$t1,2

	la	$t2,c
	add	$t3,$t2,$t1
	li	$t2,1
	sw	$t2,0($t3)
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,c
	add	$t3,$t2,$t1
	li	$t2,1
	sw	$t2,0($t3)
	li	$t1,4
	sll	$t1,$t1,2

	la	$t2,c
	add	$t3,$t2,$t1
	li	$t2,1
	sw	$t2,0($t3)
	li	$a0,4
	li	$v0,1
	syscall
	la	$t1,a
	lw	$a0,0($t1)
	li	$v0,1
	syscall
	la	$t1,b
	lw	$a0,0($t1)
	li	$v0,1
	syscall
	li	$t1,0
	sll	$t1,$t1,2

	la	$t2,c
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-8($fp)
	lw	$a0,-8($fp)
	li	$v0,1
	syscall
	li	$t1,2
	sll	$t1,$t1,2

	la	$t2,c
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-12($fp)
	lw	$a0,-12($fp)
	li	$v0,1
	syscall
	li	$t1,4
	sll	$t1,$t1,2

	la	$t2,c
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-16($fp)
	lw	$a0,-16($fp)
	li	$v0,1
	syscall
	la	$t1,a
	lw	$t1,0($t1)
	sll	$t1,$t1,2

	la	$t2,c
	add	$t3,$t2,$t1
	lw	$t2,0($t3)
	sw	$t2,-20($fp)
	lw	$a0,-20($fp)
	li	$v0,1
	syscall
	#return main
