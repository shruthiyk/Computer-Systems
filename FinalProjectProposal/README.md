# Final Project

Please fill out the proposal below. The range of projects for this course is wide, and can be anything Systems related (Even topics we have not covered such as databases, security, etc). The sidequests listed on the webpage may be example projects, or you may want to take a homework/lab substantially further. For your final project, think of this as a project that takes about 3x the effort of a homework. You may use other Systems languages(D, C++, Go, Rust, etc.) if it makes sense for the domain of the problem you are trying to solve.

For the final project you are expected to have a functioning tool, application, library, or framework that I can run. Additional deliverables will include a brief writeup and video demonstrating your tool in action. I see the final project as something you can be proud to put on your resume/portfolio!

## Proposal

** Fill this part out by July 3rd **

Who will you be working with (Max of 3 members--working solo is fine if you choose)?
  * Teammate 1: Shruthi Kulkarni 
  * Teammate 2: Amit Kulkarni
  * Teammate 3: ?

If you are looking for team members, you can use this spreadsheet to get in contact with folks and make a pitch.
(Your final team members information should be in the spreadsheet and in this README.md)
https://docs.google.com/spreadsheets/d/1Yg2_M6U9mx8hfAS10NH5fpNh-1u56QESIhnuEQGn1Ow/edit?usp=sharing

### In one sentence, describe your project.

We are going to build a Linux Debugger using C/C++ as our programming language.


### What is the minimum deliverable for this project?

The debugger will have the following features:
- Launch, halt and continue execution.
- Breakpoints: We would be implementing software breakpoints that involve modifying the code on the fly.
- Read from and write to registers and memory
- Printing backtrace
- Print current source location
- Single Stepping Instructions
- Handling Variables -> variables to be tracked and manipulated by our debugger

### What is the maximum deliverable for this project?

If possible we would like to add the following features to our debugger
- Multi-threaded debugging support
- Shared Library and Dynamic Loading Support - Debugger needs to know what shared libraries
  have been loaded by the debuggee so that it can support setting of breakpoints, get source-level information
  and symbols etc.
- Try to implement a GUI using python's Tkinter library which will allow users to perform all the\
  debugging operations


### What tools or environment will you be using?
- C/C++ for building the debugger.
- Python for building the GUI for the debugger.
- Will be building the debugger for and testing it on CCIS machines


### What are your first step(s)?

- Checkout how GDB works( https://www.cs.cmu.edu/~gilpin/tutorial/ )
- The first step would be to write a simple program( such as a queue implementation)
  and to perform various operations using gdb such as adding breakpoints, printing backtrace etc.


### Find at least one related publication or tool and reference it here.
- https://www.gnu.org/software/gdb/
- https://blog.tartanllama.xyz/writing-a-linux-debugger-setup/



### What is the biggest problem you foresee or question you need to answer to get started?

- Need to understand the ELF format of binary/executable
- Need to understand how symbol table works
- Understand system calls such as ptrace
- Need to understand assembly level registers operations if any are involved

### Instructor Feedback

*Your instructor will write a short note here if this is an acceptable project.*

*Your instructor will give you some range of the grade you can earn if you meet all of your deliverables.* e.g. [B+/A-/A]

Perfect, I'll look forward to your evaluation. This project falls in the [B+/A-/A]. It will be worth providing some buggy C/C++ programs to show how your debugger works.
