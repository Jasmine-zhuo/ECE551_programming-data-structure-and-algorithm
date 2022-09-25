#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  size_t count = 0;
  for (int i = 0; i < n; i++) {
    if (array[i] < array[i + 1]) {
      count++;
    }
    else {
      count = 1;
    }
  }
  return count;
}
