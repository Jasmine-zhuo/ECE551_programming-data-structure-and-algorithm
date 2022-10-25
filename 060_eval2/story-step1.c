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
  // char * p1 = NULL;  //find 1st '_'
  //char * p2 = NULL;  //find 2nd '_'
  //  char * p3 = NULL;     //find '\0'
  //char temp1[500];  //front
  //  char temp2[500];  //tail
  //  char temp3[500];
  const char * replacedWord = NULL;
  if (f == NULL) {
    fprintf(stderr, "Fail to open the file");
  }
  while ((len = getline(&line, &sz, f)) >= 0) {
    //newStr = malloc(sizeof(*newStr) * len);
    char * p1 = NULL;  //find 1st '_'
    char * p2 = NULL;  //find 2st '_'
    char newStr[500];
    for (ssize_t i = 0; i < len; i++) {
      if (*(line + i) == '_') {
        flag = -flag;

        /*if(flag==-1){
	temp=line+1;
	}*/
        if (flag == -1) {
          char temp1[500];
          p1 = line + i;
          if (p2 == NULL) {
            key_len1 = p1 - line;
            strncpy(temp1, line, key_len1);
            strcpy(newStr, temp1);
            memset(temp1, 0, strlen(temp1));
          }
          else {
            char temp1[500];
            //printf("After a front _ was found, before copying into temp1, it is:%s\n",
            //       temp1);
            key_len1 = p1 - p2 - 1;
            strncpy(temp1, p2 + 1, key_len1);
            //printf("After a front _ was found, temp1 is:%s\n", temp1);
            strcat(newStr, temp1);
            //printf("After a front _ was found, we got:%s\n", newStr);
            memset(temp1, 0, strlen(temp1));
          }
          //newStr = realloc(newStr, sizeof(*newStr) * key_len1);
          //strcat(newStr, temp1);
        }
        if (flag == 1) {
          p2 = line + i;
          replacedWord = chooseWord(NULL, NULL);  //will return "cat"
                                                  //int word_len = strlen(replacedWord);
          // strcpy(temp2, replacedWord);
          //strcat(newStr, temp2);
          strcat(newStr, replacedWord);
          //newStr = realloc(newStr, sizeof(*newStr) * word_len);
          //printf("After a back _ was found, we got:%s\n", newStr);
        }
      }
    }
    //printf("Before temp3: %s\n", newStr);
    p1 = line + len;  //p1 points at "\n"   (\n\0)
    char temp3[500];
    strncpy(temp3, p2 + 1, p1 - p2);
    //newStr = realloc(newStr, sizeof(*newStr) * strlen(temp2));
    strcat(newStr, temp3);
    memset(temp3, 0, strlen(temp3));
    if (flag == -1) {
      printf("Wrong input format");
      exit(EXIT_FAILURE);
      //Add: Exit with an error status!
    }
    //char * p = strchr(line, '_');
    free(line);
    line = NULL;
    //free(newStr);
    //    newStr = NULL;

    printf("%s", newStr);
  }  //end of while
}
