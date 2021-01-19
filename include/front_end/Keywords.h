#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define true 1
#define false 0
#define BUCKET_SIZE 997
#define N 21

struct KeywordNode
{
    char keyword[51];
    struct KeywordNode* next;
};
typedef struct KeywordNode* list;

void initKeywords();
int isKeyword(char* word);
void freeKeywords();
