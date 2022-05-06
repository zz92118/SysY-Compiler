.data
x:	.word	-858993460
y:	.word	-858993460
cc:	.word	10

.text
j main
	li	$t1,10
	sw	$t1,-1($fp)	#store const
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,20
	li	$t1,1
	sw	$t1,-8($fp)
	li	$t1,2
	sw	$t1,-12($fp)
	li	$t1,5
	la	$t2,x
	sw	$t1,0($t2)
	li	$t1,6
	la	$t2,y
	sw	$t1,0($t2)
	li	$t1,11
	la	$t2,x
	sw	$t1,0($t2)
	li	$t1,2
	sw	$t1,-20($fp)
	lw	$t1,-20($fp)
	li	$t2,6
	add	$t3,$t1,$t2
	sw	$t3,-12($fp)
	#return main
