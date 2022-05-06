.data
a:	.word	-858993460
b:	.word	-858993460

.text
j main
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,32
	li	$t1,0
	la	$t2,a
	sw	$t1,0($t2)
	li	$t1,0
	la	$t2,b
	sw	$t1,0($t2)
	li	$t1,0
	sw	$t1,-8($fp)
	li	$t1,0
	sw	$t1,-12($fp)
	lw	$t1,-8($fp)
	li	$t2,100
	bge	$t1,$t2,L1
L2:
	lw	$t1,-12($fp)
	li	$t2,5
	bge	$t1,$t2,L3
L4:
	la	$t1,a
	lw	$t1,0($t1)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-24($fp)
	lw	$t1,-24($fp)
	la	$t2,a
	sw	$t1,0($t2)
	lw	$t1,-12($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-28($fp)
	lw	$t1,-28($fp)
	sw	$t1,-12($fp)
	lw	$t1,-12($fp)
	li	$t2,5
	blt	$t1,$t2,L4
L3:
	la	$t1,b
	lw	$t1,0($t1)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-32($fp)
	lw	$t1,-32($fp)
	la	$t2,b
	sw	$t1,0($t2)
	lw	$t1,-8($fp)
	li	$t2,1
	add	$t3,$t1,$t2
	sw	$t3,-36($fp)
	lw	$t1,-36($fp)
	sw	$t1,-8($fp)
	lw	$t1,-12($fp)
	li	$t2,5
	blt	$t1,$t2,L2
L1:
	#return main
