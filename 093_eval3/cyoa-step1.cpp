#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

int main(int argc, char * argv[]) {
  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, stdin) != -1) {
    const char * temp = line;
  }
}
