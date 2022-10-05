#include <pandemic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
country_t parseLine(char * line) {
  country_t country;
  char * ptr;
  long num;

  if (line == NULL) {
    fprintf(stderr, "Line contains nothing\n");
    exit(EXIT_FAILURE);
  }
  num = strtol(line, &ptr, 10);
  ctrcpy(country.name, &ptr);
  country.population = num;
  return country;
}
