#include "myfun.h"

int main()
{
  int x = 16;
  
  x = mystery(x);

  if(x%2 ==0) print_even();
  else print_odd();

  return 0;
}


