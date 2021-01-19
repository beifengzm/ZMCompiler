#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SyntaxTree.h"

// 后序遍历语法树
static void postTraverse(struct TreeNode* p);

char* NodeKindStr[] = 
{
    "ClassStatement", "FunctionStatement", "WhileStatement", "IfStatement", "ElseStatement", "ForStatement", 
    "AssignStatement", "DoStatement", "UnaryOp", "MulDivOp", "AddSubOp", "CompareOp", 
    "AndOrOp", "Id", "Int", "Call", "DefineStatement", "ReturnStatement", 
    "BreakStatement", "ContinueStatement", "Array"
};

void scanFile(const char* filename)
{
    ptoken = list = getTokenStream(filename);
}

void freeTokenList()
{
    struct TokenNode *pCur, *pnext;
    pCur = list, pnext = list->next;
    while (pCur != NULL)
    {
        freeTokenNode(pCur);
        pCur = pnext;
        if (pnext != NULL)
            pnext = pnext->next;
    }
}

struct TokenNode* getToken()
{
    if (ptoken != NULL)
        ptoken = ptoken->next;
    return ptoken;
}

struct TokenNode* getKthFromCurrToken(unsigned int k)
{
    struct TokenNode* ptmpToken = ptoken;
    while (k--)
    {
        if (ptmpToken == NULL)
            break;
        ptmpToken = ptmpToken->next;
    }
    return ptmpToken;
}

void skipCurrentToken()
{
    if (ptoken != NULL)
        ptoken = ptoken->next;
}

void skipKFromCurrToken(unsigned int k)
{
    while (k-- && ptoken != NULL)
        ptoken = ptoken->next;
}

void rollbackToken()
{
    if (ptoken != NULL)
        ptoken = ptoken->last;
}

void parsingSyntaxTree()
{
    printf("Starting parsing syntax tree...\n");
    syntaxTree = parsingStatements();
    printf("Parsing syntax tree done!\n\n");
}

void printSyntaxTree()
{
    printf("Starting printing syntax tree...\n");
    postTraverse(syntaxTree);
    printf("Printing syntax tree done!\n");
}

void postTraverse(struct TreeNode* ptree)
{
    if (ptree == NULL)
        return;
    printf("[node] line: %-4d kind: %-18s descriptor: %-18s name: %s\n", ptree->lineno, ptree->kindStr, ptree->descriptor, ptree->name);        
    for (int i = 0; i < MAXCHILD; ++i)
    {
        if (ptree->children[i] == NULL)
            continue;
        postTraverse(ptree->children[i]);
    }
    // printf("[node] kind: %s, descriptor: %s, line: %d, name: %s\n", ptree->kindStr, ptree->descriptor, ptree->lineno, ptree->name);
    postTraverse(ptree->next);
    // printf("%s ", ptree->value);
}

struct TreeNode* newTreeNode(NodeKind kind, int lineno, char* name, char* descriptor)
{
    struct TreeNode* tnode;
    tnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    tnode->nodeKind = kind;
    tnode->lineno = lineno;
    tnode->kindStr = (char*)malloc(strlen(NodeKindStr[kind])+1);
    strcpy(tnode->kindStr, NodeKindStr[kind]);
    tnode->descriptor = (char*)malloc(strlen(descriptor)+1);
    strcpy(tnode->descriptor, descriptor);
    tnode->name = (char*)malloc(strlen(name)+1);
    strcpy(tnode->name, name);
    for (int i = 0; i < MAXCHILD; i++)
        tnode->children[i] = NULL;
    tnode->next = NULL;
    return tnode;
}

void setNodeVarName(struct TreeNode* pnode, const char* varName)
{
    pnode->varName = (char*)malloc(strlen(varName)+1);
    strcpy(pnode->varName, varName);
}

