.data
z:	.word	-858993460

.text
j main
fun:
	sw	$ra,0($sp)
	sw	$fp,-4($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,8
	li	$t1,1
	la	$t2,z
	sw	$t1,0($t2)
	#return
	add	$sp,$fp,$0
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	lw	$fp,-8($sp)
	jr	$ra
main:
	#main head
	sw	$ra,($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,4
	li	$t1,1
	la	$t2,z
	sw	$t1,0($t2)
	subi	$sp,$sp,4
	li	$t1,1
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	li	$t1,1
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	jal	fun
	addi	$sp,$sp,8
	#return main
