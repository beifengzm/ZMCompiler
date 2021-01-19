#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hash.h"

static int putEntry(struct Hash* phash, struct HashEntry* pEntry);
static unsigned int getIndex(struct Hash* phash, const void* key, int nbyte);
static void expand(struct Hash* phash);
static void freeHashEntry(struct HashEntry* pEntry);

static struct HashEntry* newEntry(const void* key, nbyte_t nKey, 
                                  const void* value, nbyte_t nValue)
{
    struct HashEntry* pEntry;
    pEntry = (struct HashEntry*)malloc(sizeof(struct HashEntry));
    pEntry->key = (void*)malloc(nKey);
    memcpy(pEntry->key, key, nKey);
    pEntry->nKey = nKey;
    pEntry->value = (void*)malloc(nValue);
    memcpy(pEntry->value, value, nValue);
    pEntry->nValue = nValue;
    return pEntry;
}

struct Hash* newHash()
{
    struct Hash* phash;
    phash = (struct Hash*)malloc(sizeof(struct Hash));
    phash->capcity = 4;   // 起始桶容量为4
    phash->size = 0;
    phash->hashTable = (struct HashEntry**)malloc(sizeof(struct HashEntry*)*phash->capcity);
    memset(phash->hashTable, 0, sizeof(struct HashEntry*)*phash->capcity);
    phash->last = phash->next = NULL;
    return phash;
}

static unsigned int getIndex(struct Hash* phash, const void* key, int nbyte)
{
    unsigned int hashCode = 0;
    unsigned char* pbase = (unsigned char*)key;
    for (unsigned int i = 0; i < nbyte; ++i)
    {
        hashCode = hashCode*31 + *pbase++;
    }
    return hashCode&(phash->capcity-1);
}

int putKV(struct Hash* phash, const void* key, nbyte_t nKey, 
                    const void* value, nbyte_t nValue)
{
    if (phash->size/(double)phash->capcity >= 0.72)   // 装填因子大于等于0.75时扩充
    {
        expand(phash);
    }    

    struct HashEntry* pEntry = newEntry(key, nKey, value, nValue);
    int isRepeated = putEntry(phash, pEntry);
    if (isRepeated)
    {
        phash->size++;
    }
    return isRepeated;
}

int setValue(struct Hash* phash, const void* key, nbyte_t nKey, 
                        const void* value, nbyte_t nValue)
{
    unsigned int index = getIndex(phash, key, nKey);
    struct HashEntry* pEntry = newEntry(key, nKey, value, nValue);

    struct HashEntry* tmpEntry = phash->hashTable[index];
    while (tmpEntry != NULL)
    {
        if (!memcmp(key, tmpEntry->key, nKey))
        {
            tmpEntry->value = (void*)realloc(tmpEntry->value, pEntry->nValue);
            memcpy(tmpEntry->value, pEntry->value, pEntry->nValue);
            tmpEntry->nValue = pEntry->nValue;
            freeHashEntry(pEntry);
            return 1;
        }
        tmpEntry = tmpEntry->next;
    }
    freeHashEntry(pEntry);
    return 0;
}

int removeKey(struct Hash* phash, const void* key, int nKey)
{
    unsigned int index = getIndex(phash, key, nKey);
    struct HashEntry* tmpEntry = phash->hashTable[index];
    struct HashEntry* pLastEntry = tmpEntry, *pNextEntry;
    while (tmpEntry != NULL)
    {
        pNextEntry = tmpEntry->next;
        // 当前key已存在
        if (!memcmp(key, tmpEntry->key, nKey))
        {
            if (tmpEntry == phash->hashTable[index])
                phash->hashTable[index] = tmpEntry->next;
            else 
                pLastEntry->next = pNextEntry;
            freeHashEntry(tmpEntry);
            phash->size--;
            return 1;
        }
        pLastEntry = tmpEntry;
        tmpEntry = pNextEntry;
    }
    return 0;
}

void* getValue(struct Hash* phash, const void* key, int nKey)
{
    unsigned int index = getIndex(phash, key, nKey);
    struct HashEntry* tmpEntry = phash->hashTable[index];
    while (tmpEntry != NULL)
    {
        if (!memcmp(key, tmpEntry->key, nKey))
        {
            return tmpEntry->value;
        }
        tmpEntry = tmpEntry->next;
    }
    return (void*)NULL;
}

unsigned int getSize(struct Hash* phash)
{
    return phash->size;
}

static void expand(struct Hash* phash)
{
    unsigned int oldCapcity = phash->capcity;
    struct HashEntry** oldHashTable = phash->hashTable;
    phash->capcity = oldCapcity << 1;
    phash->hashTable = (struct HashEntry**)malloc(sizeof(struct HashEntry*)*phash->capcity);
    for (unsigned int i = 0; i < oldCapcity; ++i)
    {
        struct HashEntry* pEntry = oldHashTable[i], *pNextEntry;
        while (pEntry != NULL)
        {
            pNextEntry = pEntry->next;
            putEntry(phash, pEntry);
            pEntry = pNextEntry;
        }
    }
    free(oldHashTable);
}

static int putEntry(struct Hash* phash, struct HashEntry* pEntry)
{
    unsigned int index = getIndex(phash, pEntry->key, pEntry->nKey);
    struct HashEntry* tmpEntry = phash->hashTable[index];
    while (tmpEntry != NULL)
    {
        // 当前key已存在
        if (!memcmp(pEntry->key, tmpEntry->key, pEntry->nKey))
        {
            tmpEntry->value = (void*)realloc(tmpEntry->value, pEntry->nValue);
            memcpy(tmpEntry->value, pEntry->value, pEntry->nValue);
            tmpEntry->nValue = pEntry->nValue;
            freeHashEntry(pEntry);
            return 0;
        }
        tmpEntry = tmpEntry->next;
    }
    pEntry->next = phash->hashTable[index];
    phash->hashTable[index] = pEntry;
    return 1;
}

static void freeHashEntry(struct HashEntry* pEntry)
{
    free(pEntry->key);
    free(pEntry->value);
    free(pEntry);
}

void freeHash(struct Hash* phash)
{
    for (unsigned int i = 0; i < phash->capcity; ++i)
    {
        struct HashEntry* pEntry = phash->hashTable[i], *pNextEntry;
        while (pEntry)
        {
            pNextEntry = pEntry->next;
            freeHashEntry(pEntry);
            pEntry = pNextEntry;
        }
    }
    free(phash->hashTable);
    free(phash);
}
