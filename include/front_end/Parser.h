#pragma once

#include "SyntaxTree.h"

extern struct TokenNode *ptoken;

/*** 外部调用接口：解析expression ***/
struct TreeNode* parsingExpression();

/*** 解析&,|运算term ***/ 
struct TreeNode* parsingAndOrTerm();

/*** 解析&,| ***/ 
struct TreeNode* parsingAndOrOpSymbol();

/*** 解析比较运算term ***/
struct TreeNode* parsingCompTerm();

/*** 解析运算符<, >, <=, >=, == ***/
struct TreeNode* parsingCompOpSymbol();

/*** 解析+,-term ***/ 
struct TreeNode* parsingAddSubTerm();

// 解析+,-符号
struct TreeNode* parsingAddSubSymbol();

/*** 解析*,/的term ***/ 
struct TreeNode* parsingMulDivTerm();

/*** 解析*,/符号 ***/
struct TreeNode* parsingMulDivSymbol();

/*** 解析() ***/
struct TreeNode* parsingExpBracket();

struct TreeNode* parsingArrayRef();


struct TreeNode* parsingStatements();
struct TreeNode* parsingStatement();

/*** 解析函数 ***/
struct TreeNode* parsingFunction();
struct TreeNode* parsingFunctionParam();
struct TreeNode* parsingFunctionParamList();
struct TreeNode* parsingFunctionBody();

/*** 解析Statament ***/
struct TreeNode* parsingCallStatement();
struct TreeNode* parsingWhileStatment();
struct TreeNode* parsingIfStatement();
struct TreeNode* parsingElseStatement();
struct TreeNode* parsingForStatement();
struct TreeNode* parsingDefineStatement();
struct TreeNode* parsingAssignStatement();
struct TreeNode* parsingReturnStatement();
struct TreeNode* parsingBreakStatement();
struct TreeNode* parsingContinueStatement();
