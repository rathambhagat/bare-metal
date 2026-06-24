#include<stdio.h>
int main(){
  short int v = -12345;
  unsigned short uv = (unsigned short) v;
  printf("v=%d, uv = %u\n",v,uv);
  return 0;
}
/* on a two's Complement Machine this code gives v = -12345 and uv = 53191 */
