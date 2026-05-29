// Introduction
/*Everything Starts as Bits: When you write a program (like a simple hello.c file), you are creating a source file
. To the computer, this file is just a massive sequence of bits (0s and 1s) organized into 8-bit chunks called bytes
.
Text vs. Binary Files: In a source file, each byte represents a specific text character using a standard called ASCII
. For example, the integer value 35 translates to the character '#'
. Files made exclusively of these ASCII characters are called text files, while all other files are called binary files
.
The Golden Rule (Bits + Context): The most fundamental idea in this section is that all information in a computer system—whether it is a file on your disk, data in memory, or information sent over a network—is represented simply as a bunch of bits
.
Why Context Matters: If everything is just bits, how does the computer know what they mean? The answer is context. The exact same sequence of bytes might represent an integer in one situation, a text string in another, or a machine instruction in yet another
.
Numbers are Approximations: Because computers use a finite number of bits, the numbers they represent are finite approximations, which means they can sometimes behave unexpectedly compared to pure mathematics
.*/

// How does the hello.c Praogram is actually runs on the system.
/*Your hello.c file is written in a "high-level" language, meaning it is easy for humans to read
. But your computer's hardware doesn't understand C; it only understands low-level machine instructions (binary)
.
To bridge this gap, a tool called a compiler driver (like GCC) translates your text file into an executable binary file through a four-step pipeline called the compilation system
.
Preprocessing Phase (cpp): The preprocessor looks for commands in your code that start with #, like #include <stdio.h>
. It actually opens that stdio.h file and pastes its contents directly into your program
. The result is still a text file, typically ending in .i
.
Compilation Phase (cc1): The compiler translates that .i text file into a .s text file
. This new file contains assembly language
. Assembly is still human-readable text, but it is one step closer to machine language
.
Assembly Phase (as): The assembler takes that .s assembly text and finally converts it into actual binary machine-language instructions
. It saves this into a .o file (called a relocatable object program)
. If you opened this .o file in a text editor, it would just look like unreadable gibberish
.
Linking Phase (ld): Your program uses the printf function, which is part of the standard C library
. The code for printf already exists in a separate, precompiled .o file (like printf.o)
. The linker merges printf.o with your hello.o file
.
The final result is an executable object file (often just called an executable), which is a completely self-contained binary file ready to be loaded into memory and run by the system
.*/

// The Hello world code
#include<stdio.h>
int main(){
  printf("Hello, World\n");
  return 0;
}

/* The Assembly code for the hello.c 
 .file	"hello.c"
	.text
	.section	.rodata
.LC0:
	.string	"Hello, World"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
*/


