#include <stdio.h>
#include "lexical.h"

static Token str_look_ahead_token;
static int   str_look_ahead_token_exists;  // 0: false 1: true

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

/* 获取数字 */
static double parse_primary_expression()
{
    Token token;
    get_token(&token);
    if(token.kind == NUMBER_TOKEN)
    {
        return token.value;
    }

    fprintf(stderr, "syntax error, illegal expression %s.\n", token.str);
    exit(1);
    return 0.0;  /* make compiler happy */
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
    : term
    | expression ADD term
    | expression SUB term

term
    : primary_expression
    | term MUL primary_expresion
    | term DIV primary_expresion

primary_expression
    :literal

*/
double parse_expression()
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