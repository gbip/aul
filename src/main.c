#include <stdio.h>
#include <fcntl.h>
#include "lex.yy.h"
#include "syntax.h"

int failed = 0;

void yyerror(char* mess) {
    printf("Syntax error line %d: %s \nFound %s\n",yylineno,mess,yytext);
    failed = 1;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage : %s <file>\n",argv[0]);
        return 1;
    }
    printf("Building %s ...\n", argv[1]);
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    if (failed){
        printf("Compilation failed\n");
        return 1;
    } else {
        printf("OK !\n");
        return 0;
    }
}