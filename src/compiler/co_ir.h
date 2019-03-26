//
// Created by paul on 20/03/19.
//
#include "co_ast.h"

#ifndef AUL_IR_H
#define AUL_IR_H


typedef struct ir_body ir_body;
typedef struct ir_ins ir_ins;

ir_body* ir_build_tree(ast_body* ast);

#endif //AUL_IR_H
