.data
b:	.space	40

.text
j main
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,52
	li	$t1,0
	sw	$t1,-48($fp)
	lw	$t1,-48($fp)
	li	$t2,10
	bge	$t1,$t2,L1
L2:
	lw	$t1,-48($fp)
	sll	$t1,$t1,2

	la	$t2,-8($fp)
	sub	$t3,$t2,$t1
	lw	$t2,-48($fp)
	sw	$t2,0($t3)
	lw	$t1,-48($fp)
	sll	$t1,$t1,2

	la	$t2,b
	add	$t3,$t2,$t1
	lw	$t2,-48($fp)
	sw	$t2,0($t3)
	lw	$t1,-48($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-56($fp)
	lw	$t1,-56($fp)
	sw	$t1,-48($fp)
	lw	$t1,-48($fp)
	li	$t2,10
	blt	$t1,$t2,L2
L1:
	#return main
