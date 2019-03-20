#include <stdio.h>
#include <assert.h>
#include "ast.h"
#include "symbol_table.h"

void ast_tests() {    /*
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

}

int main() {
    printf("Begin AST tests \n");
    ast_tests();
    printf("AST tests successfull \n");
    printf("Begin symbol table tests \n");
    symbol_table_tests();
    printf("Symbol table tests successfull \n");
}
