#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"
#include "Keywords.h"
#include "Scanner.h"

static int cur_state;
static int pos;   // 即将读取的字符的下一个位置
static char buff[1024];
static TokenType token_type;

static int getTableColIndex(char ch);
static struct TokenNode* newTokenNode(const char* value, int lineno, TokenType tokenType);
static char* getNextToken(const char* str, int len);

const char* tokenTypeStr[6] = 
{
    "Keyword", "Symbol", "Indentifier", "IntegerConstant", "StringConstant", "NULLToken"
};

// 10种输入类型分类分别为: (0)数字, (1)字母, (2)_, (3)/, (4)*, (5)", (6)空格orTAB, (7)/n, (8)/r, (9)其他
const static int state_table[9][10] = 
{
    {2, 1, 1, 3, 8, 7, 0, 0, 0, 8}, /* STATE_START 0 */
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, /* STATE_KEY_ID 1 */
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0}, /* STATE_NUM 2 */
    {8, 8, 8, 4, 5, 0, 8, 0, 0, 8}, /* STATE_COMMIT1 3 */
    {4, 4, 4, 4, 4, 4, 4, 0, 0, 4}, /* STATE_COMMIT2 4 */
    {5, 5, 5, 5, 6, 5, 5, 5, 5, 5}, /* STATE_COMMIT3 5 */
    {5, 5, 5, 0, 5, 6, 5, 5, 5, 5}, /* STATE_COMMIT4 6 */
    {7, 7, 7, 7, 7, 0, 7, 7, 7, 7}, /* STATE_STRING 7 */
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, /* STATE_SYMBOL 8 */
};

struct TokenNode* newTokenNode(const char* value, int lineno, TokenType tokenType)
{
    struct TokenNode* pnode = (struct TokenNode*)malloc(sizeof(struct TokenNode));
    pnode->value = (char*)malloc(sizeof(char)*(strlen(value)+1));
    strcpy(pnode->value, value);
    pnode->lineno = lineno;
    pnode->tokenType = tokenType;
    pnode->next = pnode->last = NULL;

    return pnode;
}

void freeTokenNode(struct TokenNode* pnode)
{
    free(pnode->value);
    free(pnode);
}

TokenList getTokenStream(const char* filename)
{
    FILE* fp;
    char str[4096];
    cur_state = STATE_START;
    int lineno = 0;

    // token链表的头结点和尾结点
    struct TokenNode* head = NULL, *rear = head;

    if ( (fp = fopen(filename, "r")) == NULL ) 
    {
        puts("Fail to open file!");
        exit(0);
    }

    initKeywords();

    //循环读取文件的每一行数据
    while(fgets(str, sizeof(str), fp) != NULL ) 
    {
        pos = 0;
        lineno++;
        int len = strlen(str);
        while (pos < len)
        {
            token_type = NULL_TOKEN;
            char* token = getNextToken(str, len);
            if (token_type == NULL_TOKEN) 
                continue;
            // printf("token_type: %d, cur_token: %s\n", token_type, token);

            // 新建一个token结点
            struct TokenNode* pnode = newTokenNode(token, lineno, token_type);

            if (head == NULL)
            {
                head = newTokenNode("", 0, NULL_TOKEN);
                rear = head;
            }
            rear->next = pnode;
            pnode->last = rear;
            rear = pnode;
        }
    }

    fclose(fp);
    freeKeywords();

    return head;
}

static int getTableColIndex(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;
    if (ch >= '0' && ch <= '9')
        return 0;
    switch (ch)
    {
        case ' ':
        case 9:           // 空格或TAB键
            return 6;
        case '_':
            return 2;
        case '*':
            return 4;
        case '/':
            return 3;
        case '"':
            return 5;
        case '\n':
            return 7;
        case '\r':
            return 8;
    }
    return 9;
}

static char* getNextToken(const char* str, int len)
{
    int i = 0;
    while (pos < len)
    {
        char ch = str[pos];
        cur_state = state_table[cur_state][getTableColIndex(ch)];
        if (token_type == NULL_TOKEN)
        {
            switch (cur_state)
            {
                case STATE_KEY_ID:
                    token_type = IDENTIFIER;
                    break;
                case STATE_SYMBOL:
                    token_type = SYMBOL;
                    if (i == 1 && buff[0] == '/')
                        cur_state = STATE_START;
                    break;
                case STATE_NUM:
                    token_type = INT_CONST;
                    break;
                case STATE_STRING:
                    token_type = STRING_CONST;
                    break;
            }
        }
        if (cur_state == STATE_START)
        {
            if (i == 0 || token_type == STRING_CONST)
                pos++;
            break;
        }
        buff[i++] = ch;
        pos++;
    }
    buff[i] = '\0';
    if (token_type == IDENTIFIER && isKeyword(buff))
        token_type = KEYWORD;
    if (token_type == STRING_CONST)
        return buff+1;
    else 
        return buff;
}
