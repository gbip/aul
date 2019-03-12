#include <stdio.h>
#include "ast.h"

void runtest1() {
    ast_expr* op1 = make_ast_expr_lit(12);
    ast_expr* op2 = make_ast_expr_lit(4);

}

int main() {
    printf("Begin tests");
    runtest1();
}
