# 1.1 Information Is Bits + Context

Our `hello` program begins life as a *source program* (or *source file*) that a programmer creates with an editor and saves in a text file called `hello.c`. The source program is a sequence of bits, each with a value of 0 or 1, organized in 8-bit chunks called **bytes**. Each byte represents some text character in the program.

## ASCII Text Representation

Most computer systems represent text characters using the **ASCII standard**, which represents each character with a unique byte-size integer value. For example, the first byte of `hello.c` has the integer value 35, which corresponds to `'#'`. The second byte has the value 105, corresponding to `'i'`. Each text line is terminated by the invisible *newline* character `'\n'`, represented by the integer value 10.

![ASCII representation of hello.c](./images/_page_4_Figure_0.jpeg)

**Figure 1.2 — The ASCII text representation of hello.c**

Files such as `hello.c` that consist exclusively of ASCII characters are known as **text files**. All other files are known as **binary files**.

## The Fundamental Idea: Bits + Context

The representation of `hello.c` illustrates a fundamental idea:

> All information in a system — including disk files, programs stored in memory, user data stored in memory, and data transferred across a network — is represented as a bunch of bits. The only thing that distinguishes different data objects is the **context** in which we view them.

In different contexts, the same sequence of bytes might represent:
- An integer
- A floating-point number
- A character string
- A machine instruction

## Why This Matters to Programmers

As programmers, we need to understand machine representations of numbers because they are not the same as integers and real numbers. They are **finite approximations** that can behave in unexpected ways. This fundamental idea is explored in detail in Chapter 2.

---

### Aside: Origins of the C Programming Language

C was developed from 1969 to 1973 by **Dennis Ritchie** of Bell Laboratories. The ANSI C standard was ratified in 1989, later becoming the responsibility of ISO. Kernighan and Ritchie described ANSI C in their classic book known as "K&R" [61].

**Why C succeeded:**
1. **Closely tied with Unix** — C was developed as the system programming language for Unix. Most of the Unix kernel and its tools were written in C.
2. **Small, simple language** — The design was controlled by a single person, resulting in a clean, consistent design with little baggage. The K&R book describes the complete language in only 261 pages.
3. **Designed for a practical purpose** — C was designed to implement the Unix operating system.

C is the language of choice for system-level programming. However, C pointers are a common source of confusion and errors, and C lacks explicit support for classes, objects, and exceptions (addressed by C++ and Java).

---

### The `hello.c` Program

```c
#include <stdio.h>

int main()
{
    printf("hello, world\n");
    return 0;
}
```

**Figure 1.1 — The hello program**
