#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n) {
  size_t count = 1;
  size_t ans = 0;

  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  for (int i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      count++;
    }
    else {
      count = 1;
    }
    if (count > ans) {
      ans = count;
    }
  }
  return count;
}
