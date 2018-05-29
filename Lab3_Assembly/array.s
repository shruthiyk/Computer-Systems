	.file	"array.c"
	.section	.rodata
.LC0:
	.string	"The array elements are : \n "
.LC1:
	.string	" %d\n "
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$20, myArray.2326+40(%rip)
	movl	myArray.2326+40(%rip), %eax
	movl	%eax, -12(%rbp)
	movl	$40, myArray.2326+160(%rip)
	movl	myArray.2326+160(%rip), %eax
	movl	%eax, -8(%rbp)
	movl	$0, myArray.2326+1604(%rip)
	movl	myArray.2326+1604(%rip), %eax
	movl	%eax, -4(%rbp)
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.local	myArray.2326
	.comm	myArray.2326,1600,32
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
