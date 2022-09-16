#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
bool run_check(unsigned x, unsigned y, unsigned expected_ans) {
  return (expected_ans != power(x, y));
}

void main() {
  if (run_check(0, 0, 1)) {
    exit(EXIT_FAILURE);
  }
  if (run_check(2, 0, 1)) {
    exit(EXIT_FAILURE);
  }
  if (run_check(2, 3, 8)) {
    exit(EXIT_FAILURE);
  }
  if (run_check(-1, -1, -1)) {
    exit(EXIT_FAILURE);
  }
  if (run_check(-2, 0, 1)) {
    exit(EXIT_FAILURE);
  }
  if (run_check(0, 5, 0)) {
    exit(EXIT_FAILURE);
  }
  if (run_check(1, 5, 1)) {
    exit(EXIT_FAILURE);
  }
  if (run_check(-2, 3, -8)) {
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
