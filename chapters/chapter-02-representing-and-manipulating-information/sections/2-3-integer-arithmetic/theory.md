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

### PRINCIPLE: Detecting overflow of unsigned addition

For x and y in the range  $0 \le x$ ,  $y \le UMax_w$ , let  $s = x +_w^u y$ . Then the computation of s overflowed if and only if s < x (or equivalently, s < y).

#### Practice Problem 2.27 (solution page 188)

Write a function with the following prototype:
```
/* Determine whether arguments can be added without overflow */
int uadd_ok(unsigned x, unsigned y);
```
Solution
```
int uadd_ok(unsigned x, unsigned y){
unsigned sum = x+y;
return sum >= x;
}
```
### **PRINCIPLE:** Unsigned negation

For any number x such that  $0 \le x < 2^w$ , its w-bit unsigned negation  $-\frac{u}{w} x$  is given by the following:

$$-\frac{u}{w}x = \begin{cases} x, & x = 0\\ 2^w - x, & x > 0 \end{cases}$$

## 2.3.2 Two's Complement Addition

 Given integer values x and y in the range  $-2^{w-1} \le x$ ,  $y \le 2^{w-1} - 1$ , their sum is in the range  $-2^w \le x + y \le 2^w - 2$ , potentially requiring w + 1 bits to represent exactly. As before, we avoid ever-expanding data sizes by truncating the representation to w bits.

### **PRINCIPLE:** Two's-complement addition

For integer values x and y in the range  $-2^{w-1} \le x$ ,  $y \le 2^{w-1} - 1$ :

$$x +_{w}^{t} y = \begin{cases} x + y - 2^{w}, & 2^{w-1} \le x + y & \text{Positive overflow} \\ x + y, & -2^{w-1} \le x + y < 2^{w-1} & \text{Normal} \\ x + y + 2^{w}, & x + y < -2^{w-1} & \text{Negative overflow} \end{cases}$$

### 1. What is this section about?

Computers use a fixed number of bits to represent integers.

When we add two signed integers, the mathematical result might exceed the range that can be represented using those bits.

This situation is called **signed overflow**.

This section explains:

1. How two's-complement addition works.
2. What happens when the result exceeds the representable range.
3. How positive and negative overflow occur.
4. How to detect overflow.
5. How signed and unsigned addition are related.

---

### 2. Representable range

For a signed integer represented using `w` bits:

- Minimum value (TMin):

\[
TMin_w=-2^{w-1}
\]

- Maximum value (TMax):

\[
TMax_w=2^{w-1}-1
\]

For example, with 4 bits:

\[
TMin_4=-8,\qquad TMax_4=7
\]

Therefore, the representable range is:

\[
\boxed{-8\text{ to }+7}
\]

A 4-bit signed integer cannot represent +8 or -9.

---

## 3. How two's-complement addition works

The computer performs binary addition and retains only the lowest `w` bits of the result.

Any extra bits on the left are discarded. This process is called **truncation**.

### Example 1: Positive overflow

Calculate:

\[
5+3=8
\]

Binary addition using 4 bits:

```text
   0101    (5)
 + 0011    (3)
 -------
  01000
```

The result requires 5 bits, but our system stores only 4 bits.

Discard the leftmost bit:

```text
  01000
   ↓
  1000
```

In 4-bit two's complement, `1000` represents -8.

Therefore:

\[
5+_4^t3=-8
\]

This is called **positive overflow** because two positive numbers produced a negative result.

### Example 2: Negative overflow

Calculate:

\[
-8+(-5)=-13
\]

Binary addition:

```text
   1000    (-8)
 + 1011    (-5)
 -------
  10011
```

Discard the leftmost bit:

```text
  10011
   ↓
  0011
```

`0011` represents +3.

Therefore:

\[
-8+_4^t(-5)=3
\]

This is called **negative overflow** because two negative numbers produced a positive result.

### Example 3: Normal addition

Calculate:

\[
-8+5=-3
\]

```text
   1000    (-8)
 + 0101    (5)
 -------
   1101    (-3)
```

The result is within the representable range.

There is no overflow.

---

## 4. Equation 2.13 — Principle of Two's-Complement Addition

The book describes the result of addition using the following equation:

\[
x+_w^t y =
\begin{cases}
x+y-2^w & \text{Positive overflow}\\
x+y & \text{Normal addition}\\
x+y+2^w & \text{Negative overflow}
\end{cases}
\]

### Explanation

The equation simply tells us what happens to the mathematical sum after truncation.

| Situation | Operation |
|---|---|
| Positive overflow | Subtract \(2^w\) |
| Normal addition | Keep the original sum |
| Negative overflow | Add \(2^w\) |

For a 4-bit system:

\[
2^w=2^4=16
\]

Examples:

**Positive overflow:**

\[
5+5=10
\]

\[
10-16=-6
\]

**Negative overflow:**

\[
-8+(-5)=-13
\]

\[
-13+16=3
\]

**Normal addition:**

\[
-8+5=-3
\]

No adjustment is needed.

**Remember:** \(2^w\) represents the total number of different bit patterns available with `w` bits.

---

## 5. Signed vs. Unsigned Addition

One important observation made by the book is that signed and unsigned addition use exactly the same underlying binary addition.

For example:

```text
   0101
 + 0011
 -------
   1000
```

The result is always `1000`.

However, the decimal interpretation changes:

| Binary | Unsigned | Signed |
|---|---:|---:|
| 0101 | 5 | 5 |
| 0011 | 3 | 3 |
| 1000 | 8 | -8 |

The CPU performs the same bit-level addition.

Only the interpretation of the resulting bits changes.

This is why most computers can use the same machine instruction for signed and unsigned addition.

### T2U and U2T

The book uses two conversion functions:

- `T2U`: Converts a two's-complement value into its unsigned interpretation.
- `U2T`: Converts an unsigned value into its two's-complement interpretation.

For example, using 4 bits:

```text
Binary: 1111

T2U = 15
U2T = -1
```

The bits do not change. Only their interpretation changes.

### Equation 2.14

\[
x+_w^t y =
U2T_w(T2U_w(x)+_w^u T2U_w(y))
\]

In simple terms:

1. Convert signed operands to unsigned interpretations.
2. Perform unsigned addition.
3. Interpret the resulting bits as a signed number.

The final bit pattern is identical to directly performing two's-complement addition.

---

## 6. Detecting Signed Overflow

This is one of the most important principles in this section.

Let:

\[
s=x+_w^t y
\]

### Positive overflow

Positive overflow occurs if:

\[
x>0,\quad y>0,\quad s\leq0
\]

In other words:

Two positive numbers produce a non-positive result.

### Negative overflow

Negative overflow occurs if:

\[
x<0,\quad y<0,\quad s\geq0
\]

In other words:

Two negative numbers produce a non-negative result.

### Easy way to remember

| Operand 1 | Operand 2 | Result | Overflow? |
|---|---|---|---|
| Positive | Positive | Negative | Yes |
| Negative | Negative | Positive | Yes |
| Positive | Negative | Any sign | No |
| Negative | Positive | Any sign | No |

**Golden rule:** Signed overflow occurs when both operands have the same sign but the result has the opposite sign.

---

# 7. Practice Problems and Solutions

## Practice Problem 2.29

**Question:**

Fill in the following table in the style of Figure 2.25. Give the integer values of the 5-bit arguments, the values of both their integer and two's-complement sums, the bit-level representation of the two's-complement sum, and the case from the derivation of Equation 2.13.

| x | y |
|---|---|
| [10100] | [10001] |
| [11000] | [11000] |
| [10111] | [01000] |
| [00010] | [00101] |
| [01100] | [00100] |

### Solution

First, remember that a 5-bit signed integer has the following range:

\[
-16\text{ to }+15
\]

Convert the binary operands into signed decimal values and calculate their sums.

| x (decimal) | y (decimal) | x + y | \(x+_5^t y\) | Result bits | Case |
|---:|---:|---:|---:|---|---|
| -12 | -15 | -27 | 5 | 00101 | 1 |
| -8 | -8 | -16 | -16 | 10000 | 2 |
| -9 | 8 | -1 | -1 | 11111 | 2 |
| 2 | 5 | 7 | 7 | 00111 | 3 |
| 12 | 4 | 16 | -16 | 10000 | 4 |

### Understanding the cases

The four cases in the derivation are:

- **Case 1:** \(x+y<-16\) — Negative overflow.
- **Case 2:** \(-16\leq x+y<0\) — Normal negative result.
- **Case 3:** \(0\leq x+y<16\) — Normal non-negative result.
- **Case 4:** \(x+y\geq16\) — Positive overflow.

Note that Case 2 includes the boundary value -16, and Case 3 includes zero.

### Working example: First row

```text
x = 10100 = -12
y = 10001 = -15

Integer sum = -12 + (-15)
            = -27
```

For 5 bits:

\[
2^5=32
\]

Since -27 is below the minimum representable value (-16), negative overflow occurs.

\[
-27+32=5
\]

The final 5-bit representation is:

```text
00101 = 5
```

Therefore, the first row belongs to Case 1.

---

## Practice Problem 2.30

**Question:**

Write a function with the following prototype:

```c
/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y);
```

This function should return 1 if arguments x and y can be added without causing overflow.

### Solution

We know that:

- Positive overflow occurs when both operands are positive but the result is non-positive.
- Negative overflow occurs when both operands are negative but the result is non-negative.

Therefore:

```c
int tadd_ok(int x, int y)
{
    int sum = x + y;

    // Check positive overflow
    if (x > 0 && y > 0 && sum <= 0)
        return 0;

    // Check negative overflow
    if (x < 0 && y < 0 && sum >= 0)
        return 0;

    return 1;
}
```

### Explanation

The function checks two possible situations:

1. Both numbers are positive, but their sum becomes non-positive.
2. Both numbers are negative, but their sum becomes non-negative.

If either condition is true, overflow occurred, so it returns 0.

Otherwise, it returns 1.

**C language note:** This is the textbook-style solution under the assumed wraparound machine model. Signed overflow is technically undefined behavior in standard C, so this implementation is not fully portable. That distinction matters when writing production C code.

---

## Practice Problem 2.31

**Question:**

Your coworker presents the following implementation of `tadd_ok`:

```c
/* Determine whether arguments can be added without overflow */
/* WARNING: This code is buggy. */

int tadd_ok(int x, int y)
{
    int sum = x + y;

    return (sum - x == y) && (sum - y == x);
}
```

Explain why this implementation is incorrect.

### Solution

At first glance, the implementation looks reasonable.

We know the mathematical identities:

\[
(x+y)-x=y
\]

\[
(x+y)-y=x
\]

However, the problem is that computer arithmetic with fixed-width integers operates modulo \(2^w\).

Consider a 4-bit example:

```text
x = 5
y = 5
```

Actual mathematical result:

\[
5+5=10
\]

But in 4-bit two's complement:

```text
0101 + 0101 = 1010
```

`1010` represents -6.

Now consider the coworker's checks, assuming wraparound arithmetic:

\[
sum-x=-6-5=-11
\]

Truncating to 4 bits gives 5, which equals y.

Similarly:

\[
sum-y=-6-5=-11
\]

Truncating gives 5, which equals x.

Both conditions return true, even though overflow occurred.

### Why is it incorrect?

The identities still hold under modular arithmetic.

The addition and subsequent subtraction effectively cancel each other out, even if overflow occurred.

Therefore, these checks cannot reliably detect signed overflow.

---

## Practice Problem 2.32

**Question:**

You are assigned to write a function `tsub_ok`, with arguments x and y, that returns 1 if computing x - y does not cause overflow.

Having just written the code for Problem 2.30, you write:

```c
/* Determine whether arguments can be subtracted without overflow */
/* WARNING: This code is buggy. */

int tsub_ok(int x, int y)
{
    return tadd_ok(x, -y);
}
```

For what values of x and y will this function give incorrect results?

### Solution

The problem occurs when:

\[
y=TMin_w
\]

Remember:

\[
TMin_w=-2^{w-1}
\]

The smallest representable signed integer cannot be negated using the same number of bits.

For example, with 4-bit two's complement:

\[
y=-8
\]

But:

\[
-y=+8
\]

And +8 cannot be represented using 4-bit signed integers.

In wraparound arithmetic, negating -8 produces -8 again.

Therefore, the function actually calculates:

\[
tadd\_ok(x,-8)
\]

instead of correctly checking:

\[
x-(-8)=x+8
\]

These are not equivalent.

### Example

Take:

```text
x = 0
y = -8
```

The actual subtraction is:

\[
0-(-8)=8
\]

This overflows because the maximum representable value is +7.

But the function evaluates:

\[
tadd\_ok(0, -8)
\]

This addition does not overflow, so it returns 1.

The result is incorrect.

### Final answer

The function gives incorrect results whenever:

\[
\boxed{y=TMin_w}
\]

That is, whenever y is the minimum representable signed integer.

---

# 8. Final Revision Summary

Before moving to the next section, remember these points:

1. Two's-complement addition uses normal binary addition.
2. The computer retains only the lowest w bits.
3. Discarding extra bits is called truncation.
4. Positive overflow occurs when two positive operands produce a negative result.
5. Negative overflow occurs when two negative operands produce a positive result.
6. Adding operands with opposite signs cannot cause signed overflow.
7. Signed and unsigned addition have the same underlying bit-level operation.
8. \(2^w\) is the adjustment used in the mathematical description of overflow.
9. Overflow can be detected by checking the signs of the operands and result.
10. Negating the minimum signed integer causes a special problem because its positive counterpart cannot be represented.

## Important formulas

\[
TMin_w=-2^{w-1}
\]

\[
TMax_w=2^{w-1}-1
\]

\[
2^w=\text{Number of possible bit patterns}
\]

**Positive overflow:**

\[
x>0,\quad y>0,\quad s\leq0
\]

**Negative overflow:**

\[
x<0,\quad y<0,\quad s\geq0
\]

---

## 2.3.3 Two's complement Negation

We can see that every number x in the range  $TMin_w \le x \le TMax_w$  has an additive inverse under  $+_w^t$ , which we denote  $-_w^t x$  as follows:

### PRINCIPLE: Two's-complement negation

For x in the range  $TMin_w \le x \le TMax_w$ , its two's-complement negation  $-\frac{t}{w}x$  is given by the formula

$$-\frac{1}{w}x = \begin{cases}
 TMin_w, & x = TMin_w \\
 -x, & x > TMin_w
 \end{cases}$$
(2.15)

That is, for w-bit two's-complement addition,  $TMin_w$  is its own additive inverse, while any other value x has -x as its additive inverse.

## 2.3.4 Unsigned Multiplication

Integers x and y in the range  $0 \le x$ ,  $y \le 2^w - 1$  can be represented as w-bit unsigned numbers, but their product  $x \cdot y$  can range between 0 and  $(2^w - 1)^2 = 2^{2w} - 2^{w+1} + 1$ . This could require as many as 2w bits to represent. Instead, unsigned multiplication in C is defined to yield the w-bit value given by the low-order w bits of the 2w-bit integer product. Let us denote this value as  $x *_w^u y$

**PRINCIPLE:** Unsigned multiplication

For x and y such that  $0 \le x$ ,  $y \le UMax_w$ :

$$x *_{w}^{u} y = (x \cdot y) \mod 2^{w}$$


