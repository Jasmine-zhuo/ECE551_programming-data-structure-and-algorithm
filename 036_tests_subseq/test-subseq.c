#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

bool check(int * array, size_t n, size_t ans_exp) {
  return (ans_exp != (maxSeq(array, n)));
}

int main() {
  {
    int test[] = {1};
    if (check(test, 0, 0))

      exit(EXIT_FAILURE);
  }
  {
    int test1[] = {1};
    if (check(test1, 1, 1))
      exit(EXIT_FAILURE);
  }
  {
    int test2[] = {1, 2};
    if (check(test2, 2, 2))
      exit(EXIT_FAILURE);
  }
  {
    int test3[] = {1, 2, 3};
    if (check(test3, 3, 3))
      exit(EXIT_FAILURE);
  }
  {
    int test4[] = {1, 2, 1, 3, 5};
    if (check(test4, 5, 3))
      exit(EXIT_FAILURE);
  }
  {
    int test5[] = {-1, 0, 1};
    if (check(test5, 3, 3))
      exit(EXIT_FAILURE);
  }
  {
    int test6[] = {1, 2, 1, 4, 6, 7, 8, -2};
    if (check(test6, 8, 5))
      exit(EXIT_FAILURE);
  }
  {
    int test7[] = {9, 8, 7, 6, 5, 4};
    if (check(test7, 4, 0))
      exit(EXIT_FAILURE);
  }
  {
    int test8[] = {6, 3, 5, 4, 6, 4, 7, 5};
    if (check(test8, 8, 2))
      exit(EXIT_FAILURE);
  }
  printf("success");
  exit(EXIT_SUCCESS);
}
