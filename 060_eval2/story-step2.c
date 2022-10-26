#include "provided.h"
#include "rand_story.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void addString_step2(const char * line, catarray_t * array) {
  category_t * newCat = NULL;
  newCat = divString(line);

  size_t i = 0;
  for (i = 0; i < array->n; i++) {
    category_t * cur_cat = (array->arr) + i;
    if (!strcmp(newCat->name, cur_cat->name)) {  //if same name

      cur_cat->n_words++;
      cur_cat->words =
          realloc(cur_cat->words, sizeof(*(cur_cat->words)) * (cur_cat->n_words));
      cur_cat->words[(cur_cat->n_words) - 1] = (newCat->words)[0];
      free(newCat->words);
      free(newCat->name);
      break;
    }
  }

  if (i == array->n) {
    (array->n)++;
    array->arr = realloc((array->arr), sizeof(*(array->arr)) * (array->n));
    category_t * target_cat = (array->arr) + ((array->n) - 1);

    target_cat->name = newCat->name;
    target_cat->words = newCat->words;
    target_cat->n_words = 1;
  }

  free(newCat);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input number");
  }
  size_t sz = 0;
  char * line = NULL;
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->arr = NULL;
  catarray->n = 0;

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "An error occured when opening a file!\n");
    free(catarray);
    exit(EXIT_FAILURE);
  }
  while (getline(&line, &sz, f) >= 0) {
    const char * p = strchr(line, ':');
    if (p == NULL) {
      fprintf(stderr, "Invalid input, there is no \" : \" in this line");
      free(line);
      freeStr(catarray);
      fclose(f);
      exit(EXIT_FAILURE);
    }

    addString_step2(line, catarray);
    free(line);
    line = NULL;
  }
  free(line);
  printWords(catarray);
  freeStr(catarray);
  fclose(f);
  return EXIT_SUCCESS;
}
