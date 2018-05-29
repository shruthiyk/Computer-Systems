	.file	"array2.c"
	.section	.rodata
.LC0:
	.string	"Enter the size of the array\n"
.LC1:
	.string	"%d"
	.align 8
.LC2:
	.string	"A[20] = %d\n A[60] = %d\n A[100]= %d\n"
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
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	addq	%rdx, %rax
	salq	$6, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$80, %rax
	movl	$10, (%rax)
	movq	-16(%rbp), %rax
	addq	$240, %rax
	movl	$50, (%rax)
	movq	-16(%rbp), %rax
	addq	$400, %rax
	movl	$90, (%rax)
	movq	-16(%rbp), %rax
	addq	$400, %rax
	movl	(%rax), %ecx
	movq	-16(%rbp), %rax
	addq	$240, %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	addq	$80, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L3
	call	__stack_chk_fail
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
