#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  int size;
  size = strlen(inputName);
  char * p = NULL;
  p = malloc(sizeof(p) * (size + 7));
  strncpy(p, inputName, size);
  *(p + size) = '.';
  *(p + size + 1) = 'c';
  *(p + size + 2) = 'o';
  *(p + size + 3) = 'u';
  *(p + size + 4) = 'n';
  *(p + size + 5) = 't';
  *(p + size + 6) = 's';
  *(p + size + 7) = '\0';
  return p;
}
