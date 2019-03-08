#include <stdio.h>
#include <fcntl.h>
#include "lex.yy.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage : %s <file>",argv[0]);
        exit(1);
    }
    yyin = fopen(argv[1], "r");
    yylex();
    fclose(yyin);
    return 0;
}