//
// Created by paul on 12/03/19.
//

#ifndef AUL_AST_H
#define AUL_AST_H

typedef int lit;
typedef struct id id;
typedef enum type {
    INT,
    CONST,
} type;

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
typedef union instr instr;
typedef enum instr_det {
    DECL,
    PRINT,
    ASSIGN,
}instr_det;
typedef struct ast_instr ast_instr;

/* NODE MAKERS */

id* make_id(char* name);
ast_instr* make_ast_instr(instr* instruction, instr_det determinant, ast_instr* next_instr);
ast_print* make_ast_print(id* anId);
ast_assign* make_ast_assign(id* anId, ast_expr* anExpr);
ast_decl* make_ast_decl(id* anId, type aType, ast_expr* anExpr);
ast_expr* make_ast_expr(expr* anExpr, expr_det aDet);
ast_op* make_ast_op(ast_expr* leftExpr, op operation, ast_expr* right);

#endif //AUL_AST_H
