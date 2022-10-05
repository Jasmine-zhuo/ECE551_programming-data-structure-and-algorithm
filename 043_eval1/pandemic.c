#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  long num;
  if (line == NULL) {
    fprintf(stderr, "Line contains nothing\n");
    exit(EXIT_FAILURE);
  }
  char * res;
  char * ptr;
  size_t size;
  res = strchr(line, ',');
  num = strtol(res + 1, &ptr, 10);
  size = strlen(line) - strlen(res);
  memcpy(ans.name, line, size);
  *(ans.name + size) = '\0';
  if (num < 0) {
    fprintf(stderr, "Invalid input.\n");
    exit(EXIT_FAILURE);
  }
  if (size < 0) {
    fprintf(stderr, "Invalid input.\n");
    exit(EXIT_FAILURE);
  }
  if (line == NULL) {
    fprintf(stderr, "Invalid input.\n");
    exit(EXIT_FAILURE);
  }
  ans.population = num;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  const int day = 7;
  for (size_t i = 0; i < (n_days - 6); i++) {
    *(avg + i) =
        ((*(data + i)) + (*(data + i + 1)) + (*(data + i + 2)) + (*(data + i + 3)) +
         (*(data + i + 4)) + (*(data + i + 5)) + (*(data + i + 6))) /
        day;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  double sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    for (size_t j = 0; j < i; j++) {
      sum = sum + (*(data + j));
    }
    *(cum + i) = (sum * 100000) / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  unsigned max = 0;
  size_t line = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max) {
        max = data[i][j];
        line = i;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", countries[line].name, max);
}
