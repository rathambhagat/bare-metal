/*Modern computers store and process information represented as two-valued
signals. These lowly binary digits, or bits, form the basis of the digital revolution.*/


/*Computer representations use a limited number of bits to encode a number,
and hence some operations can overflow when the results are too large to be rep
resented.*/ 
/* #include<stdio.h>
int main(){
  printf("%d",200*300*400*500);
  return 0;
} */
// When we complie the Above function we get a warning

/* bits.c: In function ‘main’:
bits.c:8:26: warning: integer overflow in expression of type ‘int’ results in ‘-884901888’ [-Woverflow]
    8 |   printf("%d",200*300*400*500);*/

// The Output of it is a negative number = -884901888
/*Word Size: Defines the nominal size of pointer data and dictates the maximum virtual address space.
A w-bit machine can access at most 2^w bytes of memory
Memory Limits: 32-bit systems are capped at 4 Gigabytes of virtual memory
64-bit systems expand this limit to 16 Exabytes
Program vs. Machine: A "32-bit program" or "64-bit program" refers to how the code is compiled, not the physical hardware.
64-bit machines are backward compatible and can seamlessly run 32-bit programs
C Data Type Byte Sizes (32-bit / 64-bit):
char: 1 byte (It is the only type not guaranteed to be signed by default; use signed char if needed)
short: 2 bytes
int: 4 bytes
long: 4 bytes / 8 bytes
Pointers (char *): 4 bytes / 8 bytes
float / double: 4 bytes / 8 bytes
ISO C99 Fixed-Size Types: To eliminate size ambiguity across different compilers and machines, C99 introduced exact-size data types like int32_t (exactly 4 bytes) and int64_t (exactly 8 bytes).
Common Portability Bug: Storing a memory pointer inside an int variable works on 32-bit systems but catastrophically truncates the data on 64-bit systems because the pointer size doubles to 8 bytes.*/
