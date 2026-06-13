# 1.3 It Pays to Understand How Compilation Systems Work

For simple programs such as `hello.c`, we can rely on the compilation system to produce correct and efficient machine code. However, there are important reasons why programmers need to understand how compilation systems work:

## Optimizing Program Performance

Modern compilers are sophisticated tools that usually produce good code. As programmers, we do not need to know the inner workings of the compiler to write efficient code. However, to make good coding decisions in our C programs, we need a basic understanding of machine-level code and how the compiler translates different C statements into machine code. Important questions include:

- Is a `switch` statement always more efficient than a sequence of `if-else` statements?
- How much overhead is incurred by a function call?
- Is a `while` loop more efficient than a `for` loop?
- Are pointer references more efficient than array indexes?
- Why does a loop run so much faster if we sum into a local variable instead of an argument passed by reference?
- How can a function run faster when we simply rearrange parentheses in an arithmetic expression?

These questions are addressed in later chapters:
- **Chapter 3** introduces x86-64 machine language and shows how compilers translate C constructs
- **Chapter 5** teaches how to tune C program performance
- **Chapter 6** covers the memory hierarchy and how to exploit it

## Understanding Link-Time Errors

Some of the most perplexing programming errors relate to the linker, especially when building large software systems:

- What does it mean when the linker reports that it cannot resolve a reference?
- What is the difference between a static variable and a global variable?
- What happens if you define two global variables in different C files with the same name?
- What is the difference between a static library and a dynamic library?
- Why does library order on the command line matter?
- Why do some linker-related errors not appear until run time?

These questions are answered in **Chapter 7**.

## Avoiding Security Holes

For many years, **buffer overflow vulnerabilities** have accounted for many security holes in network and Internet servers. These vulnerabilities exist because too few programmers understand the need to carefully restrict the quantity and forms of data they accept from untrusted sources. A first step in learning secure programming is to understand how data and control information are stored on the program stack. This is covered in **Chapter 3** as part of the study of assembly language, including methods used by programmers, compilers, and operating systems to reduce the threat of attack.
