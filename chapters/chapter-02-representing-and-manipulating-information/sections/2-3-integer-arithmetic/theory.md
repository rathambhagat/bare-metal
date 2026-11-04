# 2.3 Integer Arithmetic

Adding two positive numbers can yield a negative result, and that the comparison x<y can yield a different
result than the comparison x-y < 0. These properties are artifacts of the finite nature of computer arithmetic.

## 2.3.1 Unsigned Addition

Two non negative number x and y, such that x ≥ 0, y < $2^w$. Each of these values can be represented by a w-bit unsigned number. If we compute their sum, we have a possible range of 0 <= x+y <= $2^{w+1}$ - 1. Representing this sum could require w + 1 bits. And we would keep the sum as (w+1) and add another value we would get a (w+2) sum showing that "word size inflation" , means we cannot put any bound on the word size required to fully represent the represent of the arithmetic operations. Some programming langauge support arbitary size Arithmetic. 

### PRINCIPLE: Unsigned addition

For x and y such that 0 < x,  $y < 2^w$ :

$$x +_{w}^{u} y = \begin{cases} x + y, & x + y < 2^{w} \text{ Normal} \\ x + y - 2^{w}, & 2^{w} \le x + y < 2^{w+1} \text{ Overflow} \end{cases}$$
 (2.11)

The two cases of Equation 2.11 are illustrated in Figure 2.22, showing the sum x + y on the left mapping to the unsigned w-bit sum  $x + \frac{u}{w}y$  on the right. The normal case preserves the value of x + y, while the overflow case has the effect of decrementing this sum by  $2^w$ .

- Aside
In 2002, programmers involved in the FreeBSD open-source operating systems project realized that their implementation of the getpeername library function had a security vulnerability. A simplified version of their code went something like this:

```
 /*
* Illustration of code vulnerability similar to that found in
* FreeBSD's implementation of getpeername()
*/
/* Declaration of library function memcpy */
void *memcpy(void *dest, void *src, size_t n);
/* Kernel memory region holding user-accessible data */
#define KSIZE 1024
char kbuf[KSIZE];
/* Copy at most maxlen bytes from kernel region to user buffer */
int copy_from_kernel(void *user_dest, int maxlen) {
/* Byte count len is minimum of buffer size and maxlen */
int len = KSIZE < maxlen ? KSIZE : maxlen;
memcpy(user_dest, kbuf, len);
return len;
}
```

In this code, we show the prototype for library function memcpy on line 7, which is designed to copy a specified number of bytes n from one region of memory to another.
The function copy\_from\_kernel, starting at line 14, is designed to copy some of the data maintained by the operating system kernel to a designated region of memory accessible to the user. Most of the data structures maintained by the kernel should not be readable by a user, since they may contain sensitive information about other users and about other jobs running on the system, but the region shown as kbuf was intended to be one that the user could read. The parameter maxlen is intended to be the length of the buffer allocated by the user and indicated by argument user\_dest. The computation at line 16 then makes sure that no more bytes are copied than are available in either the source or the destination buffer.
Suppose, however, that some malicious programmer writes code that calls copy\_from\_kernel with a negative value of maxlen. Then the minimum computation on line 16 will compute this value for len, which will then be passed as the parameter n to memcpy. Note, however, that parameter n is declared as having data type size\_t. This data type is declared (via typedef) in the library file stdio.h. Typically, it is defined to be unsigned for 32-bit programs and unsigned long for 64-bit programs. Since argument n is unsigned, memcpy will treat it as a very large positive number and attempt to copy that many bytes from the kernel region to the user's buffer. Copying that many bytes (at least 231) will not actually work, because the program will encounter invalid addresses in the process, but the program could read regions of the kernel memory for which it is not authorized.
We can see that this problem arises due to the mismatch between data types: in one place the length parameter is signed; in another place it is unsigned. Such mismatches can be a source of bugs and, as this example shows, can even lead to security vulnerabilities. Fortunately, there were no reported cases where a programmer had exploited the vulnerability in FreeBSD. They issued a security advisory "FreeBSD-SA-02:38.signed-error" advising system administrators on how to apply a patch that would remove the vulnerability. The bug can be fixed by declaring parameter maxlen to copy\_from\_kernel to be of type size\_t, to be consistent with parameter n of memcpy. We should also declare local variable len and the return value to be of type size\_t.


