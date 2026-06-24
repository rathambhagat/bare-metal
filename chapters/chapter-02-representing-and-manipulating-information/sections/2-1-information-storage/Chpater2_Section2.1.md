# 2.1 Information storage 

Rather than accessing individual bits in memory, most computers use blocks of
8 bits, or bytes, as the smallest addressable unit of memory. A machine-level
program views memory as a very large array of bytes, referred to as virtual
memory. Every byte of memory is identified by a unique number, known as its
address, and the set of all possible addresses is known as the virtual address space.

The C compiler also associates type information with
each pointer, so that it can generate different machine-level code to access the
value stored at the location designated by the pointer depending on the type of
that value. Although the C compiler maintains this type information, the actual
machine-level program it generates has no information about data types. It simply
treats each program object as a block of bytes and the program itself as a sequence
of bytes.

## Hexadecimal Notation

A single byte consists of 8 bits. In binary notation, its value ranges from 000000002
to 111111112. When viewed as a decimal integer, its value ranges from 010 to 25510.
Neither notation is very convenient for describing bit patterns. Binary notation
is too verbose, while with decimal notation it is tedious to convert to and from
bit patterns. Instead, we write bit patterns as base-16, or hexadecimal numbers.
Hexadecimal (or simply “hex”) uses digits ‘0’ through ‘9’ along with characters
‘A’ through ‘F’ to represent 16 possible values. 
