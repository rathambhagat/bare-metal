# Chapter 2 Section 2.2: Integer Representations

## Summary

This section examines how computers encode integers using bit-level representations. Two fundamental encoding schemes are covered: **unsigned encoding** for nonnegative integers, and **two's-complement encoding** for signed integers (negative, zero, and positive). The mathematical foundations, conversion between representations, bit-width expansion/truncation, and the practical pitfalls of implicit casting in C are all explored in detail.

---

## 2.2.1 Integral Data Types

C provides several integral data types (`char`, `short`, `int`, `long`) with `unsigned` variants. The number of bytes allocated per type depends on whether the program is compiled for 32-bit or 64-bit architectures. The ranges are asymmetric in two's complement: the negative range extends one further than the positive range (i.e., `|TMin| = |TMax| + 1`), because zero occupies one of the nonnegative slots.

The standard fixed-size types (`intN_t`, `uintN_t` from `<stdint.h>`) guarantee exact bit widths (8, 16, 32, 64), eliminating platform dependence.

---

## 2.2.2 Unsigned Encodings

For a w-bit vector $\vec{x} = [x_{w-1}, x_{w-2}, \dots, x_0]$, the unsigned interpretation is:

$$B2U_w(\vec{x}) = \sum_{i=0}^{w-1} x_i 2^i$$

**Properties:**
- Range: $0 \leq x \leq UMax_w = 2^w - 1$
- $B2U_w$ is a bijection: every w-bit pattern maps to a unique unsigned integer in $[0, 2^w-1]$, and vice versa.

**Examples (w = 4):**
- $B2U_4([0001]) = 1$
- $B2U_4([0101]) = 5$
- $B2U_4([1011]) = 11$
- $B2U_4([1111]) = 15 = 2^4 - 1$

### The Transformation Function ($B2U_w$):
Unsigned encoding translates a raw bit vector $\vec{x}$ into a non-negative mathematical integer using the strictly defined positional formula $B2U_w(\vec{x}) \doteq \sum_{i=0}^{w-1} x_i 2^i$ 1.
### Positional Weighting: 
Each physical bit $x_i$ acts as an independent binary switch. If the bit is $1$, it contributes exactly $2^i$ to the overall decimal sum; if $0$, it contributes nothing 1.
### Absolute Boundaries:
The representable range for a $w$-bit unsigned integer is strictly bound between a minimum of $0$ (a vector of all zeros) and a maximum of $UMax_w \doteq 2^w - 1$ (a vector of all ones) 2.
### The Bijection Principle: 
$B2U_w$ is mathematically defined as a bijection 3. This guarantees a perfect 1-to-1 relationship: every bit pattern creates a unique decimal number, and every decimal number corresponds to exactly one unique bit pattern 2, 3.
### The Inverse Function ($U2B_w$): 
Because it is a bijection, $B2U_w$ has a perfect mathematical inverse called $U2B_w$ (Unsigned to Binary) 3. $U2B_w$ applies the exact same properties in reverse, mapping an integer back to its singular $w$-bit physical vector 3.

---

## 2.2.3 Two's-Complement Encodings

The most significant bit (sign bit) carries negative weight:

$$B2T_w(\vec{x}) = -x_{w-1}2^{w-1} + \sum_{i=0}^{w-2} x_i 2^i$$

**Properties:**
- Range: $TMin_w = -2^{w-1}$ to $TMax_w = 2^{w-1} - 1$
- $B2T_w$ is a bijection.
- Asymmetry: $|TMin| = |TMax| + 1$ (e.g., for w=4: -8 to 7, not -7 to 7).
- The two's-complement range is asymmetric: |*TMin*| = |*TMax*| + 1; that is, there is no positive counterpart to *TMin*.
- This asymmetry arises because half the bit patterns (those with the sign bit set to 1) represent negative numbers, while half (those with the sign bit set to 0) represent nonnegative numbers. Since 0 is nonnegative, this means that it can represent one less positive number than negative. Second, the maximum unsigned value is just over twice the maximum two's-complement value: *UMax* = 2*TMax* + 1. All of the bit patterns that denote negative numbers in two's-complement notation become positive values in an unsigned representation.

|       |      |         | Word<br>size   | w                          |
|-------|------|---------|----------------|----------------------------|
| Value | 8    | 16      | 32             | 64                         |
| UMaxw | 0xFF | 0xFFFF  | 0xFFFFFFFF     | 0xFFFFFFFFFFFFFFFF         |
|       | 255  | 65,535  | 4,294,967,295  | 18,446,744,073,709,551,615 |
| TMinw | 0x80 | 0x8000  | 0x80000000     | 0x8000000000000000         |
|       | −128 | −32,768 | −2,147,483,648 | −9,223,372,036,854,775,808 |
| TMaxw | 0x7F | 0x7FFF  | 0x7FFFFFFF     | 0x7FFFFFFFFFFFFFFF         |
|       | 127  | 32,767  | 2,147,483,647  | 9,223,372,036,854,775,807  |
| −1    | 0xFF | 0xFFFF  | 0xFFFFFFFF     | 0xFFFFFFFFFFFFFFFF         |
| 0     | 0x00 | 0x0000  | 0x00000000     | 0x0000000000000000         |

**Examples (w = 4):**
- $B2T_4([0001]) = 1$
- $B2T_4([0101]) = 5$
- $B2T_4([1011]) = -8 + 2 + 1 = -5$
- $B2T_4([1111]) = -8 + 4 + 2 + 1 = -1$
- $TMin_4 = B2T_4([1000]) = -8$
- $TMax_4 = B2T_4([0111]) = 7$

**Important numbers across word sizes:**

| Value | 8-bit | 16-bit | 32-bit | 64-bit |
|-------|-------|--------|--------|--------|
| $UMax_w$ | 0xFF (255) | 0xFFFF (65,535) | 0xFFFFFFFF (4,294,967,295) | 0xFFFFFFFFFFFFFFFF (18,446,744,073,709,551,615) |
| $TMin_w$ | 0x80 (-128) | 0x8000 (-32,768) | 0x80000000 (-2,147,483,648) | 0x8000000000000000 (-9,223,372,036,854,775,808) |
| $TMax_w$ | 0x7F (127) | 0x7FFF (32,767) | 0x7FFFFFFF (2,147,483,647) | 0x7FFFFFFFFFFFFFFF (9,223,372,036,854,775,807) |
| -1 | 0xFF | 0xFFFF | 0xFFFFFFFF | 0xFFFFFFFFFFFFFFFF |
| 0 | 0x00 | 0x0000 | 0x00000000 | 0x0000000000000000 |

### Alternative Representations

- **Ones' complement:** $B2O_w(\vec{x}) = -x_{w-1}(2^{w-1} - 1) + \sum_{i=0}^{w-2} x_i 2^i$
  - Two encodings of zero: [00...0] = +0, [11...1] = -0
- **Sign-magnitude:** $B2S_w(\vec{x}) = (-1)^{x_{w-1}} \cdot \sum_{i=0}^{w-2} x_i 2^i$
  - Two encodings of zero: [00...0] = +0, [10...0] = -0

Almost all modern machines use two's complement.

The file <limits.h> in the C library defines a set of constants

---

## 2.2.4 Conversions Between Signed and Unsigned

Conversion preserves the bit pattern, not the numeric value. For the same w-bit pattern:

- $T2U_w(x) = B2U_w(T2B_w(x))$ — two's complement to unsigned
- $U2T_w(u) = B2T_w(U2B_w(u))$ — unsigned to two's complement

**Two's complement to unsigned:**
$$T2U_w(x) = \begin{cases} x + 2^w, & x < 0 \\ x, & x \geq 0 \end{cases}$$

**Derivation:** Comparing $B2U_w$ and $B2T_w$, the difference is $x_{w-1}2^w$:
$$B2U_w(\vec{x}) = B2T_w(\vec{x}) + x_{w-1}2^w$$
$$T2U_w(x) = x + x_{w-1}2^w$$

When $x$ is negative ($x_{w-1} = 1$), $T2U_w(x) = x + 2^w$.

**Unsigned to two's complement:**
$$U2T_w(u) = \begin{cases} u, & u \leq TMax_w \\ u - 2^w, & u > TMax_w \end{cases}$$

**Derivation:**
$$U2T_w(u) = -u_{w-1}2^w + u$$

When $u > TMax_w$ ($u_{w-1} = 1$), $U2T_w(u) = u - 2^w$.

**Summary:** Values in $[0, TMax_w]$ have identical unsigned and two's complement representations. Outside this range, conversion involves adding or subtracting $2^w$.

**Examples (16-bit):**
- $T2U_{16}(-12{,}345) = -12{,}345 + 2^{16} = 53{,}191$
- $U2T_{16}(53{,}191) = 53{,}191 - 2^{16} = -12{,}345$

---

## 2.2.5 Signed vs. Unsigned in C

- Default integer constants are signed; suffix `U` makes them unsigned.
- Casting preserves bit patterns, effectively applying $T2U_w$ or $U2T_w$.
- Implicit casting: when an expression has mixed signed/unsigned operands, the signed value is implicitly cast to unsigned.

**Promotion rules effects:** Comparisons like $-1 < 0U$ evaluate as false because $-1$ is cast to unsigned ($UMax_w$), yielding $UMax_w < 0$, which is false.

---

## 2.2.6 Expanding the Bit Representation

**Zero extension (unsigned):** Add leading zeros.
$$B2U_w([u_{w-1}, \dots, u_0]) = B2U_{w'}([0, \dots, 0, u_{w-1}, \dots, u_0])$$

**Sign extension (two's complement):** Add copies of the most significant bit.
$$B2T_w([x_{w-1}, \dots, x_0]) = B2T_{w'}([x_{w-1}, \dots, x_{w-1}, x_{w-1}, x_{w-2}, \dots, x_0])$$

**Proof by induction (base case: extend by 1 bit):**
$$B2T_{w+1}([x_{w-1}, x_{w-1}, x_{w-2}, \dots, x_0]) = -x_{w-1}2^w + \sum_{i=0}^{w-1} x_i 2^i$$
$$= -x_{w-1}2^w + x_{w-1}2^{w-1} + \sum_{i=0}^{w-2} x_i 2^i$$
$$= -x_{w-1}(2^w - 2^{w-1}) + \sum_{i=0}^{w-2} x_i 2^i$$
$$= -x_{w-1}2^{w-1} + \sum_{i=0}^{w-2} x_i 2^i$$
$$= B2T_w([x_{w-1}, x_{w-2}, \dots, x_0])$$

Since $2^w - 2^{w-1} = 2^{w-1}$, the value is preserved.

**Conversion ordering matters:** In C, `(unsigned) sx` for a `short sx` is equivalent to `(unsigned)(int)sx` (change size first, then type), not `(unsigned)(unsigned short)sx`.

---

## 2.2.7 Truncating Numbers

Truncating a w-bit value to k bits drops the $w-k$ high-order bits.

**Unsigned truncation:**
$$B2U_k([x_{k-1}, \dots, x_0]) = B2U_w([x_{w-1}, \dots, x_0]) \bmod 2^k$$

**Derivation:**
$$B2U_w(\vec{x}) \bmod 2^k = \left[\sum_{i=0}^{w-1} x_i 2^i\right] \bmod 2^k = \sum_{i=0}^{k-1} x_i 2^i = B2U_k([x_{k-1}, \dots, x_0])$$

Since $2^i \bmod 2^k = 0$ for $i \geq k$, the high-order bits vanish.

**Two's complement truncation:**
$$B2T_k([x_{k-1}, \dots, x_0]) = U2T_k\left(B2U_w([x_{w-1}, \dots, x_0]) \bmod 2^k\right)$$

First compute $x \bmod 2^k$ as an unsigned value, then convert to two's complement via $U2T_k$.

---

## 2.2.8 Advice on Signed vs. Unsigned

Implicit casting from signed to unsigned is a common source of bugs. The key pitfalls:

1. **Loop bounds with unsigned counters:** `for (i = 0; i <= length-1; i++)` when `length` is `unsigned` and `length = 0` causes `length-1` to wrap to $UMax$.
2. **Subtraction of unsigned values:** `strlen(s) - strlen(t) > 0` yields incorrect results when `strlen(s) < strlen(t)` due to unsigned wraparound.

**Avoidance strategies:**
- Avoid unsigned types when possible (as Java does).
- Use explicit casts where mixed types are unavoidable.
- Use direct comparison (`strlen(s) > strlen(t)`) instead of subtraction.
- Use signed loop counters.

---

## Practice Problem Solutions

### Practice Problem 2.17

Assuming w = 4, fill in the table with binary, B2U4(x), and B2T4(x):

| Hexadecimal | Binary | $B2U_4(x)$ | $B2T_4(x)$ |
|-------------|--------|-----------|------------|
| 0xA | [1010] | $2^3 + 2^1 = 8 + 2 = \mathbf{10}$ | $-2^3 + 2^1 = -8 + 2 = \mathbf{-6}$ |
| 0x1 | [0001] | $2^0 = \mathbf{1}$ | $2^0 = \mathbf{1}$ |
| 0xB | [1011] | $2^3 + 2^1 + 2^0 = 8 + 2 + 1 = \mathbf{11}$ | $-2^3 + 2^1 + 2^0 = -8 + 2 + 1 = \mathbf{-5}$ |
| 0x2 | [0010] | $2^1 = \mathbf{2}$ | $2^1 = \mathbf{2}$ |
| 0x7 | [0111] | $2^2 + 2^1 + 2^0 = 4 + 2 + 1 = \mathbf{7}$ | $2^2 + 2^1 + 2^0 = 4 + 2 + 1 = \mathbf{7}$ |
| 0xC | [1100] | $2^3 + 2^2 = 8 + 4 = \mathbf{12}$ | $-2^3 + 2^2 = -8 + 4 = \mathbf{-4}$ |

Notice that for hex digits 0x1, 0x2, and 0x7 (MSB = 0), unsigned and two's complement values are identical. For 0xA, 0xB, and 0xC (MSB = 1), the two's complement values are negative, while the unsigned values exceed $TMax_4 = 7$.

---

### Practice Problem 2.19

Using the results from Problem 2.17, fill in $T2U_4(x)$:

| $x$ | $T2U_4(x)$ | Derivation |
|-----|-----------|------------|
| -1 | $\mathbf{15}$ | Pattern [1111]: $B2U_4([1111]) = 15$; or $T2U_4(-1) = -1 + 16 = 15$ |
| -5 | $\mathbf{11}$ | Pattern [1011]: $B2U_4([1011]) = 11$; or $T2U_4(-5) = -5 + 16 = 11$ |
| -6 | $\mathbf{10}$ | Pattern [1010]: $B2U_4([1010]) = 10$; or $T2U_4(-6) = -6 + 16 = 10$ |
| -4 | $\mathbf{12}$ | Pattern [1100]: $B2U_4([1100]) = 12$; or $T2U_4(-4) = -4 + 16 = 12$ |
| 1 | $\mathbf{1}$ | Pattern [0001]: $B2U_4([0001]) = 1$; $T2U_4(1) = 1$ (nonnegative) |
| 8 | $\mathbf{8}$ | Pattern [1000]: $B2U_4([1000]) = 8$; $T2U_4(8) = 8$ (nonnegative). Note: 8 exceeds $TMax_4 = 7$, so this value cannot be represented as a 4-bit two's complement number under the standard definition. |

---

### Practice Problem 2.20

Explain how Equation 2.5 applies to the entries in Problem 2.19.

Equation 2.5: $$T2U_w(x) = \begin{cases} x + 2^w, & x < 0 \\ x, & x \geq 0 \end{cases}$$

For w = 4, $2^w = 16$. Applying the equation:

- $x = -1$ (negative): $T2U_4(-1) = -1 + 16 = 15$ ✓
- $x = -5$ (negative): $T2U_4(-5) = -5 + 16 = 11$ ✓
- $x = -6$ (negative): $T2U_4(-6) = -6 + 16 = 10$ ✓
- $x = -4$ (negative): $T2U_4(-4) = -4 + 16 = 12$ ✓
- $x = 1$ (nonnegative): $T2U_4(1) = 1$ ✓
- $x = 8$ (nonnegative): $T2U_4(8) = 8$ ✓

For negative $x$, the conversion adds $2^w = 16$, mapping negative numbers to large positive ones. For nonnegative $x$, the value is preserved. This matches the entries: negative inputs map to values ≥ 8 (i.e., $\geq 2^{w-1}$), while nonnegative inputs map to values ≤ 7 (i.e., $\leq TMax_w$).

---

### Practice Problem 2.21

Assuming a 32-bit program with two's-complement arithmetic, evaluate the following expressions:

| Expression | Type | Evaluation | Reasoning |
|------------|------|------------|-----------|
| $-2147483647-1 == 2147483648U$ | Unsigned | $\mathbf{1}$ | Left: $-2147483648$ (int $TMin_{32}$). Right: unsigned. Cast left to unsigned: $T2U_{32}(-2147483648) = 2147483648$. $2147483648U == 2147483648U$ → true. |
| $-2147483647-1 < 2147483647$ | Signed | $\mathbf{1}$ | Both int. $-2147483648 < 2147483647$ → true. |
| $-2147483647-1U < 2147483647$ | Unsigned | $\mathbf{0}$ | Left: $(-2147483647) - 1U$. Cast $-2147483647$ to unsigned: $2147483649U$. $2147483649U - 1U = 2147483648U$. Right: cast $2147483647$ to unsigned: $2147483647U$. $2147483648U < 2147483647U$ → false. |
| $-2147483647-1 < -2147483647$ | Signed | $\mathbf{1}$ | Both int. $-2147483648 < -2147483647$ → true. |
| $-2147483647-1U < -2147483647$ | Unsigned | $\mathbf{1}$ | Left: $2147483648U$ (as computed above). Right: $-2147483647$ (int) cast to unsigned: $T2U_{32}(-2147483647) = 2147483649U$. $2147483648U < 2147483649U$ → true. |

---

### Practice Problem 2.22

Show that each bit vector is a two's-complement representation of -4 using Equation 2.3.

**A. [1100] (w = 4):**
$$B2T_4([1100]) = -1 \cdot 2^3 + 1 \cdot 2^2 + 0 \cdot 2^1 + 0 \cdot 2^0 = -8 + 4 + 0 + 0 = \mathbf{-4}$$

**B. [11100] (w = 5):**
$$B2T_5([11100]) = -1 \cdot 2^4 + 1 \cdot 2^3 + 1 \cdot 2^2 + 0 \cdot 2^1 + 0 \cdot 2^0 = -16 + 8 + 4 + 0 + 0 = \mathbf{-4}$$

**C. [111100] (w = 6):**
$$B2T_6([111100]) = -1 \cdot 2^5 + 1 \cdot 2^4 + 1 \cdot 2^3 + 1 \cdot 2^2 + 0 \cdot 2^1 + 0 \cdot 2^0 = -32 + 16 + 8 + 4 + 0 + 0 = \mathbf{-4}$$

**Observation:** Vector B is vector A sign-extended by 1 bit (copied the MSB = 1 to the left). Vector C is vector A sign-extended by 2 bits. In each case, the added sign bit has weight $-2^{w-1}$, but converting the previous sign bit from weight $-2^{w-2}$ to $+2^{w-2}$ preserves the total value. Specifically, for the extension from w = 4 to w = 5: the new MSB contributes $-16$, while the old MSB changes from weight $-8$ to $+8$, giving a net change of $-16 + 8 + 8 = 0$.

---

### Practice Problem 2.23

Analyze the following functions (32-bit, two's complement, arithmetic right shift for signed, logical right shift for unsigned):

```c
int fun1(unsigned word) {
    return (int) ((word << 24) >> 24);
}
int fun2(unsigned word) {
    return ((int) word << 24) >> 24;
}
```

**A. Table of results:**

| $w$ | $fun1(w)$ | $fun2(w)$ |
|-----|----------|----------|
| 0x00000076 | $\mathbf{0x00000076}$ (118) | $\mathbf{0x00000076}$ (118) |
| 0x87654321 | $\mathbf{0x00000021}$ (33) | $\mathbf{0x00000021}$ (33) |
| 0x000000C9 | $\mathbf{0x000000C9}$ (201) | $\mathbf{0xFFFFFFC9}$ (-55) |
| 0xEDCBA987 | $\mathbf{0x00000087}$ (135) | $\mathbf{0xFFFFFF87}$ (-121) |

**Detailed derivations:**

**For $w = 0x00000076$:**
- *fun1:* $0x00000076 \ll 24 = 0x76000000$ (unsigned). Logical $\gg 24$: $0x00000076$. Cast to int: $118$.
- *fun2:* $(int)0x00000076 = 118$. $118 \ll 24 = 0x76000000$ (signed, MSB=0). Arithmetic $\gg 24$ (shift in 0s): $0x00000076 = 118$.

**For $w = 0x87654321$:**
- *fun1:* $0x87654321 \ll 24 = 0x21000000$ (unsigned). Logical $\gg 24$: $0x00000021$. Cast to int: $33$.
- *fun2:* $(int)0x87654321 = -2023406815$ (MSB=1). Bitwise left shift: $0x21000000$ (MSB=0, positive). Arithmetic $\gg 24$ (shift in 0s): $0x00000021 = 33$.

**For $w = 0x000000C9$:**
- *fun1:* $0x000000C9 \ll 24 = 0xC9000000$ (unsigned). Logical $\gg 24$: $0x000000C9$. Cast to int: $201$.
- *fun2:* $(int)0x000000C9 = 201$. $201 \ll 24 = 0xC9000000$ (signed, MSB=1). Arithmetic $\gg 24$ (sign extend): $0xFFFFFFC9$. As signed: $-55$.

**For $w = 0xEDCBA987$:**
- *fun1:* $0xEDCBA987 \ll 24 = 0x87000000$ (unsigned). Logical $\gg 24$: $0x00000087$. Cast to int: $135$.
- *fun2:* $(int)0xEDCBA987$ (signed, MSB=1). Left shift: $0x87000000$ (MSB=1, negative). Arithmetic $\gg 24$ (sign extend): $0xFFFFFF87$. As signed: $-121$.

**B. Description of each function:**

- **fun1:** Extracts the least significant byte (LSB) of `word` and returns it as a **zero-extended** (nonnegative) integer between 0 and 255. The left shift moves the low byte to the high byte position; the logical right shift brings it back to the low byte, discarding the higher-order bits and filling with zeros.

- **fun2:** Extracts the least significant byte (LSB) of `word` and returns it as a **sign-extended** (potentially negative) integer between -128 and 127. The cast to `int` preserves the bit pattern, then the left shift moves the low byte to the high position. The arithmetic right shift sign-extends the byte, propagating the MSB of the shifted value.

---

### Practice Problem 2.24

Truncating 4-bit values to 3-bit values:

| Original Hex | Truncated Hex | Unsigned Original | Unsigned Truncated | Signed Original | Signed Truncated |
|--------------|---------------|--------------------|--------------------|-----------------|-------------------|
| 0x1 (0001) | 0x1 (001) | 1 | 1 | 1 | 1 |
| 0x3 (0011) | 0x3 (011) | 3 | 3 | 3 | 3 |
| 0x5 (0101) | 0x5 (101) | 5 | 5 | 5 | -3 |
| 0xC (1100) | 0x4 (100) | 12 | 4 | -4 | -4 |
| 0xE (1110) | 0x6 (110) | 14 | 6 | -2 | -2 |

**Verification using Equations 2.9 and 2.10:**

Equation 2.9 (unsigned truncation): $B2U_k(\vec{x}') = B2U_w(\vec{x}) \bmod 2^k$

For $0xC$: $B2U_4([1100]) = 12$. $12 \bmod 2^3 = 12 \bmod 8 = 4$. $B2U_3([100]) = 4$ ✓

Equation 2.10 (two's complement truncation): $B2T_k(\vec{x}') = U2T_k(B2U_w(\vec{x}) \bmod 2^k)$

For $0x5$: $B2U_4([0101]) = 5$. $5 \bmod 8 = 5$. $U2T_3(5) = 5 - 2^3 = 5 - 8 = -3 = B2T_3([101])$ ✓
For $0xC$: $12 \bmod 8 = 4$. $U2T_3(4) = 4$ (since $4 \leq TMax_3 = 3$? No, $TMax_3 = 3$, so $4 > 3$, therefore $U2T_3(4) = 4 - 8 = -4 = B2T_3([100])$) ✓
For $0xE$: $14 \bmod 8 = 6$. $U2T_3(6) = 6 - 8 = -2 = B2T_3([110])$ ✓

---

### Practice Problem 2.25

**Buggy code:**
```c
float sum_elements(float a[], unsigned length) {
    int i;
    float result = 0;
    for (i = 0; i <= length-1; i++)
        result += a[i];
    return result;
}
```

**Why it fails when `length = 0`:**

When `length = 0` (unsigned), the expression `length - 1` evaluates to $0 - 1 = UMax_{32} = 4{,}294{,}967{,}295$ due to unsigned wraparound. The loop condition becomes `i <= 4294967295`, which is effectively always true for any 32-bit signed `i` (since `i` will be cast to unsigned for the comparison). The loop will access memory far beyond the array bounds until a segmentation fault occurs.

**Fix:** Change the loop condition to avoid unsigned underflow, or use a signed type for `length`:

```c
float sum_elements(float a[], unsigned length) {
    int i;
    float result = 0;
    for (i = 0; i < length; i++)  /* Changed from i <= length-1 to i < length */
        result += a[i];
    return result;
}
```

Or alternatively, make `length` a signed `int`.

---

### Practice Problem 2.26

**Buggy code:**
```c
int strlonger(char *s, char *t) {
    return strlen(s) - strlen(t) > 0;
}
```

**A. Cases producing incorrect results:**

The function produces incorrect results when `strlen(s) < strlen(t)` (i.e., when string `s` is shorter than string `t`). For example, `strlonger("abc", "hello")` returns 1 (true) even though "abc" is shorter.

**B. Explanation:**

`strlen` returns type `size_t`, which is an unsigned integer type (typically `unsigned int` on 32-bit systems, `unsigned long long` on 64-bit systems). When `strlen(s) < strlen(t)`, the subtraction `strlen(s) - strlen(t)` yields a negative mathematical result, but because both operands are unsigned, the result wraps modulo $2^{32}$ (or $2^{64}$), producing a large positive value. This large positive value is always $> 0$, so the function incorrectly returns 1.

**C. Fix:**

Use a direct comparison instead of subtraction:

```c
int strlonger(char *s, char *t) {
    return strlen(s) > strlen(t);
}
```

Alternatively, cast to a signed type before subtracting:

```c
int strlonger(char *s, char *t) {
    return (int)strlen(s) - (int)strlen(t) > 0;
}
```

The direct comparison approach is cleaner and avoids any risk of overflow.
