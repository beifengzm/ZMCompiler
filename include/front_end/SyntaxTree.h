#pragma once

#include "Scanner.h"

#define MAXCHILD 5
#define KINDSIZE 21

typedef enum
{
    CLASS_KIND, FUNCTION_KIND, WHILE_KIND, IF_KIND, ELSE_KIND, FOR_KIND, ASSIGN_KIND, DO_KIND,
    UNARY_KIND, MUL_DIV_KIND, ADD_SUB_KIND, COMP_OP_KIND, 
    AND_OR_KIND, IDENTIFIER_KIND, INT_CONST_KIND, CALL_KIND,
    DEFINE_KIND, RETURN_KIND, BREAK_KIND, CONTINUE_KIND, ARRAY_KIND
}NodeKind;

struct TreeNode
{
    NodeKind nodeKind;
    char* kindStr;
    char* descriptor;
    char* name;
    char* varName;
    int lineno;   // 行号
    struct TreeNode* children[MAXCHILD];  // 孩子节点
    struct TreeNode* next;   // 指向链表的下一个结点
};

char* NodeKindStr[KINDSIZE];

struct TreeNode* syntaxTree;   

struct TokenNode *list, *ptoken;
struct TokenNode* getToken();
struct TokenNode* getKthFromCurrToken(unsigned int k);  // 当前token之后的第k个token
void skipCurrentToken(); // 跳过当前Token
void skipKFromCurrToken(unsigned int k);
void rollbackToken();

/*** 
 * 用户调用接口 
***/
void scanFile(const char* filename);

void parsingSyntaxTree();
void printSyntaxTree();
void freeTokenList();

/*** 动态新建一个语法树结点 ***/
struct TreeNode* newTreeNode(NodeKind nodeKind, int lineno, char* name, char* descriptor);
void setNodeVarName(struct TreeNode* pnode, const char* varName);

/*** 
 * 各类解析函数
***/
extern struct TreeNode* parsingExpression();
extern struct TreeNode* parsingStatements();



