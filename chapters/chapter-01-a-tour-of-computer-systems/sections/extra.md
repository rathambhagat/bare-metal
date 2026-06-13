# Backup of Original Section Files

---

## 01-information-is-bits-plus-context.md

# 1.1 Information Is Bits + Context

Computers store everything as bits, grouped into bytes. The same bit pattern can mean different things depending on context: text, integer, instruction, or image data.

## Key ideas

- Text files are byte sequences interpreted through character encodings such as ASCII or UTF-8.
- Binary files are still just bits, but their meaning is defined by the program that reads them.
- Finite bit-widths create limits, so numbers are approximations and can overflow.

---

## 02-programs-are-translated-by-other-programs.md

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
/*At this point, our hello program is a compiled, executable binary sitting on the disk
. To actually run it, we use a program called a shell
. The shell is simply a command-line interpreter
. It prints a prompt, waits for you to type a command (like ./hello), and if it is not a built-in command, it assumes it is an executable file and loads it to run
.

Hardware Organization of a System To understand how the program runs, you need to know the four main hardware components:
Buses: These are electrical conduits (wires) running throughout the system that carry fixed-size chunks of data, called words, back and forth between components
.
I/O (Input/Output) Devices: These connect the system to the external world
. Examples include your keyboard and mouse (input), display monitor (output), and the disk drive (storage)
.
Main Memory: This is a temporary storage device (made of DRAM chips) that holds both the program and its data while the processor is running it
. Logically, it is organized as a massive linear array of bytes, each with its own unique address
.
The Processor (CPU): This is the engine that interprets and executes instructions
. Its core component is a register called the Program Counter (PC)
. The PC always points to the memory address of the next machine-language instruction to be executed
. The CPU performs simple operations like loading data from memory, storing data, performing math (in the ALU), and jumping to new instructions
.

Running the hello Program Step-by-Step Here is exactly what happens when you use the hardware to run the code:
Typing the command: As you type ./hello on the keyboard, the shell reads those characters into a register and then stores them in memory
.
Loading the file: When you hit "Enter", the shell knows you are done
. It then loads the compiled hello file from the disk into the main memory
. To save time, it often uses a technique called Direct Memory Access (DMA), which allows the data to travel directly from the disk to the main memory without the CPU having to manage the transfer
.
Executing and Displaying: Once the code and data are in memory, the processor begins executing the machine-language instructions
. It copies the bytes representing "hello, world\n" from memory into its registers, and then sends them out to the display device so you can see them on your screen
.*/
/*The Problem (The Processor-Memory Gap): A system spends a huge amount of time just moving data around (like from the disk to memory, and memory to the processor)
. As technology has advanced, processors have become incredibly fast, but main memory hasn't kept up
. This means the processor often wastes time waiting for data to arrive from memory
.
The Solution (Caches): To deal with this delay, system designers add smaller, faster storage devices called cache memories (or just caches) directly onto or near the processor chip
. Caches act as a temporary staging area for data the processor is likely to need in the near future
.
Cache Levels (L1 and L2):
The L1 cache is very small (tens of thousands of bytes) but lightning-fast—almost as quick as the processor's own internal registers
.
The L2 cache is larger (hundreds of thousands to millions of bytes) and is connected by a special bus
. It is slightly slower than L1, but still 5 to 10 times faster than accessing main memory
. Both of these caches are built using a fast hardware technology called SRAM (Static Random Access Memory)
.
Why Caches Work (Locality): Caches are effective because of a concept called locality
. This is the tendency for programs to access data and code in small, concentrated areas rather than randomly all over the place
.*/
/* The Big Picture: A computer system consists of hardware and systems software cooperating to run application programs
.
Data and Translation: Information is just a collection of bits, interpreted differently based on their context
. Programs begin as text and are translated by compilers and linkers into binary executables
.
Memory Hierarchy: Storage is organized in a strict hierarchy
. Faster, smaller devices at the top act as caches for the slower, larger, and cheaper devices at the bottom
.
OS Abstractions: The operating system kernel acts as an intermediary using three core abstractions: files (abstracting I/O devices), virtual memory (abstracting main memory and disks), and processes (abstracting the processor, memory, and I/O)
.
Networks: Computers communicate via networks, which the system simply treats as just another I/O device
.*/

---

## 03-processors-read-and-interpret-instructions-stored-in-memory.md

# 1.4 Processors Read and Interpret Instructions Stored in Memory

The CPU repeatedly fetches instructions from memory, decodes them, and executes them. The program counter points to the next instruction to run.

## Core hardware pieces

- Buses move data between components.
- I/O devices connect the system to the outside world.
- Main memory holds active programs and data.
- The processor executes instructions and updates state.

---

## 04-caches-matter.md

# 1.5 Caches Matter

Processors are much faster than main memory, so systems use caches to reduce the time spent waiting for data.

## Why caches help

- They keep recently used data close to the CPU.
- They exploit locality: programs tend to reuse the same data and instructions.
- Multi-level caches trade size for speed.

---

## 05-storage-devices-form-a-hierarchy.md

# 1.6 Storage Devices Form a Hierarchy

Storage is organized from fast and small to slow and large. Registers, caches, RAM, SSDs, and disks each serve different roles in the system.

## Takeaway

Higher levels are faster but more expensive per byte. Lower levels are cheaper and larger but slower.

---

## 06-the-operating-system-manages-the-hardware.md

# 1.7 The Operating System Manages the Hardware

The operating system provides abstractions that make hardware easier to use:

- **Processes** for running programs
- **Threads** for concurrency within a process
- **Virtual memory** for controlled address spaces
- **Files** for persistent storage access

---

## 07-systems-communicate-with-other-systems-using-networks.md

# 1.8 Systems Communicate with Other Systems Using Networks

Networks extend the computer system beyond local hardware. From the programmer's view, they behave like another form of I/O device, with messages moving between systems.

---

*End of backup — preserved from original section files on 2026-06-13.*
