.data

.text
j main
fun:
	sw	$ra,0($sp)
	sw	$fp,-4($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,12
	li	$t1,1
	sw	$t1,-8($fp)
	#return
	add	$sp,$fp,$0
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	lw	$fp,-8($sp)
	jr	$ra
fun2:
	sw	$ra,0($sp)
	sw	$fp,-4($sp)
	add	$fp,$sp,$0
	subi	$sp,$sp,16
	li	$t1,10
	sw	$t1,-8($fp)
	li	$t1,11
	sw	$t1,-8($fp)
	lw	$v1,-8($fp)
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
	subi	$sp,$sp,8
	li	$t1,2
	sw	$t1,-8($fp)
	subi	$sp,$sp,4
	li	$t1,3
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	li	$t1,4
	sw	$t1,0($sp)
	subi	$sp,$sp,4
	jal	fun2
	addi	$sp,$sp,8
	sw	$v1,-4($fp)
	lw	$t1,-4($fp)
	sw	$t1,-8($fp)
	#return main
