#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if ((argc != 4) && (argc != 3)) {
    fprintf(stderr, "Wrong input number");
    exit(EXIT_FAILURE);
  }
  int sym = 0;
  if (argc == 3) {
    sym = 1;
  }  //same with step 3
  char * choose = "-n";
  if (argc == 4) {
    if (!(strcmp(argv[1], choose))) {  //not repeat
      sym = -1;
    }
    else {  //invalid argument
      fprintf(stderr, "Invalid input argument");
      exit(EXIT_FAILURE);
    }
  }
  //printf("sym is %d\n", sym);
  catarray_t * array = malloc(sizeof(*array));
  category_t * usedWords = malloc(sizeof(*usedWords));  //record words
  usedWords->name = NULL;
  usedWords->n_words = 0;
  usedWords->words = NULL;
  FILE * f1 = fopen(argv[argc - 2], "r");
  if (f1 == NULL) {
    fprintf(stderr, "An error occured when opening a file!\n");
    free(array);
    free(usedWords);
    exit(EXIT_FAILURE);
  }
  parseArray(array, f1);  //step 2 abstraction
  fclose(f1);
  FILE * f2 = fopen(argv[argc - 1], "r");
  if (f2 == NULL) {
    fprintf(stderr, "An error occured when opening a file!\n");
    freeStr(array);
    free(usedWords);
    exit(EXIT_FAILURE);
  }

  replace(f2, array, usedWords, sym);  //step 1 abstraction
  freeStr(array);
  free(usedWords);

  fclose(f2);
  return EXIT_SUCCESS;
}
