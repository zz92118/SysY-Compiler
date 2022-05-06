.data
z:	.word	-858993460
z2:	.word	-858993460

.text
j main
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,16
	li	$t1,1
	sw	$t1,-8($fp)
	li	$t1,2
	sw	$t1,-12($fp)
	lw	$t1,-8($fp)
	lw	$t2,-12($fp)
	bgt	$t1,$t2,L1
	li	$t1,1
	la	$t2,z
	sw	$t1,0($t2)
	j	L2
L1:
	li	$t1,2
	la	$t2,z
	sw	$t1,0($t2)
L2:
	lw	$t1,-8($fp)
	lw	$t2,-12($fp)
	ble	$t1,$t2,L3
	li	$t1,1
	la	$t2,z2
	sw	$t1,0($t2)
	j	L4
L3:
	li	$t1,2
	la	$t2,z2
	sw	$t1,0($t2)
L4:
	#return main
