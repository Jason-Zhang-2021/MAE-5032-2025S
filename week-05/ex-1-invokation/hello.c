#include <stdio.h>

#define PI 3.14159
#define SQUARE(x) ((x) * (x))

int main()
{
  // print message
  printf("Hello world!\n");

#ifdef DEBUG
  double area = PI * SQUARE(5);
  printf("Area is %e \n", area);
#endif

  return 0;
}

//EOF
