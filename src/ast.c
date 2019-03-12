//
// Created by paul on 12/03/19.
//

#include "ast.h"


struct id{};

enum type{
    INT,
    CONST,
};


/* EXPR */
union expr {
    ast_op* op;
    id* id;
    lit literral;
    ast_expr* expr;
};

enum expr_det {
    OP,
    ID,
    LIT,
    EXPR,
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

enum op {
    ADD,
    SUB,
    DIV,
    MUL
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