#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 10

int main (int argc,char **argv) {
  int i=0;
  
  while (i < N) {
    i++;
    if (argv[1] != NULL)
      printf("%s: %d\n", argv[1], i);
    else
      printf("%d\n", i);
  }

  assert(i==10);
  
  return EXIT_SUCCESS;
}
