#include "provided.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input number");
  }
  size_t sz = 0;
  ssize_t len = 0;
  size_t key_len1 = 0;
  // size_t key_len2 = 0;
  char * line = NULL;
  int flag = 1;  //odd:-1 even:1
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "An error occured when opening a file!\n");
    exit(EXIT_FAILURE);
  }
  const char * replacedWord = NULL;
  if (f == NULL) {
    fprintf(stderr, "Fail to open the file");
  }
  while ((len = getline(&line, &sz, f)) >= 0) {
    char * p1 = NULL;  //find 1st '_'
    char * p2 = NULL;  //find 2st '_'
    char newStr[500] = {'\0'};
    for (ssize_t i = 0; i < len; i++) {
      if (*(line + i) == '_') {
        flag = -flag;

        if (flag == -1) {
          char temp1[500] = {'\0'};
          p1 = line + i;
          if (p2 == NULL) {
            key_len1 = p1 - line;
            strncpy(temp1, line, key_len1);
            strcpy(newStr, temp1);
            memset(temp1, 0, 500);
          }
          else {
            char temp1[500] = {'\0'};
            key_len1 = p1 - p2 - 1;
            strncpy(temp1, p2 + 1, key_len1);
            strcat(newStr, temp1);
            memset(temp1, 0, strlen(temp1));
          }
        }
        if (flag == 1) {
          p2 = line + i;
          replacedWord = chooseWord(NULL, NULL);  //will return "cat"
                                                  //int word_len = strlen(replacedWord);
          strcat(newStr, replacedWord);
        }
      }
    }

    if (flag == -1) {
      fprintf(stderr, "Missing closing uderscore!\n");
      free(line);
      fclose(f);
      exit(EXIT_FAILURE);
    }
    p1 = line + len;  //p1 points at "\n"   (\n\0)
    char temp3[500] = {'\0'};
    if (p2) {
      strncpy(temp3, p2 + 1, p1 - p2);
    }
    else {  //p2 == NULL
      strncpy(temp3, line, len);
    }
    strcat(newStr, temp3);
    memset(temp3, 0, strlen(temp3));

    printf("%s", newStr);
    free(line);
    line = NULL;
  }  //end of while
  free(line);
  fclose(f);
  return EXIT_SUCCESS;
}
