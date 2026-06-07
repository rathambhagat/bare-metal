# Boolean Alegbra Symbols
(~) -> NOT, flips the bits 0 to 1 and 1 to 0
(&) -> AND,Outputs 1 only if both input bits are 1 
(|) -> OR,outputs 1 if either (or both) input bits are 1
(^) -> EXCLUSIVE-OR,Outputs 1 only if the input bits are different (one is 0, the other is 1).

# Bit vectors
Bit Vectors: The machine doesn't just process one bit at a time. It applies these operations across entire strings of bits (bit vectors) simultaneously, matching up the bits position by position

# Set Encoding 
Set Encoding: Bit vectors mechanically represent finite sets, where a 1 at a specific position means that element is present, and a 0 means it is absent Because of this, & physically performs set intersection, | performs set union, and ~ performs set complement.

# XOR 
The XOR Annihilator: XOR mathematically forms a "Boolean ring" where every element is its own additive inverse. Mechanically, this means applying XOR to a value with itself strictly cancels it out to zero ( a ˆ a =0).

#### **Practice Problem 2.10 (solution page 182)**

As an application of the property that *a* ^ *a* = 0 for any bit vector *a*, consider the following program:

```
1 void inplace_swap(int *x, int *y) {
2 *y = *x ^ *y; /* Step 1 */
3 *x = *x ^ *y; /* Step 2 */
4 *y = *x ^ *y; /* Step 3 */
5 }
```

As the name implies, we claim that the effect of this procedure is to swap the values stored at the locations denoted by pointer variables x and y. Note that unlike the usual technique for swapping two values, we do not need a third location to temporarily store one value while we are moving the other. There is no performance advantage to this way of swapping; it is merely an intellectual amusement.

Starting with values *a* and *b* in the locations pointed to by x and y, respectively, fill in the table that follows, giving the values stored at the two locations after each step of the procedure. Use the properties of ^ to show that the desired effect is achieved. Recall that every element is its own additive inverse (that is, *a* ^ *a* = 0).

##### Solution 

| Step      | *x | *y |
|-----------|----|----|
| Initially | a  | b  |
| Step<br>1 | a  | a^b|
| Step<br>2 | b  | a^b|
| Step<br>3 | b  | a  |

#### **Practice Problem 2.11 (solution page 182)**

Armed with the function inplace\_swap from Problem 2.10, you decide to write code that will reverse the elements of an array by swapping elements from opposite ends of the array, working toward the middle.

You arrive at the following function:

```
1 void reverse_array(int a[], int cnt) {
2 int first, last;
3 for (first = 0, last = cnt-1;
4 first <= last;
5 first++,last--)
6 inplace_swap(&a[first], &a[last]);
7 }
```

When you apply your function to an array containing elements 1, 2, 3, and 4, you find the array now has, as expected, elements 4, 3, 2, and 1. When you try it on an array with elements 1, 2, 3, 4, and 5, however, you are surprised to see that the array now has elements 5, 4, 0, 2, and 1. In fact, you discover that the code always works correctly on arrays of even length, but it sets the middle element to 0 whenever the array has odd length.

- A. For an array of odd length cnt = 2*k* + 1, what are the values of variables first and last in the final iteration of function reverse\_array?
- B. Why does this call to function inplace\_swap set the array element to 0?
- C. What simple modification to the code for reverse\_array would eliminate this problem?

One common use of bit-level operations is to implement *masking* operations, where a mask is a bit pattern that indicates a selected set of bits within a word. As an example, the mask 0xFF (having ones for the least significant 8 bits) indicates the low-order byte of a word. The bit-level operation x & 0xFF yields a value consisting of the least significant byte of x, but with all other bytes set to 0. For example, with x = 0x89ABCDEF, the expression would yield 0x000000EF. The expression ~0 will yield a mask of all ones, regardless of the size of the data representation. The same mask can be written 0xFFFFFFFF when data type int is 32 bits, but it would not be as portable.

##### Solution
A ->  In the final iteration for an array of odd length cnt=2k+1, both first and last will be exactly equal to k.For your 5-element array example, both variables equal 2.
B -> Because first and last equal each other, inplace_swap receives two pointers to the exact same memory address.The very first step of the swap calculates *x ^ *y, which physically evaluates to a^a, immediately overwriting the data with 0.
C -> You just change the loop condition from first <= last to first < last.The exact middle element of an odd-length array doesn't actually need to move anyway, so stopping the loop right before the pointers overlap prevents the bug entirely.






