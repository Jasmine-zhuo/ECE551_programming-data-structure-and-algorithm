#include "rand_story.h"

#include "provided.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int isNumber(char * s) {
  for (int i = 0; s[i] != '\0'; i++) {
    if ((s[i] < '0') || (s[i] > '9')) {
      return -1;
    }
  }

  return 1;
}

void replace(FILE * f, catarray_t * array, category_t * usedWords) {
  size_t sz = 0;
  ssize_t len = 0;
  size_t key_len1 = 0;
  char * line = NULL;
  int flag = 1;  //odd:-1 even:1

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

        if (flag == -1) {  //read 1 '_'
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
        if (flag == 1) {  //read 2'_'
          const char * replacedWord = NULL;
          p2 = line + i;
          int length = p2 - p1 - 1;
          char current_cat[100];
          strncpy(current_cat, p1 + 1, length);
          current_cat[length] = '\0';
          int isNum = isNumber(current_cat);
          if (isNum == 1) {
            //Match from previously used words
            char * endPtr = &current_cat[length];
            size_t index = strtol(current_cat, &endPtr, 10);
            printf("The index we found is :%lu\n", index);
            if (index > usedWords->n_words) {
              fprintf(stderr, "There is no that many used words!Invalid index!\n");
              exit(EXIT_FAILURE);  //!!!!!ADD:EXIT THINGS
            }

            int real_index = usedWords->n_words - index;
            replacedWord = usedWords->words[real_index];
          }
          else {
            replacedWord = chooseWord(current_cat, array);  //will return "cat"
          }
          usedWords->words = realloc(
              usedWords->words, sizeof(*(usedWords->words)) * (usedWords->n_words + 1));
          (usedWords->n_words)++;
          *(usedWords->words + (usedWords->n_words - 1)) = strdup(replacedWord);
          //strcpy(usedWords->words[(usedWords->n_words) - 1], current_cat);

          strcat(newStr, replacedWord);
        }
      }
    }  //end of for

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
  return;
}  //end of replace

category_t * divString(const char * line) {
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
}  //end of divString
void addString(const char * line, catarray_t * array) {
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
}  //end of addString
void freeStr(catarray_t * array) {
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
}  //end of freeStr

void parseArray(catarray_t * catarray, FILE * f) {
  size_t sz = 0;
  char * line = NULL;
  catarray->arr = NULL;
  catarray->n = 0;
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

    addString(line, catarray);
    free(line);
    line = NULL;
  }
  free(line);
  printWords(catarray);

  return;
}
