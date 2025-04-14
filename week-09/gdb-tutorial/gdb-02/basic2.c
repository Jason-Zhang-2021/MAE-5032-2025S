#include "black_box.h"

void crash(int *i)
{
  *i = 1;
}

void f(int * i)
{
  int * j = i;
  j = complicated(j);
  j = sophisticated(j);
  crash(j);
}

int main()
{
  int i;
  f(&i);
  return 0;
}


