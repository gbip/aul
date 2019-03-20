#include <stdio.h>
#include "ast.h"

void runtest1() {
    /*
     *
     * cas de test :
     *  variable = 4+12
     *
     */
    ast_expr* op1 = make_ast_expr_lit(12);
    ast_expr* op2 = make_ast_expr_lit(4);
    ast_op* opNode = make_ast_op(op1,ADD,op2);
    ast_expr* op4 = make_ast_expr_op(opNode);
    id* anId = make_id("variable");
    ast_decl* declNode = make_ast_decl(anId, INT, op4);
    ast_instr* finalNode = make_ast_instr_decl(declNode,NULL);
    print_ast(finalNode);
}

int main() {
    printf("Begin tests \n");
    runtest1();
    printf("Tests ended \n");
}
