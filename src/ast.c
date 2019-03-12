//
// Created by paul on 12/03/19.
//

#include <stdlib.h>
#include "ast.h"


struct id {
    char *name;
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
    op op;
    ast_expr* right;
};

/* DECL */
struct ast_decl {
    id* id;
    type type;
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

/* MAKERS */

id* make_id(char* name) {
    id* result = malloc(sizeof(id));
    result->name = name;
    return result;
}

ast_instr* make_ast_instr(instr* instruction, instr_det determinant, ast_instr* next_instr) {
    ast_instr* result = malloc(sizeof(ast_instr));
    result->det = determinant;
    result->instruction = instruction;
    result->following = next_instr;
    return result;
}

ast_print* make_ast_print(id* anId) {
    ast_print* result = malloc(sizeof(ast_print));
    result->id = anId;
    return result;
}

ast_assign* make_ast_assign(id* anId, ast_expr* anExpr) {
    ast_assign* result = malloc(sizeof(ast_assign));
    result->id = anId;
    result->expr = anExpr;
    return result;
}

ast_decl* make_ast_decl(id* anId, type aType, ast_expr* anExpr) {
    ast_decl* result = malloc(sizeof(ast_decl));
    result->id = anId;
    result->type = aType;
    result->expr = anExpr;
    return result;
}

ast_expr* make_ast_expr(expr* anExpr, expr_det aDet) {
    ast_expr* result = malloc(sizeof(ast_expr));
    result->expr = anExpr;
    result->det = aDet;
    return result;
}

ast_op* make_ast_op(ast_expr* leftExpr, op operation, ast_expr* rightExpr) {
    ast_op* result = malloc(sizeof(ast_op));
    result->left = leftExpr;
    result->right = rightExpr;
    result->op = operation;
    return result;
}