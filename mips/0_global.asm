.data
a:	.word	-858993460
b:	.word	1
array:	.space	40
zz:	.word	-858993460

.text
j main
	li	$t1,1
	sw	$t1,-1($fp)	#store const
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,8
	li	$t1,1
	la	$t2,a
	sw	$t1,0($t2)
	li	$t1,2
	la	$t2,a
	sw	$t1,0($t2)
	la	$t1,a
	lw	$t1,0($t1)
	li	$t2,1
	add	$t3,$t1,$t2
	la	$t2,zz
	sw	$t3,0($t2)
	la	$t1,a
	lw	$a0,0($t1)
	li	$v0,1
	syscall
	la	$t1,zz
	lw	$a0,0($t1)
	li	$v0,1
	syscall
	la	$t1,b
	lw	$a0,0($t1)
	li	$v0,1
	syscall
	#return main
