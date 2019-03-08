#include <stdio.h>
#include <fcntl.h>
#include "lex.yy.h"
#include "syntax.h"

void yyerror(char* mess) {
    printf("Yacc error line %d: %s \n",yylineno,mess);

}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage : %s <file>",argv[0]);
        exit(1);
    }
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    return 0;
}