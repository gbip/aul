//
// Created by paul on 20/03/19.
//

#include "co_ir.h"
#include "../aul_utils.h"
#include "../virtual_machine/vm_machine.h"
#include "../virtual_machine/vm_op_code.h"
#include "co_ast_private.h"
#include <errno.h>
#include <stdint.h>
#include <string.h>


struct ir_ins {
	enum vm_opcode_t opcode;
	uint8_t op1;
	uint32_t op2;
	/*
	struct _if {
	    ir_body* if_cond;
	    ir_body* if_body;
	};*/
};

struct ir_body {
	ir_body* next;
	ir_ins instr;
};

// Build a new instruction, chaining it to `p`.
ir_body** ir_make_instr(ir_body** p, vm_opcode_t code, uint8_t op1, uint32_t op2, ir_body* following) {
	*p = malloc(sizeof(ir_ins));
	(*p)->instr.opcode = code;
	(*p)->instr.op1 = op1;
	(*p)->instr.op2 = op2;
	(*p)->next = following;
	return &(*p)->next;
}


// Load the value `data` inside the register `reg`, chaining it `p`
ir_body** ir_load_data(ir_body** p, uint32_t data, uint8_t reg) {
	p = ir_make_instr(p, LOAD, reg, reg, NULL);
	p = ir_make_instr(p, MOVE, reg, data, NULL);
	return p;
}

// Load the variable `name` inside the register `reg`, chaining it `p
ir_body** ir_load_var(ir_body** p, const char* name, ts* ts, uint8_t reg) {
	uint32_t addr = ts_get(ts, name);
	return ir_load_data(p, addr, reg);
}

// Store the content of `reg` into the memory, using r1 as a working register
ir_body** ir_push_register_data(ir_body** p, uint8_t reg, ts* ts) {
	p = ir_make_instr(p, MOVE, 1, ts_gen_tmp(ts), NULL);
	p = ir_make_instr(p, STORE, reg, 1, NULL);
	return p;
}


ir_body** ir_build_tree(ast_body* ast) {}


ir_body** ir_build_instr(ir_body** p, ast_instr* ast, ts* ts) {}

ir_body** ir_build_instrs(ir_body** p, ast_body* ast, ts* ts) {
	p = ir_build_instr(p, ast->instr, ts);
	if(ast->next != NULL)
		p = ir_build_instrs(p, ast->next, ts);
	return p;
}


ir_body** ir_build_expr(ir_body** p, ast_expr* ast, ts* ts) {
	switch(ast->det) {
		case OP: {
			// Evaluate the left side
			p = ir_build_expr(p, ast->op->right, ts);
			// Evaluate the right side
			p = ir_build_expr(p, ast->op->left, ts);
			// Retrieve the evaluation results and store it in r0 and r1
			p = ir_load_data(p, ts_pop_tmp(ts), 0);
			p = ir_load_data(p, ts_pop_tmp(ts), 1);
			// Perform the operation
			switch(ast->op->op) {
				case OP_ADD: {
					p = ir_make_instr(p, ADD, 0, 1, NULL);
					break;
				}
				case OP_SUB: {
					p = ir_make_instr(p, SUB, 0, 1, NULL);
					break;
				}
				case OP_DIV: {
					p = ir_make_instr(p, DIV, 0, 1, NULL);
					break;
				}
				case OP_MUL: {
					p = ir_make_instr(p, MUL, 0, 1, NULL);
					break;
				}
			}
			// Store the result
			p = ir_push_register_data(p, 0, ts);
			return p;
		}
		case ID:
			// Retrieve the data associated with the ID
			p = ir_load_data(p, ts_get(ts, ast->id->name), 0);
			// Push it in as a temporary variable in the symbol table, so that it can be retrieved during operation
			// evaluation
			p = ir_push_register_data(p, 0, ts);
			return p;
		case LIT: {
			// Store the literral content in r0
			p = ir_make_instr(p, MOVE, 0, ast->literral, NULL);
			// Push r0 as a temporary variable
			p = ir_push_register_data(p, 0, ts);
			return p;
		}
	}
	return p;
}

ir_body** ir_build_decl(ir_body** p, ast_decl* ast, ts* ts) {
	// Add the new symbol to the symbol table
	ts_add(ts, ast->id->name, ast->type, 0);
	// Generate expr evaluation
	p = ir_build_expr(p, ast->expr, ts);
	// Retrieve the result pushed from the evaluation
	p = ir_load_data(p, ts_pop_tmp(ts), 0);
	// Associate the result with the variable
	p = ir_make_instr(p, STORE, 0, ts_get(ts, ast->id->name), NULL);
	return p;
}

ir_body** ir_build_assign(ir_body** p, ast_assign* ast, ts* ts) {
	// Evaluate the expression
	p = ir_build_expr(p, ast->expr, ts);
	// Store the variable address in r0
	p = ir_make_instr(p, MOVE, 0, ts_get(ast->id->name, ts), NULL);
	// Retrieve the expression result in r1
	p = ir_load_data(p, ts_pop_tmp(ts), 1);
	// Store the result at the address of the variable
	p = ir_make_instr(p, STORE, 1, 0, NULL);
	return p;
}

void ir_write_to_file(const char* filename, ir_body* root) {
	uint8_t buffer[INSTR_SIZE] = {0};

	FILE* output = fopen(filename, "w");

	if(output == NULL) {
		printf("Failed to open %s for writing : %s", filename, strerror(errno));
		return;
	}

	while(root != NULL) {
		buffer[0] = vm_opcode_to_byte(root->instr.opcode);
		buffer[1] = root->instr.op1;
		for(int i = 0; i < 4; ++i)
			buffer[i + 2] = ((uint8_t*)&root->instr.op2)[3 - i];

		fwrite(buffer, 1, sizeof(buffer), output);
		root = root->next;
	}

	fclose(output);
}
