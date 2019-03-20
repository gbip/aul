//
// Created by paul on 12/03/19.
//

#ifndef AUL_AST_H
#define AUL_AST_H

#include "types.h"

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
        EXPR,

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

/* NODE MAKERS */

id* make_id(char* name);
ast_print* make_ast_print(id* anId);
ast_assign* make_ast_assign(id* anId, ast_expr* anExpr);
ast_decl* make_ast_decl(id* anId, type_t aType, ast_expr* anExpr);
ast_op* make_ast_op(ast_expr* leftExpr, op operation, ast_expr* right);
void free_ast(ast_instr* tree);


#define CREATE_MAKE_UNION(type, code, deter, field) \
    ast_expr* make_ast_expr_##type  (code field); \

CREATE_MAKE_UNION(op,ast_op*,OP,op);
CREATE_MAKE_UNION(lit,lit,LIT,literral);
CREATE_MAKE_UNION(id,id*,ID,id);
CREATE_MAKE_UNION(expr,ast_expr*,EXPR,expr);

#define CREATE_MAKE_UNION_INSTR(type, deter, typeArg) \
ast_instr* make_ast_instr_##type(typeArg arg, ast_instr* next_instr); \


CREATE_MAKE_UNION_INSTR(decl, DECL, ast_decl*);
CREATE_MAKE_UNION_INSTR(print, PRINT,ast_print*);
CREATE_MAKE_UNION_INSTR(assign, ASSIGN,ast_assign*);

#endif //AUL_AST_H

