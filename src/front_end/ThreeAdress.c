#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ThreeAdress.h"
#include "SyntaxTree.h"
#include "Hash.h"

#define IR_EMIT fprintf
#define STACKSIZE 101

struct ScopeNode
{
    unsigned int index;
    char* scopeName;
    struct ScopeNode* parent;
    struct ScopeNode* child;
    struct ScopeNode* left;
    struct ScopeNode* right;
};

extern struct TreeNode* syntaxTree; 

static FILE* fp;
static char scopeBuff[101];
static struct ScopeNode* pRootScopeNode;
static struct ScopeNode* pCurScopeNode;

static int scopeTop;
static unsigned int scopeStack[STACKSIZE];
static int loopTop;
static char loopStack[STACKSIZE][18];

static unsigned int elseIndex;

static void getCurScopeNode();
static void setScopeName(struct ScopeNode*, const char*);
static void emitTreeNode(struct TreeNode* pnode);

static void getCurScopeNode()
{
    struct ScopeNode* ptmpNode;
    ptmpNode = (struct ScopeNode*)malloc(sizeof(struct ScopeNode));
    ptmpNode->index = 1;
    ptmpNode->parent = ptmpNode->child = NULL;
    ptmpNode->left = ptmpNode->right = NULL;

    if (pCurScopeNode != NULL)
    {
        if (pCurScopeNode->child)
        {
            pCurScopeNode->child->right = ptmpNode;
            ptmpNode->left = pCurScopeNode->child;
            ptmpNode->index = pCurScopeNode->child->index+1;
        }
        ptmpNode->parent = pCurScopeNode;
        pCurScopeNode->child = ptmpNode;
    }
    pCurScopeNode = ptmpNode;
}

static void setScopeName(struct ScopeNode* pnode, const char* scopeName)
{
    pnode->scopeName = (char*)malloc(strlen(scopeName)+1);
    strcpy(pnode->scopeName, scopeName);
}

void generateIR(const char* filename)
{
#if 0
    char path[31];
    sprintf(path, "../output/main.ir");

    fp = fopen(path, "w");
#endif 

    fp = stdout;

    getCurScopeNode();
    setScopeName(pCurScopeNode, "global");
    pRootScopeNode = pCurScopeNode;

    for (int i = 0; i < STACKSIZE; ++i)
        scopeStack[i] = 1;
    scopeTop = 0;  // 表示global域
    loopTop = 0;
    elseIndex = 1;
    
    emitTreeNode(syntaxTree);

    fclose(fp);
}

static void emitTreeNode(struct TreeNode* pnode)
{
    if (pnode == NULL) return;
    switch (pnode->nodeKind)
    {
        case FUNCTION_KIND:
        {
            scopeTop++;  // 进入函数域
            getCurScopeNode();
            setScopeName(pCurScopeNode, pnode->name);
           
            IR_EMIT(fp, ". Scope %s\n", pCurScopeNode->scopeName);
            IR_EMIT(fp, "Function %s %s\n", pnode->name, pnode->descriptor);
            struct TreeNode* ptmpNode = pnode->children[0];
            while (ptmpNode)
            {
                if (ptmpNode->nodeKind==IDENTIFIER_KIND)
                    IR_EMIT(fp, "Param %s $%s\n", ptmpNode->descriptor, ptmpNode->name);
                else if (ptmpNode->nodeKind==ARRAY_KIND)
                    IR_EMIT(fp, "Param %s $%s %s\n", ptmpNode->descriptor, ptmpNode->name, "-1");
                ptmpNode = ptmpNode->next;
            }
            emitTreeNode(pnode->children[1]);
            IR_EMIT(fp, "End %s\n", pnode->name);

            scopeStack[scopeTop--] = 1;
            pCurScopeNode = pCurScopeNode->parent;

            break;
        }

        case IF_KIND:
        {
            scopeTop++;  // 进入If域

            getCurScopeNode();
            sprintf(scopeBuff, "If%d", pCurScopeNode->index);
            setScopeName(pCurScopeNode, scopeBuff);

            IR_EMIT(fp, ". Scope %s\n", pCurScopeNode->scopeName);
            IR_EMIT(fp, "Label %s\n", pCurScopeNode->scopeName);
            emitTreeNode(pnode->children[0]);
            if (pnode->children[2])
            {
                IR_EMIT(fp, "Ifn-goto %s Label %s_else%u\n", pnode->children[0]->varName, pCurScopeNode->scopeName, elseIndex);
            }
            else
            {
                IR_EMIT(fp, "Ifn-goto %s End %s\n", pnode->children[0]->varName, pCurScopeNode->scopeName);
            }
            
            emitTreeNode(pnode->children[1]);
            IR_EMIT(fp, "goto End %s\n", pCurScopeNode->scopeName);
            
            if (pnode->children[2])
                emitTreeNode(pnode->children[2]);
            IR_EMIT(fp, "End %s\n", pCurScopeNode->scopeName);

            scopeStack[scopeTop--] = 1;
            pCurScopeNode = pCurScopeNode->parent;
            elseIndex = 1;

            break;
        }
            
        case ELSE_KIND:
        {
            IR_EMIT(fp, "Label %s_else%u\n", pCurScopeNode->scopeName, elseIndex);
            elseIndex++;
            
            if (pnode->children[0])
            {
                emitTreeNode(pnode->children[0]);
                if (pnode->children[2])
                {
                    IR_EMIT(fp, "Ifn-goto %s Label %s_else%u\n", pnode->children[0]->varName, pCurScopeNode->scopeName, elseIndex);
                }
                else
                {
                    IR_EMIT(fp, "Ifn-goto %s End %s\n", pnode->children[0]->varName, pCurScopeNode->scopeName);
                }
            }
            
            emitTreeNode(pnode->children[1]);
            IR_EMIT(fp, "goto End %s\n", pCurScopeNode->scopeName);
            
            if (pnode->children[2])
                emitTreeNode(pnode->children[2]);

            break;
        }

        case FOR_KIND:
        {
            scopeTop++;  // 进入for域
            loopTop++;

            getCurScopeNode();
            sprintf(scopeBuff, "For%d", pCurScopeNode->index);
            setScopeName(pCurScopeNode, scopeBuff);

            strcpy(loopStack[loopTop], pCurScopeNode->scopeName);

            IR_EMIT(fp, ". Scope %s\n", pCurScopeNode->scopeName);
            emitTreeNode(pnode->children[0]);
            IR_EMIT(fp, "Label %s\n", pCurScopeNode->scopeName);
            emitTreeNode(pnode->children[1]);
            IR_EMIT(fp, "Ifn-goto %s End %s\n", pnode->children[1]->varName, pCurScopeNode->scopeName);
            emitTreeNode(pnode->children[3]);
            IR_EMIT(fp, "Label %s_continue\n", pCurScopeNode->scopeName);
            emitTreeNode(pnode->children[2]);
            IR_EMIT(fp, "goto Label %s\n", pCurScopeNode->scopeName);
            IR_EMIT(fp, "End %s\n", pCurScopeNode->scopeName);

            scopeStack[scopeTop--] = 1;
            loopTop--;
            pCurScopeNode = pCurScopeNode->parent;

            break;
        }

        case WHILE_KIND:
        {
            scopeTop++;  // 进入while域
            loopTop++;

            getCurScopeNode();
            sprintf(scopeBuff, "While%d", pCurScopeNode->index);
            setScopeName(pCurScopeNode, scopeBuff);

            strcpy(loopStack[loopTop], pCurScopeNode->scopeName);

            IR_EMIT(fp, ". Scope %s\n", pCurScopeNode->scopeName);
            IR_EMIT(fp, "Label %s\n", pCurScopeNode->scopeName);
            emitTreeNode(pnode->children[0]);
            IR_EMIT(fp, "Ifn-goto %s End %s\n", pnode->children[0]->varName, pCurScopeNode->scopeName);
            emitTreeNode(pnode->children[1]);
            IR_EMIT(fp, "Label %s_continue\n", pCurScopeNode->scopeName);
            IR_EMIT(fp, "goto Label %s\n", pCurScopeNode->scopeName);
            IR_EMIT(fp, "End %s\n", pCurScopeNode->scopeName);

            scopeStack[scopeTop--] = 1;
            loopTop--;
            pCurScopeNode = pCurScopeNode->parent;

            break;
        }

        case CONTINUE_KIND:
            IR_EMIT(fp, "goto Label %s_continue\n", loopStack[loopTop]);
            break;
        
        case BREAK_KIND:
            IR_EMIT(fp, "goto End %s\n", loopStack[loopTop]);
            break;

        case DEFINE_KIND:
        {
            if (pnode->children[0])  // array definition
            {
                IR_EMIT(fp, "Define %s $%s %s\n", pnode->descriptor, 
                        pnode->name, pnode->children[0]->name);
            }
            else
            {
                IR_EMIT(fp, "Define %s $%s\n", pnode->descriptor, pnode->name);
            }
            
            setNodeVarName(pnode, pnode->name);
            break;
        }

        case ASSIGN_KIND:
        {
            emitTreeNode(pnode->children[0]);
            emitTreeNode(pnode->children[1]);
            IR_EMIT(fp, "%s = %s\n", pnode->children[0]->varName, pnode->children[1]->varName);
            setNodeVarName(pnode, pnode->name);
            break;
        }

        case ARRAY_KIND:
        {
            emitTreeNode(pnode->children[0]);
            char tmpBuff[512];
            sprintf(tmpBuff, "$%s(%s)", pnode->name, pnode->children[0]->varName);
            setNodeVarName(pnode, tmpBuff);

            break;
        }

        case AND_OR_KIND:
        case COMP_OP_KIND:
        case MUL_DIV_KIND:
        case ADD_SUB_KIND:
        {   
            char varName[512];

            emitTreeNode(pnode->children[0]);
            emitTreeNode(pnode->children[1]);

            sprintf(varName, "%%t%d", scopeStack[scopeTop]++);
            IR_EMIT(fp, "%s = %s %s %s\n", varName, 
                pnode->children[0]->varName, pnode->name, pnode->children[1]->varName);
            setNodeVarName(pnode, varName);

            break;
        }

        case IDENTIFIER_KIND:
        {
            char varName[512];

            sprintf(varName, "$%s", pnode->name);
            setNodeVarName(pnode, varName);
            break;
        }

        case INT_CONST_KIND:
            setNodeVarName(pnode, pnode->name);
            break;

        case RETURN_KIND:
            emitTreeNode(pnode->children[0]);
            if (pnode->children[0])
                IR_EMIT(fp, "Ret %s\n", pnode->children[0]->varName);
            else
                IR_EMIT(fp, "Ret\n");
            
            break;

        default:
            break;
    }
    emitTreeNode(pnode->next);
}
