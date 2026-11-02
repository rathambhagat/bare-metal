# 2.3 Integer Arithmetic

Adding two positive numbers can yield a negative result, and that the comparison x<y can yield a different
result than the comparison x-y < 0. These properties are artifacts of the finite nature of computer arithmetic.

## 2.3.1 Unsigned Addition

Two non negative number x and y, such that x ≥ 0, y < $2^w$. Each of these values can be represented by a w-bit unsigned number. If we compute their sum, we have a possible range of 0 <= x+y <= $2^{w+1}$ - 1. Representing this sum could require w + 1 bits. And we would keep the sum as (w+1) and add another value we would get a (w+2) sum showing that "word size inflation" , means we cannot put any bound on the word size required to fully represent the represent of the arithmetic operations. Some programming langauge support arbitary size Arithmetic. 


