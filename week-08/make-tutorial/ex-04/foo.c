#include <stdio.h>
#include "bar.h"
#include "hello.h"

int c=3;
int d=4;

int main()
{
  int a=2;
  double m = 3.1415926535897932;
  printf("get(%e) = %e\n", m, get(m) );
  return (bar(a*c*d));
}
