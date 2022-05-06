.data
n:	.word	10

.text
j main
	li	$t1,10
	la	$t2,n
	sw	$t1,0($t2)
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,16
	li	$t1,0
	sw	$t1,-8($fp)
	lw	$t1,-8($fp)
	li	$t2,10
	bge	$t1,$t2,L1
L2:
	la	$t1,n
	lw	$t1,0($t1)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-16($fp)
	lw	$t1,-16($fp)
	la	$t2,n
	sw	$t1,0($t2)
	lw	$t1,-8($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-20($fp)
	lw	$t1,-20($fp)
	sw	$t1,-8($fp)
	lw	$t1,-8($fp)
	li	$t2,10
	blt	$t1,$t2,L2
L1:
	#return main
