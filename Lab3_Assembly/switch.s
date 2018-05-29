	.file	"switch.c"
	.section	.rodata
.LC0:
	.string	" Enter the numbers : a\n "
.LC1:
	.string	"%d"
.LC2:
	.string	" Enter the numbers : b\n "
.LC3:
	.string	" 1: Add 2: Sub 3: Mul 4:Div \n"
.LC4:
	.string	" Enter any option : \n "
.LC5:
	.string	" Sum is %d \n"
.LC6:
	.string	" Sub is %d \n"
.LC7:
	.string	" Mul is %d \n"
.LC8:
	.string	" Div is %d \n"
	.align 8
.LC9:
	.string	" enter one among the options only"
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
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	leaq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-24(%rbp), %eax
	cmpl	$2, %eax
	je	.L3
	cmpl	$2, %eax
	jg	.L4
	cmpl	$1, %eax
	je	.L5
	jmp	.L2
.L4:
	cmpl	$3, %eax
	je	.L6
	cmpl	$4, %eax
	je	.L7
	jmp	.L2
.L5:
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	jmp	.L8
.L3:
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	jmp	.L8
.L6:
	movl	-20(%rbp), %edx
	movl	-16(%rbp), %eax
	imull	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	jmp	.L8
.L7:
	movl	-20(%rbp), %eax
	movl	-16(%rbp), %ecx
	cltd
	idivl	%ecx
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC8, %edi
	movl	$0, %eax
	call	printf
	jmp	.L8
.L2:
	movl	$.LC9, %edi
	movl	$0, %eax
	call	printf
	nop
.L8:
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L10
	call	__stack_chk_fail
.L10:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
