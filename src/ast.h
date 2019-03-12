//
// Created by paul on 12/03/19.
//

#ifndef AUL_AST_H
#define AUL_AST_H

typedef int lit;
typedef struct id id;
typedef enum type type;

/* EXPR */
typedef union expr expr;
typedef struct ast_expr ast_expr;
typedef enum expr_det expr_det;

/* OP */
typedef enum op op;
typedef struct ast_op ast_op;

/* DECL */
typedef struct ast_decl ast_decl;

/* PRINT */
typedef struct ast_print ast_print;

/* ASSIGN */
typedef struct ast_assign ast_assign;

#endif //AUL_AST_H
