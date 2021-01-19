#include "Keywords.h"

static list bucket[BUCKET_SIZE];

static char* keywords[N] = 
{
    "class", "constructor", "function", "method", "field", "static", "var", "int",
    "char", "boolean", "void", "true", "false", "null", "this", "let", "do", "if",
    "else", "while", "return"
};

static unsigned int getHash(char *str);

void initKeywords()
{
    memset(bucket, 0, sizeof(bucket));
    for (int i = 0; i < N; ++i)
    {
        char* keyword = keywords[i];
        unsigned int hash = getHash(keyword);
        struct KeywordNode* pnode = (struct KeywordNode*)malloc(sizeof(struct KeywordNode));
        strcpy(pnode->keyword, keyword);
        pnode->next = NULL;
        if (bucket[hash] == NULL)
        {
            bucket[hash] = pnode;
        }    
        else
        {
            struct KeywordNode* p = bucket[hash];
            bucket[hash] = pnode;
            pnode->next = p;
        }
    }
}

int isKeyword(char* word)
{
    unsigned int hash = getHash(word);
    if (bucket[hash] == NULL)
        return false;
    struct KeywordNode* p = bucket[hash];
    while (p != NULL)
    {
        if (!strcmp(word, p->keyword))
            return true;
        p = p->next;
    }
    return false;
}

void freeKeywords()
{
    for (int i = 0; i < BUCKET_SIZE; ++i)
    {
        if (bucket[i] == NULL) 
            continue;
        struct KeywordNode* p = bucket[i];
        while (p != NULL)
        {
            struct KeywordNode* pnext = p->next;
            free(p);
            p = pnext;
        }
        bucket[i] = NULL;
    }
}

static unsigned int getHash(char *str)
{ 
    register unsigned int h = 0; 
    register unsigned char *p; 
    for(p = (unsigned char*)str; *p ; p++) 
    h = 31 * h + *p; 
    return h%BUCKET_SIZE;
} 
