#include <stdio.h>
#include <fcntl.h>
#include "gen/lex.yy.h"
#include "gen/syntax.h"
#include "co_ir.h"

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
    void * file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File does not exist");
        return 1;
    }
    yyin = file;
    int error = yyparse();
    fclose(yyin);
    if (error){
        printf("Compilation failed\n");
        return 1;
    } else {
        print_ast(get_ast());
        free_ast(get_ast());
        printf("AST build, building intermediate representation tree ...\n");
        ir_body* irt = ir_build_tree(get_ast());
        fclose(file);
        //free_ast(get_ast());
        return 0;
    }
}