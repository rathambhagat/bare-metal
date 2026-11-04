#include<stdio.h>
/*int main(){
  short int v = -12345;
  unsigned short uv = (unsigned short) v;
  printf("v=%d, uv = %u\n",v,uv);
  return 0;
}*/
/* on a two's Complement Machine this code gives v = -12345 and uv = 53191 */

int main(){
    int x = -1;
    unsigned u = 2147483648;
    printf("x = %u = %d\n", x, x);
    printf("u = %u = %d\n", u, u);
    return 0;
}
/* Output for the above code when complied as a 64 bit program
  x = 4294967295 = -1
u = 2147483648 = -2147483648 
Output for the Above code when complied as a 32 bit program 
x = 4294967295 = -1
u = 2147483648 = -2147483648
*/
