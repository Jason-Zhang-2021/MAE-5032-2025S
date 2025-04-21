#include <stdio.h>

int main()
{
  int j = 3;
  int k = 7;
  j += k;
  k = j * 2;
  int * l = new int [5];
  l[4] = 100.0;
  printf("l[4] is %d \n", l[4]);
  return 0;
}

// EOF
