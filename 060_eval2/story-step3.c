#include "provided.h"
#include "rand_story.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Wrong input number");
    exit(EXIT_FAILURE);
  }
  catarray_t * array = malloc(sizeof(*array));
  category_t * usedWords = malloc(sizeof(*usedWords));  //record words
  usedWords->name = NULL;
  usedWords->n_words = 0;
  usedWords->words = NULL;
  FILE * f1 = fopen(argv[1], "r");
  if (f1 == NULL) {
    fprintf(stderr, "An error occured when opening a file!\n");
    free(array);
    free(usedWords);
    exit(EXIT_FAILURE);
  }
  parseArray(array, f1);  //step 2 abstraction
  fclose(f1);
  FILE * f2 = fopen(argv[2], "r");
  if (f2 == NULL) {
    fprintf(stderr, "An error occured when opening a file!\n");
    freeStr(array);
    free(usedWords);
    exit(EXIT_FAILURE);
  }
  replace(f2, array, usedWords);  //step 1 abstraction
  freeStr(array);
  free(usedWords);

  fclose(f2);
  return EXIT_SUCCESS;
}
