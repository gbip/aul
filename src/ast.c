//
// Created by paul on 12/03/19.
//

#include <stdlib.h>
#include "ast.h"




/* EXPR */
struct ast_expr {
    union {
        ast_op* op;
        id* id;
        lit literral;
        ast_expr* expr;
    };
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

struct ast_instr {
    union {
        ast_decl* decl;
        ast_print* print;
        ast_assign* assign;
    };
    instr_det det;

    // Following instruction
    ast_instr* following;
};

#define CREATE_MAKE_UNION_INSTR(type, deter, typeArg) \
ast_instr* make_ast_instr_##type(typeArg arg, ast_instr* next_instr) { \
    ast_instr* result = malloc(sizeof(ast_instr));\
    result->det = deter; \
    result->type = arg;\
    result->following = next_instr;\
    return result; \
}

CREATE_MAKE_UNION_INSTR(decl, DECL, ast_decl*);
CREATE_MAKE_UNION_INSTR(print, PRINT,ast_print*);
CREATE_MAKE_UNION_INSTR(assign, ASSIGN,ast_assign*);

/* MAKERS */

id* make_id(char* name) {
    id* result = malloc(sizeof(id));
    result->name = name;
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

ast_op* make_ast_op(ast_expr* leftExpr, op operation, ast_expr* rightExpr) {
    ast_op* result = malloc(sizeof(ast_op));
    result->left = leftExpr;
    result->right = rightExpr;
    result->op = operation;
    return result;
}

/* FREERS */
/*
void free_ast_expr(ast_expr* tree);

void free_ast_op(ast_op* tree) {
    free_ast_expr(tree->left);
    free_ast_expr(tree->right);
    free(tree);
}

void free_ast_expr(ast_expr* tree) {
    switch(tree->det) {
        case OP:
            free_ast_op(tree->expr);
            break;
        case ID:
            free(tree->expr);
            break;
        case EXPR:
            free_ast_expr(tree->expr);
            break;
    }
    free(tree);
}

void free_ast_decl(ast_decl* tree) {
    free_ast_expr(tree->expr);
    free(tree->id);
    free(tree);
}

void free_ast_print(ast_print* tree) {
    free(tree->id);
    free(tree);
}

void free_ast_assign(ast_assign* tree) {
    free_ast_expr(tree->expr);
    free(tree->id);
    free(tree);
}

void free_ast(ast_instr* tree) {
    switch(tree->det) {
        case DECL:
            free_ast_decl(tree->instruction);
            break;
        case PRINT:
            free_ast_print(tree->instruction);
            break;
        case ASSIGN:
            free_ast_assign(tree->instruction);
            break;
        default:
            break;
    }
    free(tree);
    free_ast(tree->following);
}
*/

#define CREATE_MAKE_UNION(type, code, deter, field) \
    ast_expr* make_ast_expr_##type  (code field) { \
        ast_expr* result = malloc(sizeof(ast_expr)); \
        result->det = deter; \
        result->field = field; \
        return result;\
    }

CREATE_MAKE_UNION(op,ast_op*,OP,op);
CREATE_MAKE_UNION(lit,lit,LIT,literral);
CREATE_MAKE_UNION(id,id*,ID,id);
CREATE_MAKE_UNION(expr,ast_expr*,EXPR,expr);