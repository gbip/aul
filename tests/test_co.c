//
// Created by paul on 21/03/19.
//

#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include <setjmp.h>
#include <cmocka.h>
#include <co_symbol_table.h>
#include <stdio.h>

#include "../src/compiler/co_ast.h"

typedef struct {int input; int expected;} vector_t;

const vector_t vectors[] = {
        {0,0},
        {1,2},
        {2,4},
        {INT_MAX/2, INT_MAX-1},
        {INT_MAX, -2},
};

static void test_ast(void **state)
{
    id* anId = ast_make_id("variable");
    ast_expr* op1 = ast_make_expr_lit(12);
    ast_expr* op2 = ast_make_expr_id(anId);
    ast_op* opNode = ast_make_op(op1, OP_ADD, op2);
    ast_expr* op4 = ast_make_expr_op(opNode);
    id* id2 = ast_make_id("var2");
    ast_print* printNode = ast_make_print(anId);
    ast_assign* assignNode = ast_make_assign(id2,op4);
    ast_instr* finalNode4 = ast_make_instr_assign(assignNode);
    ast_instr* finalNode3 = ast_make_instr_print(printNode);
    ast_decl* simpleDecl = ast_make_decl(id2, CONST, NULL);
    ast_instr* finalNode2 = ast_make_instr_decl(simpleDecl);
    ast_decl* declNode = ast_make_decl(anId, INT, op4);
    ast_instr* finalNode = ast_make_instr_decl(declNode);
    ast_body* bod1 = ast_make_body(finalNode,NULL);
    ast_body* bod2 = ast_make_body(finalNode2,NULL);
    ast_body* bod3 = ast_make_body(finalNode3,NULL);
    ast_body* bod4 = ast_make_body(finalNode4,NULL);
    ast_body_set_next(bod1,bod2);
    ast_body_set_next(bod2,bod3);
    ast_body_set_next(bod3,bod4);
    //print_ast(bod1);
    free_ast(bod1);
}

void test_ts(void **state) {
    ts* ts = ts_make();
    ts_add(ts, "var1", INT, 0);
    ts_add(ts, "var2", CONST, 0);
    ts_add(ts, "var3", INT, 0);
    ts_add(ts, "var4", INT, 1);
    ts_pop_current_depth(ts);
    assert_null(ts_get(ts,"var4"));
    ts_add(ts,"var4", INT,1);
    assert_non_null(ts_get(ts,"var4"));
    ts_add(ts,"var5", INT, 0);
    ts_add(ts, "var6", INT, 1);
    assert_non_null(ts_get(ts,"var6"));
    ts_add(ts,"var7", INT,2);
    ts_add(ts,"var7_1", INT,2);
    ts_add(ts,"var8", INT, 3);
    ts_add(ts, "var9", INT, 2);
    assert_non_null(ts_get(ts,"var7"));
    ts_pop_current_depth(ts);
    assert_null(ts_get(ts,"var9"));
    assert_non_null(ts_get(ts,"var8"));
    ts_pop_current_depth(ts);
    assert_null(ts_get(ts,"var8"));
    ts_pop_current_depth(ts);
    ts_pop_current_depth(ts);
    assert_null(ts_get(ts,"var7"));
    assert_null(ts_get(ts,"var7_1"));
    assert_non_null(ts_get(ts,"var4"));
    ts_pop_current_depth(ts);
    ts_pop_current_depth(ts);
    ts_pop_current_depth(ts);
    ts_pop_current_depth(ts);

    for (int i = 0; i < 9; i++) {
        char buffer[15];
        sprintf(buffer, "var%d", i);
        assert_null(ts_get(ts, buffer));
    }
    ts_free(ts);
}

int main()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_ast),
            cmocka_unit_test(test_ts),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}