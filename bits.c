/*Modern computers store and process information represented as two-valued
signals. These lowly binary digits, or bits, form the basis of the digital revolution.*/


/*Computer representations use a limited number of bits to encode a number,
and hence some operations can overflow when the results are too large to be rep
resented.*/ 
#include<stdio.h>
int main(){
  printf("%d",200*300*400*500);
  return 0;
}
// When we complie the Above function we get a warning

/* bits.c: In function ‘main’:
bits.c:8:26: warning: integer overflow in expression of type ‘int’ results in ‘-884901888’ [-Woverflow]
    8 |   printf("%d",200*300*400*500);*/

// The Output of it is a negative number = -884901888
