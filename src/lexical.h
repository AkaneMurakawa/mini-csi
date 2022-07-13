#ifndef LEXICAL_H
#define LEXICAL_H

/* token种类 */
typedef enum {
    BAD_TOKEN,                      // ?
    NUMBER_TOKEN,                   // 数字
    ADD_OPERATOR_TOKEN,             // +
    SUB_OPERATOR_TOKEN,             // -
    MUL_OPERATOR_TOKEN,             // *
    DIV_OPERATOR_TOKEN,             // /
    LEFT_OPERATOR_TOKEN,            // (
    RIGHT_OPERATOR_TOKEN,           // )
    END_OF_LINE_TOKEN               // end '\n'
} TokenKind;

#define MAX_TOKEN_SIZE (100)
typedef struct{
    TokenKind kind;                 // 类型
    double    value;                // 值
    char      str[MAX_TOKEN_SIZE];  // 字符值，最后赋值给value
} Token;

/* 数值解析状态流 */
typedef enum {
    INITIAL_STATUS,                 // 初始状态
    IN_INI_PART_STATUS,             // 整数状态，遇到数字，整数部分
    DOT_STATUS,                     // . 遇到小数点
    IN_FRAC_PART_STATUS             // 小数状态，再遇到数字，小数部分

} LexerStatus;

/* terminator */
const char DOT                      = '.',
           ENTER                    = '\n',
           LEFT_PAREN               = '(',
           RIGHT_PAREN              = ')';

/* symbols */
const char ADD                      = '+',
           SUB                      = '-',
           MUL                      = '*',
           DIV                      = '/';

/* 设置line */
void set_line(char *line);

/* 词法解析 */
void tokenizer(Token *token);

#endif