.data

.text
j main
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,32
	li	$t1,1
	sw	$t1,-16($fp)	#store const
	li	$t1,1
	sw	$t1,8($fp)
	li	$t1,2
	sw	$t1,4($fp)
	li	$t1,3
	sw	$t1,0($fp)
	li	$t1,4
	sw	$t1,-4($fp)
	li	$t1,5
	sw	$t1,-8($fp)
	li	$t1,6
	sw	$t1,-12($fp)
	li	$t1,3
	sw	$t1,-16($fp)
	#return main
