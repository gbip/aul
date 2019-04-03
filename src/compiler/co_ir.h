//
// Created by paul on 20/03/19.
//

#ifndef AUL_IR_H
#define AUL_IR_H


#include "co_ast.h"
#include "co_symbol_table.h"

typedef struct ir_body ir_body;
typedef struct ir_ins ir_ins;

// Write the intermediate representation to a file
void ir_write_to_file(const char* filename, ir_body* root);

void ir_print_debug(ir_body* root);

ir_body* ir_build_tree(ast_body* ast);

ir_body** ir_build_instr(ir_body** p, ast_instr* ast, ts* ts);

ir_body** ir_build_instrs(ir_body** p, ast_body* ast, ts* ts);

ir_body** ir_build_decl(ir_body** p, ast_decl* ast, ts* ts);

ir_body** ir_build_assign(ir_body** p, ast_assign* ast, ts* ts);

ir_body** ir_build_expr(ir_body** p, ast_expr* ast, ts* ts);

ir_body** ir_build_print(ir_body** p, ast_print* ast, ts* ts);

void free_ir(ir_body* root);

#endif // AUL_IR_H
