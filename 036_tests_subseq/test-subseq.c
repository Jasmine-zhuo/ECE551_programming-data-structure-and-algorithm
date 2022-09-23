#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

bool check(int * array, size_t n, int ans_exp) {
  return (ans_exp != (maxSeq(array, n)));
}

int main() {
  {
      // int test[] = {};
      // if (check(test, 0, 0))
      // exit(EXIT_FAILURE);
  } {
    int test[] = {1};
    if (check(test, 1, 0))
      exit(EXIT_FAILURE);
  }
  {
    int test[] = {1, 2};
    if (check(test, 2, 2))
      exit(EXIT_FAILURE);
  }
  {
    int test[] = {1, 2, 3};
    if (check(test, 3, 3))
      exit(EXIT_FAILURE);
  }
  {
    int test[] = {1, 2, 1, 3, 5};
    if (check(test, 5, 3))
      exit(EXIT_FAILURE);
  }
  {
    int test[] = {-1, 0, 1};
    if (check(test, 3, 3))
      exit(EXIT_FAILURE);
  }
  {
    int test[] = {1, 2, 1, 4, 6, 7, 8, -2};
    if (check(test, 8, 5))
      exit(EXIT_FAILURE);
  }
  printf("success");
  exit(EXIT_SUCCESS);
}
