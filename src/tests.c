#include <stdio.h>
#include <assert.h>
#include "ast.h"
#include "symbol_table.h"

void ast_tests() {
    /*
     *
     * cas de test :
     *  variable = 4+12;
     *  const var2;
     *  print(var2);
     *
     */
    id* anId = ast_make_id("variable");
    ast_expr* op1 = ast_make_expr_lit(12);
    ast_expr* op2 = ast_make_expr_id(anId);
    ast_op* opNode = ast_make_op(op1, ADD, op2);
    ast_expr* op4 = ast_make_expr_op(opNode);
    id* id2 = ast_make_id("var2");
    ast_print* printNode = ast_make_print(anId);
    ast_assign* assignNode = ast_make_assign(id2,op4);
    ast_instr* finalNode4 = ast_make_instr_assign(assignNode, NULL);
    ast_instr* finalNode3 = ast_make_instr_print(printNode, finalNode4);
    ast_decl* simpleDecl = ast_make_decl(id2, CONST, NULL);
    ast_instr* finalNode2 = ast_make_instr_decl(simpleDecl, finalNode3);
    ast_decl* declNode = ast_make_decl(anId, INT, op4);
    ast_instr* finalNode = ast_make_instr_decl(declNode,finalNode2);
    print_ast(finalNode);
}

void symbol_table_tests() {
    ts* ts = ts_make();
    ts_add(ts, "var1", INT, 0);
    ts_add(ts, "var2", CONST, 0);
    ts_add(ts, "var3", INT, 0);
    ts_add(ts, "var4", INT, 1);
    ts_pop_current_depth(ts);
    assert(ts_get(ts,"var4")==NULL);
    ts_add(ts,"var4", INT,1);
    assert(ts_get(ts,"var4")!=NULL);
    ts_add(ts,"var5", INT, 0);
    ts_add(ts, "var6", INT, 1);
    assert(ts_get(ts,"var6") != NULL);
    ts_add(ts,"var7", INT,2);
    ts_add(ts,"var7_1", INT,2);
    ts_add(ts,"var8", INT, 3);
    ts_add(ts, "var9", INT, 2);
    assert(ts_get(ts,"var7")!= NULL);
    ts_pop_current_depth(ts);
    assert(ts_get(ts,"var9")==NULL);
    assert(ts_get(ts,"var8") != NULL);
    ts_pop_current_depth(ts);
    assert(ts_get(ts,"var8") == NULL);
    ts_pop_current_depth(ts);
    ts_pop_current_depth(ts);
    assert(ts_get(ts,"var7")== NULL);
    assert(ts_get(ts,"var7_1")== NULL);
    assert(ts_get(ts,"var4")!=NULL);
    ts_pop_current_depth(ts);
    ts_pop_current_depth(ts);
    ts_pop_current_depth(ts);
    ts_pop_current_depth(ts);

    for (int i = 0; i < 9; i++) {
        char buffer[15];
        sprintf(buffer, "var%d", i);
        assert(ts_get(ts, buffer) == NULL);
    }
    ts_free(ts);
}

int main() {
    printf("Begin AST tests \n");
    ast_tests();
    printf("AST tests successfull \n");
    printf("Begin symbol table tests \n");
    symbol_table_tests();
    printf("Symbol table tests successfull \n");
}
