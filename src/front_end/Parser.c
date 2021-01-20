#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PrintInfo.h"
#include "Parser.h"

struct TreeNode* parsingExpression()
{
    struct TreeNode* pCurRoot;
    struct TreeNode* pnodes[3];
    pnodes[0] = parsingAndOrTerm();
    while (1)
    {
        pnodes[1] = parsingAndOrOpSymbol();
        if (pnodes[1] == NULL)
        {
            pCurRoot = pnodes[0];
            break;
        }
        pnodes[2] = parsingAndOrTerm();
        pnodes[1]->children[0] = pnodes[0];
        pnodes[1]->children[1] = pnodes[2];

        pnodes[0] = pnodes[1];
    }
    skipCurrentToken();
    return pCurRoot;
}

// 解析&,|运算term
struct TreeNode* parsingAndOrTerm()
{
    struct TreeNode* pCurRoot;
    struct TreeNode* pnodes[3];
    pnodes[0] = parsingCompTerm();
    pnodes[1] = parsingCompOpSymbol();
    if (pnodes[1] != NULL)
    {
        pnodes[2] = parsingCompTerm();
        pnodes[1]->children[0] = pnodes[0];
        pnodes[1]->children[1] = pnodes[2];
        pCurRoot = pnodes[1];
    }
    else
        pCurRoot = pnodes[0];
    return pCurRoot;
}

// 解析&,|
struct TreeNode* parsingAndOrOpSymbol()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    if (ptoken == NULL)
        return pCurRoot;
    switch (ptoken->value[0])
    {
        case '&':
        case '|':
            pCurRoot = newTreeNode(AND_OR_KIND, ptoken->lineno, ptoken->value, "AndOrOpSymbol");
            break;
        default:
            rollbackToken();
            break;
    }

    return pCurRoot;
}

// 解析比较运算<, >, <=, >=, ==的term
struct TreeNode* parsingCompTerm()
{
    struct TreeNode* pCurRoot;
    struct TreeNode* pnodes[3];
    pnodes[0] = parsingAddSubTerm();
    while (1)
    {
        pnodes[1] = parsingAddSubSymbol();
        if (pnodes[1] == NULL)
        {
            pCurRoot = pnodes[0];
            break;
        }
        pnodes[2] = parsingAddSubTerm();
        pnodes[1]->children[0] = pnodes[0];
        pnodes[1]->children[1] = pnodes[2];

        pnodes[0] = pnodes[1];
    }

    return pCurRoot;
}

// 解析比较运算符<, >, <=, >=, ==
struct TreeNode* parsingCompOpSymbol()
{
    struct TreeNode* pCurRoot = NULL;
    char value[3];
    int i, flag = 0;
    for (i = 0; i < 2;)
    {
        getToken();
        if (ptoken == NULL)
            return pCurRoot;
        switch (ptoken->value[0])
        {
            case '<':
            case '>':
            case '=':
                value[i] = ptoken->value[0];
                break;
            default:
                flag = 1;
                break;
        }
        if (flag)
        {
            rollbackToken();
            break;
        }
        ++i;
    }
    value[i] = '\0';
    if (i > 0)
        pCurRoot = newTreeNode(COMP_OP_KIND, ptoken->lineno, value, "CompOpSymbol");
    
    return pCurRoot;
}

/*** 解析+,-的term ***/ 
struct TreeNode* parsingAddSubTerm()
{
    struct TreeNode* pCurRoot;
    struct TreeNode* pnodes[3];
    pnodes[0] = parsingMulDivTerm();
    while (1)
    {
        pnodes[1] = parsingMulDivSymbol();
        if (pnodes[1] == NULL)
        {
            pCurRoot = pnodes[0];
            break;
        }
        pnodes[2] = parsingMulDivTerm();
        pnodes[1]->children[0] = pnodes[0];
        pnodes[1]->children[1] = pnodes[2];

        pnodes[0] = pnodes[1];
    }

    return pCurRoot;
}

// 解析+,-符号
struct TreeNode* parsingAddSubSymbol()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    if (ptoken == NULL)
        return pCurRoot;
    switch (ptoken->value[0])
    {
        case '+':
        case '-':
            pCurRoot = newTreeNode(ADD_SUB_KIND, ptoken->lineno, ptoken->value, "AddSubSymbol");
            break;
        default:
            rollbackToken();
            break;
    }

    return pCurRoot;
}

/*** 解析*,/的term ***/ 
struct TreeNode* parsingMulDivTerm()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    if (ptoken == NULL)
        return pCurRoot;
    if (!strcmp("(", ptoken->value))
        return pCurRoot = parsingExpBracket();
    switch (ptoken->tokenType)
    {
        case IDENTIFIER:
        {
            struct TokenNode* tmpNode = getKthFromCurrToken(1);
            if (!strcmp(tmpNode->value, "["))
            {
                rollbackToken();
                pCurRoot = parsingArrayRef();
            }
            else if (!strcmp(tmpNode->value, "("))
            {
                rollbackToken();
                pCurRoot = parsingCallStatement();
                rollbackToken();
            }
            else
                pCurRoot = newTreeNode(IDENTIFIER_KIND, ptoken->lineno, ptoken->value, "Identifier");
            break;
        }

        case KEYWORD:
            if (!strcmp(ptoken->value, "true") || !strcmp(ptoken->value, "false"))
                pCurRoot = newTreeNode(INT_CONST_KIND, ptoken->lineno, 
                    !strcmp(ptoken->value, "true")?"1":"0", "Boolean const");
            break;
            
        case INT_CONST:
            pCurRoot = newTreeNode(INT_CONST_KIND, ptoken->lineno, ptoken->value, "Integer const");
            break;
            
        default:
            break;
    }
    return pCurRoot;
}

/*** 解析*,/符号 ***/
struct TreeNode* parsingMulDivSymbol()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    if (ptoken == NULL)
        return pCurRoot;
    switch (ptoken->value[0])
    {
        case '*':
        case '/':
            pCurRoot = newTreeNode(MUL_DIV_KIND, ptoken->lineno, ptoken->value, "MulDivSymbol");
            break;
        default:
            rollbackToken();
            break;
    }

    return pCurRoot;
}

/*** 解析() ***/
struct TreeNode* parsingExpBracket()
{
    struct TreeNode* pCurRoot = NULL;
    pCurRoot = parsingExpression();
    return pCurRoot;
}

struct TreeNode* parsingArrayRef()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    pCurRoot = newTreeNode(ARRAY_KIND, ptoken->lineno, ptoken->value, "array");
    skipCurrentToken();
    pCurRoot->children[0] = parsingExpression();
    return pCurRoot;
}

struct TreeNode* parsingStatements()
{
    struct TreeNode* pCurRoot = NULL;
    struct TreeNode* pnodes[2];
    pCurRoot = pnodes[0] = parsingStatement();
    while (pnodes[0] != NULL)
    {
        while (pnodes[0]->next)
            pnodes[0] = pnodes[0]->next;
        pnodes[1] = parsingStatement();
        pnodes[0]->next = pnodes[1];
        pnodes[0] = pnodes[1];
    }
    return pCurRoot;
}

struct TreeNode* parsingStatement()
{
    struct TreeNode* pCurRoot = NULL;
    struct TokenNode* p1stToken = getKthFromCurrToken(1);
    if (p1stToken == NULL) return pCurRoot;
    if (!strcmp(p1stToken->value, "int"))
    {
        pCurRoot = parsingDefineStatement();
    }
    else if (!strcmp(p1stToken->value, "if"))
    {
        pCurRoot = parsingIfStatement();
    }
    else if (!strcmp(p1stToken->value, "for"))
    {
        pCurRoot = parsingForStatement();
    }
    else if (!strcmp(p1stToken->value, "while"))
    {
        pCurRoot = parsingWhileStatment();
    }
    else if (!strcmp(p1stToken->value, "function"))
    {
        pCurRoot = parsingFunction();
    }
    else if (!strcmp(p1stToken->value, "break"))
    {
        pCurRoot = parsingBreakStatement();
    }
    else if (!strcmp(p1stToken->value, "continue"))
    {
        pCurRoot = parsingContinueStatement();
    }
    else if (!strcmp(p1stToken->value, "return"))
    {
        pCurRoot = parsingReturnStatement();
    }
    else if (!strcmp(p1stToken->value, "}"))
    {
        skipCurrentToken();
    }
    else if (p1stToken->tokenType == IDENTIFIER)
    {
        getToken();
        struct TreeNode* tmpNode;
        if (!strcmp(getKthFromCurrToken(1)->value, "[")) // array
        {
            rollbackToken();
            tmpNode = parsingArrayRef();
        }
        else 
        {
            tmpNode = newTreeNode(IDENTIFIER_KIND, ptoken->lineno, ptoken->value, "identifier");
        }

        if (!strcmp(getKthFromCurrToken(1)->value, "="))  // Assign statement
        {
            pCurRoot = parsingAssignStatement();
            pCurRoot->children[0] = tmpNode;
        }
        else if (!strcmp(getKthFromCurrToken(1)->value, "("))  // Call statement
        {
            // TODO: Call statement code
        }
    }
    
    return pCurRoot;
}

/*** 解析函数参数 ***/
struct TreeNode* parsingFunctionParam()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    if (!strcmp(ptoken->value, "int"))
    {
        getToken();
        if (!strcmp(getKthFromCurrToken(1)->value, "["))
        {
            pCurRoot = newTreeNode(ARRAY_KIND, ptoken->lineno, ptoken->value, "int");
            pCurRoot->children[0] = newTreeNode(INT_CONST_KIND, ptoken->lineno, "-1", "nArray");
            skipKFromCurrToken(2);
        }
        else
        {
            pCurRoot = newTreeNode(IDENTIFIER_KIND, ptoken->lineno, ptoken->value, "int");
        }
    }
    else
    {
        rollbackToken();
    }
    return pCurRoot;
}

/*** 解析参数列表 ***/
struct TreeNode* parsingFunctionParamList()
{
    struct TreeNode* pCurRoot = NULL;
    struct TreeNode* pnode[2];
    pnode[0] = parsingFunctionParam();
    while (pnode[0] != NULL)
    {
        pCurRoot = pnode[0];
        getToken();
        if (!strcmp(ptoken->value, ","))
        {
            pnode[1] = parsingFunctionParam();
            pnode[1]->next = pnode[0];
            pnode[0] = pnode[1];
        }    
        else
        {
            rollbackToken();
            break;
        }
    }
    return pCurRoot;
}

struct TreeNode* parsingFunctionBody()
{
    struct TreeNode* pCurRoot = NULL;
    pCurRoot = parsingStatements();

    return pCurRoot;
}

struct TreeNode* parsingFunction()
{
    struct TreeNode* pCurRoot, *ptmpNode;
    skipCurrentToken(); // 跳过“Function”
    getToken();
    pCurRoot = newTreeNode(FUNCTION_KIND, ptoken->lineno, ptoken->value, "0");
    skipCurrentToken();  // 跳过"("
    ptmpNode = pCurRoot->children[0] = parsingFunctionParamList();

    unsigned int nCount = 0;
    while (ptmpNode)
    {
        nCount++;
        ptmpNode = ptmpNode->next;
    }
    sprintf(pCurRoot->descriptor, "%d", nCount);
    
    skipCurrentToken();  // 跳过")"
    skipCurrentToken();  // 跳过"{"
    pCurRoot->children[1] = parsingFunctionBody();

    return pCurRoot;
}

struct TreeNode* parsingCallStatement()
{
    struct TreeNode* pCurRoot = NULL;
    struct TreeNode* pnode[2];
    getToken();
    pCurRoot = newTreeNode(CALL_KIND, ptoken->lineno, ptoken->value, "call");
    skipCurrentToken();  // 跳过"("
    pnode[0] = parsingExpression();
    while (pnode[0])
    {
        pCurRoot->children[0] = pnode[0];
        if (strcmp(ptoken->value, ",")) break;
        pnode[1] = parsingExpression();
        if (pnode[1])
            pnode[1]->next = pnode[0];
        pnode[0] = pnode[1];
    }
    if (!strcmp(ptoken->value, ")"))
        skipCurrentToken();  // 跳过")"
    return pCurRoot;
}

struct TreeNode* parsingDefineStatement()
{
    struct TreeNode* pCurRoot = NULL;
    struct TreeNode* pnode[2];
    getToken();
    char defineType[30];
    sprintf(defineType, "%s", ptoken->value);
    getToken();
    if (ptoken->tokenType != IDENTIFIER) 
    {
        GRAMMER_ERROR("Variable defined must be an identifier or array.");
    }
    pCurRoot = pnode[0] = newTreeNode(DEFINE_KIND, ptoken->lineno, ptoken->value, defineType);
    if (!strcmp(getKthFromCurrToken(1)->value, "["))   // array
    {
        skipKFromCurrToken(2);
        pnode[0]->children[0] = newTreeNode(INT_CONST_KIND, ptoken->lineno, ptoken->value, "nArray");
        skipKFromCurrToken(1);
    }
    
    if (!strcmp(getKthFromCurrToken(1)->value, "="))
    {
        pnode[1] = newTreeNode(IDENTIFIER_KIND, ptoken->lineno, ptoken->value, "identifier");
        pCurRoot->next = parsingAssignStatement();
        pCurRoot->next->children[0] = pnode[1];
    }
    else while (!strcmp(getKthFromCurrToken(1)->value, ","))
    {
        skipCurrentToken();
        getToken();
        pnode[1] = newTreeNode(DEFINE_KIND, ptoken->lineno, ptoken->value, defineType);
        if (!strcmp(getKthFromCurrToken(1)->value, "["))   // array
        {
            skipKFromCurrToken(2);
            pnode[1]->children[0] = newTreeNode(INT_CONST_KIND, ptoken->lineno, ptoken->value, "nArray");
            skipCurrentToken();
        }
        pnode[0]->next = pnode[1];
        pnode[0] = pnode[1];
    }
    if (!strcmp(getKthFromCurrToken(1)->value, ";"))
        skipCurrentToken();
    
    return pCurRoot;
}

struct TreeNode* parsingWhileStatment()
{
    struct TreeNode* pCurRoot;
    getToken(); 
    pCurRoot = newTreeNode(WHILE_KIND, ptoken->lineno, ptoken->value, "while");
    skipCurrentToken();  // 跳过"("
    pCurRoot->children[0] = parsingExpression();
    skipCurrentToken();  // 跳过")"
    pCurRoot->children[1] = parsingStatements();

    return pCurRoot;
}

struct TreeNode* parsingIfStatement()
{
    struct TreeNode* pCurRoot;
    getToken(); 
    pCurRoot = newTreeNode(IF_KIND, ptoken->lineno, ptoken->value, "if");
    skipCurrentToken();  // 跳过"("
    pCurRoot->children[0] = parsingExpression();
    skipCurrentToken();  // 跳过")"
    pCurRoot->children[1] = parsingStatements();
    if (!strcmp(getKthFromCurrToken(1)->value, "else"))
    {
       pCurRoot->children[2] = parsingElseStatement();
    }

    return pCurRoot;
}

struct TreeNode* parsingElseStatement()
{
    struct TreeNode* pCurRoot;
    getToken(); 
    pCurRoot = newTreeNode(ELSE_KIND, ptoken->lineno, ptoken->value, "else");
    if (!strcmp(getKthFromCurrToken(1)->value, "if"))
    {
        skipCurrentToken();
        skipCurrentToken();
        pCurRoot->children[0] = parsingExpression();
    }
    skipCurrentToken();
    pCurRoot->children[1] = parsingStatements();
    if (!strcmp(getKthFromCurrToken(1)->value, "else"))
    {
        pCurRoot->children[2] = parsingElseStatement();
    }

    return pCurRoot;
}

struct TreeNode* parsingForStatement()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    pCurRoot = newTreeNode(FOR_KIND, ptoken->lineno, ptoken->value, "for");
    skipCurrentToken();
    pCurRoot->children[0] = parsingStatement();
    pCurRoot->children[1] = parsingExpression();
    pCurRoot->children[2] = parsingStatement();
    skipCurrentToken();
    pCurRoot->children[3] = parsingStatements();
    
    return pCurRoot;
}

struct TreeNode* parsingAssignStatement()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    pCurRoot = newTreeNode(ASSIGN_KIND, ptoken->lineno, ptoken->value, "assignment");
    pCurRoot->children[1] = parsingExpression();
    return pCurRoot;
}

struct TreeNode* parsingReturnStatement()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    pCurRoot = newTreeNode(RETURN_KIND, ptoken->lineno, ptoken->value, "return");
    if (strcmp(getKthFromCurrToken(1)->value, ";"))
        pCurRoot->children[0] = parsingExpression();
    else
        skipCurrentToken();
    return pCurRoot;
}

struct TreeNode* parsingBreakStatement()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    pCurRoot = newTreeNode(BREAK_KIND, ptoken->lineno, ptoken->value, "break");
    skipCurrentToken();
    return pCurRoot;
}

struct TreeNode* parsingContinueStatement()
{
    struct TreeNode* pCurRoot = NULL;
    getToken();
    pCurRoot = newTreeNode(CONTINUE_KIND, ptoken->lineno, ptoken->value, "continue");
    skipCurrentToken();
    return pCurRoot;
}
