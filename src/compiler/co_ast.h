//
// Created by paul on 12/03/19.
//

#ifndef AUL_AST_H
#define AUL_AST_H

#include "co_types.h"

typedef int lit;
typedef struct id {
    char *name;
} id;

/* EXPR */
typedef union expr expr;
typedef struct ast_expr ast_expr;
typedef enum expr_det {
        OP,
        ID,
        LIT,

}expr_det;

/* OP */
typedef enum op {
    ADD,
    SUB,
    DIV,
    MUL
} op;
typedef struct ast_op ast_op;

/* DECL */
typedef struct ast_decl ast_decl;

/* PRINT */
typedef struct ast_print ast_print;

/* ASSIGN */
typedef struct ast_assign ast_assign;

/* INSTRUCTION */
typedef enum instr_det {
    DECL,
    PRINT,
    ASSIGN,
}instr_det;
typedef struct ast_instr ast_instr;

/* BODY */
typedef struct ast_body ast_body;

/* NODE MAKERS */

id* ast_make_id(char *name);
ast_print* ast_make_print(id *anId);
ast_assign* ast_make_assign(id *anId, ast_expr *anExpr);
ast_decl* ast_make_decl(id *anId, co_type_t aType, ast_expr *anExpr);
ast_op* ast_make_op(ast_expr *leftExpr, op operation, ast_expr *right);
ast_body* ast_make_body(ast_instr* instr, ast_body* next);


#define CREATE_MAKE_UNION_H(type, code, deter, field) \
    ast_expr* ast_make_expr_##type  (code field); \

CREATE_MAKE_UNION_H(op,ast_op*,OP,op);
CREATE_MAKE_UNION_H(lit,lit,LIT,literral);
CREATE_MAKE_UNION_H(id,id*,ID,id);
CREATE_MAKE_UNION_H(expr,ast_expr*,EXPR,expr);

#define CREATE_MAKE_UNION_INSTR_H(type, deter, typeArg) \
ast_instr* ast_make_instr_##type(typeArg arg); \


CREATE_MAKE_UNION_INSTR_H(decl, DECL, ast_decl*);
CREATE_MAKE_UNION_INSTR_H(print, PRINT,ast_print*);
CREATE_MAKE_UNION_INSTR_H(assign, ASSIGN,ast_assign*);

/* BODY OPERATIONS */
void ast_body_set_next(ast_body* body, ast_body* next);

/* UTILS */
void print_ast(struct ast_body* body);
void free_ast(ast_body *tree);
ast_body* get_ast();
void set_ast(ast_body*);

#endif //AUL_AST_H

