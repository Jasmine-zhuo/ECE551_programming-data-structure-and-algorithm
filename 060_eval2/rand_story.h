#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//any functions you want your main to use
category_t * divString(const char * line);
void addString(const char * line, catarray_t * array);
void freeStr(catarray_t * array);
void parseArray(catarray_t * catarray, FILE * f);
void replace(FILE * f, catarray_t * array, category_t * usedWords);
#endif
