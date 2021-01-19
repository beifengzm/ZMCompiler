#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hash.h"

int main(int argc, char** argv)
{
    struct Hash* phash = newHash();
    // char* str[8] = {"while", "function", "int", "char", "for", "if", "return", "assign"};
    char* str[8] = {"while", "het", "while", "}", "het", "vfdabadfb", "false", "function"};
    for (int i = 0; i < 8; i = i+1)
    {
        int result = putKV(phash, str[i], strlen(str[i])+1, &i, sizeof(int));
        printf("%s---->%s\n", str[i], result==1?"Yes":"No");
        // int result = putKV(phash, &i, sizeof(int), str[i], strlen(str[i])+1);
        // printf("%d---->%s\n", i, result==1?"Yes":"No");
    }
    for (int i = 0; i < 8; i = i+2)
    {
        removeKey(phash, str[i], strlen(str[i])+1);
        printf("current size: %u\n", getSize(phash));
    }
    // for (int i = 0; i < 8; i = i+2)
    // {
    //     // int result = putKV(phash, str[i], strlen(str[i])+1, &i, sizeof(int));
    //     // printf("%s---->%s\n", str[i], result==1?"Yes":"No");
    //     int result = putKV(phash, &i, sizeof(int), str[i+1], strlen(str[i+1])+1);
    //     printf("%d---->%s\n", i, result==1?"Yes":"No");
    // }
    for (int i = 0; i < 8; ++i)
    {
        // int result = putKV(phash, str[i], strlen(str[i])+1, &i, sizeof(int));
        // printf("%s---->%s\n", str[i], result==1?"Yes":"No");
        int* pValue = (int*)getValue(phash, str[i], strlen(str[i])+1);
        printf("%s---->%d\n", str[i], pValue == NULL?-1:*pValue);
    }
    freeHash(phash);
    return 0;
}