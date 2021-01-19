#pragma once

#include "SyntaxTree.h"

extern struct TokenNode *ptoken;

/*** 外部调用接口：解析expression ***/
struct TreeNode* parsingExpression();

/*** 解析&,|运算term ***/ 
static struct TreeNode* parsingAndOrTerm();

/*** 解析&,| ***/ 
static struct TreeNode* parsingAndOrOpSymbol();

/*** 解析比较运算term ***/
static struct TreeNode* parsingCompTerm();

/*** 解析运算符<, >, <=, >=, == ***/
static struct TreeNode* parsingCompOpSymbol();

/*** 解析+,-term ***/ 
static struct TreeNode* parsingAddSubTerm();

// 解析+,-符号
static struct TreeNode* parsingAddSubSymbol();

/*** 解析*,/的term ***/ 
static struct TreeNode* parsingMulDivTerm();

/*** 解析*,/符号 ***/
static struct TreeNode* parsingMulDivSymbol();

/*** 解析() ***/
static struct TreeNode* parsingExpBracket();

static struct TreeNode* parsingArrayRef();


struct TreeNode* parsingStatements();
static struct TreeNode* parsingStatement();

/*** 解析函数 ***/
static struct TreeNode* parsingFunction();
static struct TreeNode* parsingFunctionParam();
static struct TreeNode* parsingFunctionParamList();
static struct TreeNode* parsingFunctionBody();

/*** 解析Statament ***/
static struct TreeNode* parsingCallStatement();
static struct TreeNode* parsingWhileStatment();
static struct TreeNode* parsingIfStatement();
static struct TreeNode* parsingElseStatement();
static struct TreeNode* parsingForStatement();
static struct TreeNode* parsingDefineStatement();
static struct TreeNode* parsingAssignStatement();
static struct TreeNode* parsingReturnStatement();
static struct TreeNode* parsingBreakStatement();
static struct TreeNode* parsingContinueStatement();
