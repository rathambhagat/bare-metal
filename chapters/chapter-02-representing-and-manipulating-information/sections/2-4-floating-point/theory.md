# 2.4 Floating Point

A floating-point representation encodes rational numbers of the form *V* = *x* × 2*y*. It is useful for performing computations involving very large numbers (|*V* | 0),

## 2.4.1 Fractional Binary Number

Decimal notation
$$d_m d_{m-1} \cdots d_1 d_0 \cdot d_{-1} d_{-2} \cdots d_{-n}$$
where each decimal digit  $d_i$  ranges between 0 and 9. This notation represents a value d defined as
$$d = \sum_{i=-n}^{m} 10^i \times d_i$$
The weighting of the digits is defined relative to the decimal point symbol ('.'), meaning that digits to the left are weighted by nonnegative powers of 10, giving integral values, while digits to the right are weighted by negative powers of 10, giving fractional values. For example,  $12.34_{10}$  represents the number  $1 \times 10^1 + 2 \times 10^0 + 3 \times 10^{-1} + 4 \times 10^{-2} = 12\frac{34}{100}$ .

Binary Notation
$$b_m b_{m-1} \cdots b_1 b_0 \cdot b_{-1} b_{-2} \cdots b_{-n+1} b_{-n}$$
$$b = \sum_{i=-n}^{m} 2^i \times b_i \tag{2.19}$$
The symbol '.' now becomes a *binary point*, with bits on the left being weighted by nonnegative powers of 2, and those on the right being weighted by negative powers of 2. For example,  $101.11_2$  represents the number  $1 \times 2^2 + 0 \times 2^1 + 1 \times 2^0 + 1 \times 2^{-1} + 1 \times 2^{-2} = 4 + 0 + 1 + \frac{1}{2} + \frac{1}{4} = 5\frac{3}{4}$ .

- **Practice Problem 2.46**

The imprecision of floating-point arithmetic can have disastrous effects. On February 25, 1991, during the first Gulf War, an American Patriot Missile battery in Dharan, Saudi Arabia, failed to intercept an incoming Iraqi Scud missile. The Scud struck an American Army barracks and killed 28 soldiers. The US General

Accounting Office (GAO) conducted a detailed analysis of the failure [76] and determined that the underlying cause was an imprecision in a numeric calculation. In this exercise, you will reproduce part of the GAO's analysis.

The Patriot system contains an internal clock, implemented as a counter that is incremented every 0.1 seconds. To determine the time in seconds, the program would multiply the value of this counter by a 24-bit quantity that was a fractional binary approximation to  $\frac{1}{10}$ . In particular, the binary representation of  $\frac{1}{10}$  is the nonterminating sequence 0.000110011[0011]  $\cdots$ <sub>2</sub>, where the portion in brackets is repeated indefinitely. The program approximated 0.1, as a value x, by considering just the first 23 bits of the sequence to the right of the binary point: x = 0.000110011001100110011001100. (See Problem 2.51 for a discussion of how they could have approximated 0.1 more precisely.)

- A. What is the binary representation of 0.1 x?
- B. What is the approximate decimal value of 0.1 x?
- C. The clock starts at 0 when the system is first powered up and keeps counting up from there. In this case, the system had been running for around 100 hours. What was the difference between the actual time and the time computed by the software?
- D. The system predicts where an incoming missile will appear based on its velocity and the time of the last radar detection. Given that a Scud travels at around 2,000 meters per second, how far off was its prediction?

Normally, a slight error in the absolute time reported by a clock reading would not affect a tracking computation. Instead, it should depend on the relative time between two successive readings. The problem was that the Patriot software had been upgraded to use a more accurate function for reading time, but not all of the function calls had been replaced by the new code. As a result, the tracking software used the accurate time for one reading and the inaccurate time for the other.
Solution:
A. \[\boxed{0.1-x=0.000000000000000000000001100110011\ldots_2}\]
B. \[\boxed{0.1-x=0.000000095367431640625}\] or \[\boxed{9.5367431640625\times10^{-8}}\]
C. \[\boxed{E=0.34332275390625\text{ seconds}}\]
D. \[\boxed{D\approx686.65\text{ meters}}\]

## 2.4.2 IEEE Floating-Point Representation

The IEEE floating-point standard represents a number in a form  $V = (-1)^s \times M \times 2^E$ :



