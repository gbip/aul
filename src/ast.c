//
// Created by paul on 12/03/19.
//

#include "ast.h"


struct id{
    char* name;
};

/* EXPR */
union expr {
    ast_op* op;
    id* id;
    lit literral;
    ast_expr* expr;
};

struct ast_expr {
    expr* expr;
    expr_det det;
};

/* OP */
struct ast_op {
    ast_expr* left;
    op* op;
    ast_expr* right;
};

/* DECL */
struct ast_decl {
    id* id;
    type* type;
    ast_expr* expr;
};

/* PRINT */
struct ast_print {
    id* id;
};

/* ASSIGN */
struct ast_assign {
    id* id;
    ast_expr* expr;
};

/* INSTRUCTION */
union instr {
    ast_decl* decl;
    ast_print* print;
    ast_assign* assign;
};


struct ast_instr {
    // Data
    instr* instruction;
    instr_det det;

    // Following instruction
    ast_instr* following;
};