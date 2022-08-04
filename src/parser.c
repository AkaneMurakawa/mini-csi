#include <stdio.h>

#include "lexical.h"

static Token str_look_ahead_token;
static int   str_look_ahead_token_exists;  // 0: false 1: true

/* 函数声明 */
static double parse_expression();

/* 获取token */
static void get_token(Token *token)
{

    if (str_look_ahead_token_exists)
    {
        *token = str_look_ahead_token;
        str_look_ahead_token_exists = 0;
    }
    else
    {
        tokenizer(token);
        if (token->kind != END_OF_LINE_TOKEN)
        {
            printf("tokenKind=%d, value=%s\n", token->kind, token->str);
        }
    }
}

/* 标记token已存在 */
static void unget_token(Token *token)
{
    str_look_ahead_token = *token;
    str_look_ahead_token_exists = 1;
}

/* 获取值 */
static double parse_primary_expression()
{
    Token token;
    double value;
    int minus_flag = 0;
    get_token(&token);
    if (token.kind == SUB_OPERATOR_TOKEN)
    {
        minus_flag = 1;
    }
    else
    {
        unget_token(&token);
    }

    get_token(&token);
    if (token.kind == NUMBER_TOKEN)
    {
        value = token.value;
    }
    else if (token.kind == LEFT_OPERATOR_TOKEN)
    {
        // 递归解析(expression)
        value = parse_expression();
        get_token(&token);
        if (token.kind != RIGHT_OPERATOR_TOKEN)
        {
            fprintf(stderr, "syntax error, missing ')' %s.\n", token.str);
            exit(1);
        }
    }
    else{
        unget_token(&token);
    }
    if (minus_flag)
    {
        value = -value;
    }
    return value;
}

/* * \/ 操作 */
static double parse_term()
{
    double left = parse_primary_expression();
    double right;
    double result = left;
    Token token;

    for (;;)
    {
        get_token(&token);
        // 无需 * /
        if (token.kind != MUL_OPERATOR_TOKEN && token.kind != DIV_OPERATOR_TOKEN)
        {
            unget_token(&token);
            break;
        }
        right = parse_primary_expression();
        if (token.kind == MUL_OPERATOR_TOKEN)
        {
            result *= right;
        }
        else if (token.kind == DIV_OPERATOR_TOKEN)
        {
            result /= right;
        }
    }
    return result;
}

/*
expression
    : term                              // 项
    | expression ADD term               // 表达式 + 项

term
    : primary_expression                // 优先表达式
    | term MUL primary_expresion        // 项 * 优先表达式
    | term DIV primary_expresion        // 项 / 优先表达式

primary_expression
    :literal                            // 常量
    | ( expression )                    // 表达式
    | SUB ( expression )                // 负数

*/
static double parse_expression()
{
    double left = parse_term();
    double right;
    double result = left;
    Token token;
    for (;;)
    {
        get_token(&token);
        if (token.kind == END_OF_LINE_TOKEN)
        {
            break;
        }
        // 无需 + -
        if (token.kind != ADD_OPERATOR_TOKEN && token.kind != SUB_OPERATOR_TOKEN)
        {
            unget_token(&token);
            break;
        }
        right = parse_term();
        if (token.kind == ADD_OPERATOR_TOKEN)
        {
            result += right;
        }
        else if (token.kind == SUB_OPERATOR_TOKEN)
        {
            result -= right;
        }
        else
        {
            unget_token(&token);
        }
    }
    return result;
    
}