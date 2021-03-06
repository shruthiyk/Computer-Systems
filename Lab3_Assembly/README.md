# "Assembly - Nearing Machine Code Representation"



# Part 1 - Compiler Generated Assembly

Let us get some experience reading assembly code generated by the compiler! It is actually kind of fun, and you may learn some new instructions.

I **strongly** recommend using the godbolt tool (https://godbolt.org/) to write and experiment. The color mappings will help you see what is going on with the generated assembly.

Then you are required to get practice generating the assembly from your compiler (as instructed below).

## Compiler generated assembly 1 

- Write a C program that swaps two integers(in the main body of code).
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as swap_int.s).
  - Use: `gcc -O0 -fno-builtin swap_int.c -S -o swap_int.s`
- Now modify your program to swap two long's.
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as swap_long.s).
  - Use: `gcc -O0 -fno-builtin swap_long.c -S -o swap_long.s`
- Compare each of the two assembly files using diff. See what changed.
- diff syntax
  - Use: `diff -y swap_int.s swap_long.s`

## Compiler generated assembly 2 

- Write a C program that swaps two integers in a **function** (You may use today's slide as a reference)
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as swap.s).
  - Use: `gcc -O0 -fno-builtin  swap.c -S -o swap.s`
- Do the instructions use memory/registers in a different way?

## Compiler generated assembly 3 - Static Array
- Write a C program called array.c that has an array of 400 integers in the function of main.
- Initialize some of the values to something (do not use a loop) (e.g. myArray[0]=72; myArray[70]=56; etc)
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as array.s).
  - Use: `gcc -O0 -fno-builtin  array.c -S -o array.s`
- How much are the offsets from the address?

## Compiler generated assembly 4 - Dynamic Array 

- Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.
- Initialize some of the values to something (do not use a loop) (e.g. myArray[66]=712; myArray[70]=536; etc)
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as array2.s).
  - Use: `gcc -O0 -fno-builtin  array2.c -S -o array2.s`
- Study the assembly and think about what is different from the static array.

The screenshot below may also help illustrate something interesting.
<img src="./assembly.PNG">

## Compiler generated assembly 5 - Goto
The C programming language has a 'goto' command, search how to use it if you have not previously.

- Write a C program using the goto command and a label.
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as goto.s).
  - Use: `gcc -O0 -fno-builtin  goto.c -S -o goto.s`
- Observe what kind of jmp statement is inserted.

## Compiler generated assembly 6 - For-loops
- Write a C program using a for-loop that counts to 5.
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as for.s).
  - Use: `gcc -O0 -fno-builtin  for.c -S -o for.s`
- Observe where the code goes for the condition statement (at the start or at the end?).

## Compiler generated assembly 7 - Switch Statements

- Write a C program using a switch statement (Sample here).
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as switch.s).
  - Use: `gcc -O0 -fno-builtin switch.c -S -o switch.s`
- See what code a switch statement generates. Is it optimal?

## Compiler generated assembly 8 - Add Function

- Write a C program that calls an add function(long add(long a, long b).
- Save, Compile, and Run the program to verify it works.
- Output the assembly from that program (Save it as add.s).
  - Use: `gcc -O0 -fno-builtin add.c -S -o add.s`
- Observe the outputs
- Observe arguments put into registers
- Observe where 'popq' is called.

# More resources to help

- Matt Godbolt has written a great tool to help understand assembly generated from the compiler. 
  - https://godbolt.org/
- An assembly cheat sheet from Brown
  - https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf
- MIT Cheat sheet
  - http://6.035.scripts.mit.edu/sp17/x86-64-architecture-guide.html

# Deliverable
  
- Add your programs and their output to this repository.
  - Note this submission will be auto graded for completion (i.e. save the file names as shown).

# Going Further

- (Optional) Try the objdump example to read the disassembly from your programs.
