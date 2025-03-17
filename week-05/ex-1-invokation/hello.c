#include <stdio.h>

#define PI 3.14159
#define SQUARE(x) ((x) * (x))

int main()
{
  // print message
  printf("Hello world!\n");

  double area = PI * SQUARE(5);

  printf("Area is %e", area);

#ifdef DEBUG
  printf("Debug mode enabled!\n");
#endif

  return 0;
}

//EOF
