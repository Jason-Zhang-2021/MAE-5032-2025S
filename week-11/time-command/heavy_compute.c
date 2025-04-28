// heavy_compute.c
#include <stdio.h>

int main() 
{
  double sum = 0;
  for (long long i = 0; i < 1e9; ++i) 
    sum += i * 0.000001;
  printf("Sum: %f\n", sum);
  return 0;
}

