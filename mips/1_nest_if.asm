.data
c:	.word	-858993460

.text
j main
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,8
	li	$t1,1
	li	$t2,2
	bge	$t1,$t2,L1
	li	$t1,1
	li	$t2,2
	bge	$t1,$t2,L3
	li	$t1,1
	la	$t2,c
	sw	$t1,0($t2)
	j	L4
L3:
L4:
	j	L2
L1:
L2:
	#return main
