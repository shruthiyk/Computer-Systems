.global _start # code segment 
.text
# this program sorts the given array of integers using bubblesort


sort:
	pushq	%rbp  # base pointer of the current stack frame 
	movq	%rsp, %rbp  # rsp is the stack pointer for the current stack frame and points to the top of the stack, here since there is not data yet, we are setting the stack pointer to base pointer 			 	#location , both pointing to same location , initially, 
	movq	%rdi, -24(%rbp)  # index pointers for array
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp) # initializing the variables 
	movl	$0, -4(%rbp) 
	jmp	.outerloop

.innerloop:
	movl	$0, -8(%rbp)
	jmp	.incinnerloop # call function to increment inneer loop

.swap:                           # swap the two consecutive numbers if the condition is met
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rcx
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.addtoinnerloop  
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rcx     
	movq	-24(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	movl	%eax, (%rdx)
.addtoinnerloop:
	addl	$1, -8(%rbp)

.incinnerloop:
	movl	-28(%rbp), %eax
	subl	$1, %eax
	cmpl	-8(%rbp), %eax
	jg	.swap # if the first element i.e a[j] is greater than a[j+1] , then swap the numbers , swap function is called
	addl	$1, -4(%rbp)
.outerloop:
	movl	-28(%rbp), %eax
	subl	$1, %eax
	cmpl	-4(%rbp), %eax
	jg	.innerloop
	nop
	popq	%rbp
	ret
_start:      # _start is like main function in C
	pushq	%rbp   
	movq	%rsp, %rbp
	subq	$48, %rsp     #allocating space on stack for each integer in the array
	movl	$116, -48(%rbp) # each in integer is 4 bytes, and the stack space is shifted by 4 bytes everytime an integer is pushed on to the stack
	movl	$67, -44(%rbp)
	movl	$69, -40(%rbp)
	movl	$102, -36(%rbp)
	movl	$101, -32(%rbp)
	movl	$102, -28(%rbp)
	movl	$111, -24(%rbp)
	movl	$114, -20(%rbp)
	movl	$65, -16(%rbp)
	leaq	-48(%rbp), %rax 
	movl	$9, %esi     # index pointer to indicate the size of the array, which is 9 here in this program
	movq	%rax, %rdi
	call	sort         # sort function is called
	movl	$0, -4(%rbp) # intializing i for printing the integers after sort function is executed
	jmp	.printarray  # for loop to print the sorted array is called

.printtoscreen:
	leaq	-48(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	$4, %edx
	movq	%rax, %rsi
	movl	$1, %edi     
	mov 	$1, %rax     # syscall for write
	mov	$1, %rdi     #file handle 1 is stdout 
	mov 	$4, %rdx
	syscall			# invoke the operating system to write to the screen
	addl	$1, -4(%rbp)    # increment after each number is printed in the array

.printarray:
	cmpl	$8, -4(%rbp)
	jle	.printtoscreen # function to print each element of the sorted array on the screen is called when i is less than 9(value specified for the static array)  
	movl	$0, %eax
	leave
	mov	$60, %rax  #syscall to exit 
	xor 	%rdi, %rdi    # exit code 0
	syscall              # invoke the operating system to exit
