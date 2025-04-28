#include <stdio.h>
#include <stdlib.h>

void fill_array(int *arr, int size) {
  for (int i = 0; i <= size; ++i) { // BUG: should be i < size
    arr[i] = i * 2;
  }
}

int main() {
  int n = 10;
  int *data = (int *)malloc(n * sizeof(int));

  if (data == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  fill_array(data, n);

  printf("Data array:\n");
  for (int i = 0; i < n; ++i) {
    printf("%d ", data[i]);
  }
  printf("\n");

  free(data);
  return 0;
}

// EOF
