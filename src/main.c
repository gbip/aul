#include <stdio.h>
#include <fcntl.h>
#include "lex.yy.h"
#include "syntax.h"

void yyerror(char* mess) {
    printf("Line %d: %s \nFound \"%s\"\n",yylineno,mess,yytext);
}

int main(int argc, char** argv) {
    /* to remove */
    if (argc != 2) {
        printf("Usage : %s <file>\n",argv[0]);
        return 1;
    }
    printf("Building %s ...\n", argv[1]);
    yyin = fopen(argv[1], "r");
    int error = yyparse();
    fclose(yyin);
    if (error){
        printf("Compilation failed\n");
        return 1;
    } else {
        printf("OK !\n");
        return 0;
    }
}