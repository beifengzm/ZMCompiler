#pragma once

typedef enum 
{
    KEYWORD=0, SYMBOL=1, IDENTIFIER=2, INT_CONST=3, STRING_CONST=4, NULL_TOKEN=5
}TokenType;

struct TokenNode
{
    char* value;
    int lineno;
    TokenType tokenType;
    struct TokenNode *last, *next;
};
typedef struct TokenNode* TokenList;


// 10种输入类型分类分别为: (0)数字, (1)字母, (2)_, (3)/, (4)*, (5)", (6)空格orTAB, (7)/n, (8)/r, (9)其他
const static int state_table[9][10];
const char* tokenTypeStr[6];

void freeTokenNode(struct TokenNode* pnode);
TokenList getTokenStream(const char* filename);
