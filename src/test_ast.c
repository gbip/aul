#include <stdio.h>
#include "ast.h"

void runtest1() {
    ast_expr* op1 = make_ast_expr_lit(12);
    ast_expr* op2 = make_ast_expr_lit(4);
    ast_op* opNode = make_ast_op(op1,ADD,op2);
    ast_expr* op3 = make_ast_expr_id("variable");
    ast_expr* op4 = make_ast_expr_op(opNode);
    id* anId = make_id("variable");
    ast_decl* declNode = make_ast_decl(anId, INT, op4);
    ast_instr* finalNode = make_ast_instr_assign(declNode,NULL);
}

int main() {
    printf("Begin tests \n");
    runtest1();
    printf("Tests ended \n");
}
