#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  //printf("1");
  counts_t * p = malloc(sizeof(*p));
  p->count_array = NULL;
  p->numCounts = 0;
  p->unknown = 0;
  return p;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  //printf("2");
  if (name == NULL) {
    c->unknown++;
    return;
  }
  size_t j = 0;
  for (j = 0; j < c->numCounts; j++) {
    if (!(strcmp(c->count_array[j].string, name))) {
      c->count_array[j].count++;
      break;
    }
  }
  if (j == c->numCounts) {
    c->count_array =
        realloc(c->count_array, sizeof(*(c->count_array)) * (c->numCounts + 1));
    (c->count_array[c->numCounts]).string =
        strdup(name);  //name is const, cannot assign to another pointer, so strdup, copy.
    (c->count_array[c->numCounts]).count = 1;  //add the first string
    c->numCounts++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  //printf("3");
  for (size_t i = 0; i < c->numCounts; i++) {
    fprintf(outFile, "%s : %zd\n", c->count_array[i].string, c->count_array[i].count);
  }
  if (c->unknown != 0) {
    fprintf(outFile, "<unknown> : %zd\n", c->unknown);
  }
  // if (fclose(outFile) != 0) {
  // fprintf(stderr, "Cannot close file");
  // }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  //printf("4");
  for (size_t i = 0; i < c->numCounts; i++) {
    free(c->count_array[i].string);
    //free(c->count_array[i]);
  }
  free(c->count_array);
  free(c);
}
