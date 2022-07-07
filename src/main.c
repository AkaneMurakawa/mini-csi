#include <stdio.h>
#include "lexical.c"
#include "parser.c"

int main(int argc, char **argv)
{
    char buf[1024];
    const char prompt[3] = ">> ";
    printf("%s\n", "Hello, C script interpreter");
    printf("%s", prompt);
    while(fgets(buf, 1024, stdin) != NULL)
    {
        set_line(buf);
        str_look_ahead_token_exists = 0;
        double data = parse_expression();
        printf("=%lf\n", data);
    }
    return 0;
}