#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexical.h"

/* 记录输入内容 */
static char *str_line;
static int   str_line_pos;

void set_line(char *line)
{
    str_line = line;
    str_line_pos = 0;
}

void tokenizer(Token *token)
{
    /* 记录字符下标 */
    int out_pos = 0;
    char current_char;
    LexerStatus status = INITIAL_STATUS;

    token->kind = BAD_TOKEN;
    while(str_line[str_line_pos] != '\0')
    {
        current_char = str_line[str_line_pos];
        // 当前非数字，非.符号，则代表解析完毕，写入token值。IN_INI_PART_STATUS代表整数，IN_FRAC_PART_STATUS代表小数
        if ((status == IN_INI_PART_STATUS || status == IN_FRAC_PART_STATUS) && !isdigit(current_char) && current_char != DOT)
        {
            token->kind = NUMBER_TOKEN;
            // 将value写入到str
            sscanf(token->str, "%lf", &token->value);
            return;
        }
        // 跳过空格
        if(isspace(current_char)){
            if(current_char == ENTER)
            {
                token->kind = END_OF_LINE_TOKEN;
                return;
            }
            str_line_pos++;
            continue;
        }
        // token size limit
        if (out_pos >= MAX_TOKEN_SIZE)
        {
            fprintf(stderr, "token too long.\n");
        }
        // next
        str_line_pos++;
        out_pos++;
        token->str[out_pos] = current_char;

        // + - / *
        if(current_char == ADD)
        {
            token->kind = ADD_OPERATOR_TOKEN;
            return;
        }
        else if(current_char == SUB)
        {
            token->kind = SUB_OPERATOR_TOKEN;
            return;
        }      
        else if(current_char == MUL)
        {
            token->kind = MUL_OPERATOR_TOKEN;
            return;
        }      
        else if(current_char == DIV)
        {
            token->kind = DIV_OPERATOR_TOKEN;
            return;
        }
        // 数字
        else if(isdigit(current_char))
        {
            // 数字状态流
            if (status == INITIAL_STATUS)
            {
                status = IN_INI_PART_STATUS;
            }
            else if (status == DOT_STATUS)
            {
                status = IN_FRAC_PART_STATUS;
            }
        }
        // .
        else if(current_char == DOT)
        {
            if (status == IN_INI_PART_STATUS)
            {
                status == DOT_STATUS;
            }
            else
            {
                fprintf(stderr, "syntax error.\n");
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "bad character(%c).\n", current_char);
            exit(1);
        }
    }
}

void parse_line(char *buf)
{
    Token token;
    set_line(buf);

    printf("[debug] token list:\n");
    for(;;)
    {
        tokenizer(&token);
        if (token.kind == END_OF_LINE_TOKEN) break;
        else 
        {
            printf("tokenKind=%d, value=%s\n", token.kind, token.str);
        }
    }
}