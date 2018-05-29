Compiler generated Assembly 1:
- What was the change between files swap_int.s and swap_long.s
Ans: Swapping of long integer uses -> movq instruction
     Swapping of integer uses -> movl instruction
     Difference in allocation of memory:
     For swap_int - multiple of 4
     For swap_long - multiple of 8

-------------------------------------------------

Compiler generated assembly 2( Swap 2 integers in a function)
Do the instructions use memory / registers in a different way?
Ans: This program uses rdi and rsi registers ( which are special registers used for representing the first and second argument of a function repectively)

-------------------------------------------------

Compiler generated assembly 3 - Static Array
How much are the offsets from the address?
The offset has been multiple of 4

For instance the location the memory address of the 0th element is offset by 1600, teh 50th element is offset by 1404 and so on

For example:
myArray[0] = 23;
myArray[49] = 6;
myArray[99] = 33;
myArray[199] = 81;
myArray[299] = 100;



movl    $23, -1600(%rbp)
movl    $6, -1404(%rbp)
movl    $33, -1204(%rbp)
movl    $81, -804(%rbp)
movl    $100, -404(%rbp)


-------------------------------------------------
 
Compiler generated assembly 4 - Dynamic Array
What is different from the static array?
- There is a call to malloc
- The offset starts from 0
- The register holding the base pointer %rbp is always offset by -8 for each mov instruction
- Also, before a movl instruction an addq instruction is carried out(addq $4 %rax)

For example:
myArray[0] = 23;
myArray[1] = 100;
myArray[2] = 200;
myArray[3] = 123;
myArray[4] = 256;
myArray[99] = 1;
myArray[299] = -20;


subq    $16, %rsp
movl    $1600, %edi
call    malloc
movq    %rax, -8(%rbp)
movq    -8(%rbp), %rax
movl    $23, (%rax)
movq    -8(%rbp), %rax
addq    $4, %rax
movl    $100, (%rax)
movq    -8(%rbp), %rax
addq    $8, %rax
movl    $200, (%rax)
movq    -8(%rbp), %rax
addq    $12, %rax
movl    $123, (%rax)
movq    -8(%rbp), %rax
addq    $16, %rax
movl    $256, (%rax)
movq    -8(%rbp), %rax
addq    $396, %rax
movl    $1, (%rax)
movq    -8(%rbp), %rax
addq    $1196, %rax
movl    $-20, (%rax)

-------------------------------------------------

Compiler generated assembly 5 - Goto

int a = 5;

  GOTO_LOOP:
    a += 1;

    if (a < 20){
      goto GOTO_LOOP;
    }

Was the code in goto.c
So the assembly had a jg instruction to end the program as below:


.L2:
	addl    $1, -4(%rbp)
	cmpl    $19, -4(%rbp)
	jg      .L4
	jmp     .L2
.L4:
	popq    %rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc


-------------------------------------------------

Compiler generated assembly 6 - For-loops

Source code:
int main(){
  // C program that counts to 5
  int i;

  for(i = 1; i <= 5; i++){
    //printf("Value = %d\n", i);
  }
}

The assembly code generated was:

.LFB0:
	.cfi_startproc
	pushq   %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq    %rsp, %rbp
	.cfi_def_cfa_register 6
	movl    $1, -4(%rbp)
	jmp     .L2

.L3:
	addl    $1, -4(%rbp)
.L2:
	cmpl    $5, -4(%rbp)
	jle     .L3
	popq    %rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc

	
So my guess is that the code goes to the start for the condition statement(cmpl $5, -4(%rbp), jle .L3)

-------------------------------------------------

Compiler generated assembly 7 - Switch Statements

For switch statements the compiler generates a jump table.
As the number of cases increases the jump table also increases hence not optimal.

-------------------------------------------------

Compiler generated assembly 8 - Add Function

- This program uses rdi and rsi registers
- popq is called in the add function

-------------------------------------------------