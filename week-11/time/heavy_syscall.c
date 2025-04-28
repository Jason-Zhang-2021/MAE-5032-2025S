#include <stdio.h>
#include <stdlib.h>

int main() 
{
  FILE *fp = fopen("testfile.txt", "w");
  for (long long i = 0; i < 1e7; ++i)
    fprintf(fp, "This is a line.\n");
  fclose(fp);
  int ret = system("rm -f testfile.txt");
  return 0;
}
// EOF
