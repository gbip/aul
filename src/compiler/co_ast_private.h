//
// Created by paul on 26/03/19.
//

#ifndef AUL_CO_AST_PRIVATE_H
#define AUL_CO_AST_PRIVATE_H
//
// Created by paul on 12/03/19.
//

#include "../aul_utils.h"
#include "co_ast.h"

ast_body* ast;

/* EXPR */
struct ast_expr {
	union {
		ast_op* op;   // opération sur deux expressions
		id* id;       // type atomique
		lit literral; // type atomique
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
	co_type_t type;
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
};

struct ast_body {
	ast_instr* instr;
	ast_body* next;
};

#endif // AUL_CO_AST_PRIVATE_H
