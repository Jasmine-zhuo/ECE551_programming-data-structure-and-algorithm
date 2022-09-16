#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  if (y == 0)
    return 1;
  else
    return power(x, y - 1) * x;
}

int main(void) {
  unsigned x = 0;
  unsigned y = 0;
  power(x, y);
  return 0;
}
