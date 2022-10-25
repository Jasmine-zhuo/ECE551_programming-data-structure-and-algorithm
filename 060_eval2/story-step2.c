#include "provided.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

category_t sepString(char * line) {
  for (size_t i = 0; i < num; i++) {
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input number");
  }
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Fail to oprn file");
  }
  while (getline(&line, &sz, f) >= 0) {
    char * end = strchr(line, '\n');
    /*if(end!=NULL){
      *end='\0'
      }*/
    sepString();
  }
}
