#include "provided.h"
#include "rand_story.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/*category_t * divString(const char * line) {
  const char * p = strchr(line, ':');
  const char * x = strchr(line, '\n');
  category_t * newCat = malloc(sizeof(*newCat));
  size_t name_len = p - line;
  newCat->name = malloc((name_len + 1) * sizeof(*(newCat->name)));
  strncpy(newCat->name, line, name_len);
  newCat->name[name_len] = '\0';

  size_t word_len = x - p - 1;
  newCat->words = malloc(sizeof(*(newCat->words)));
  newCat->words[0] = malloc((word_len + 1) * sizeof(*(newCat->words[0])));
  strncpy(*(newCat->words), p + 1, word_len);
  newCat->words[0][word_len] = '\0';
  newCat->n_words = 1;
  return newCat;
  }*/
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
/*void freeStr(catarray_t * array) {
  for (size_t i = 0; i < array->n; i++) {
    category_t * cur_cat = (array->arr) + i;
    free(cur_cat->name);
    for (size_t j = 0; j < cur_cat->n_words; j++) {
      free(cur_cat->words[j]);
    }
    free(cur_cat->words);
  }
  free(array->arr);
  free(array);
  }*/
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
    fprintf(stderr, "Fail to open file");
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
