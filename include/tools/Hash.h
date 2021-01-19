#pragma once

typedef unsigned int nbyte_t;

struct HashEntry
{
    void* key;
    void* value;
    nbyte_t nKey;      // key在内存中所占的字节数
    nbyte_t nValue;      // value在内存中所占的字节数
    struct HashEntry* next;  // 冲突链表
};

struct Hash
{
    struct HashEntry** hashTable;
    unsigned int capcity;    // 桶容量
    unsigned int size;       // 当前entry个数      
    struct Hash *last, *next;   // Hash链表
};

struct Hash* newHash();
int putKV(struct Hash* phash, const void* key, nbyte_t nKey, 
                    const void* value, nbyte_t nValue);
int setValue(struct Hash* phash, const void* key, nbyte_t nKey, 
                        const void* value, nbyte_t nValue);
void* getValue(struct Hash* phash, const void* key, int nKey);
unsigned int getSize(struct Hash* phash);
int removeKey(struct Hash* phash, const void* key, int nKey);
void freeHash(struct Hash* phash);

