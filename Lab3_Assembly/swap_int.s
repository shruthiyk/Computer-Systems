	.file	"swap_int.c"
	.section	.rodata
.LC0:
	.string	" enter the values for a : "
.LC1:
	.string	"%d"
.LC2:
	.string	" enter the values for b : "
	.align 8
.LC3:
	.string	"The values are \n a: %d \n b: %d \n"
	.align 8
.LC4:
	.string	" The values after swapping are\n a: %d\n b: %d\n"
	.align 8
.LC5:
	.string	" Both the numbers are same , hence not swapped "
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
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %eax
	cmpl	%eax, %edx
	je	.L2
	movl	-20(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	jmp	.L3
.L2:
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
.L3:
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L5
	call	__stack_chk_fail
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
