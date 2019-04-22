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
};

struct ir_if {
	ir_body* cond;
	ir_body* _then;
	ir_body* _else;
};

struct ir_while {
	ir_body* cond;
	ir_body* _while;
};

struct ir_body {
	ir_body_kind kind;
	ir_body* next;
	union {
		ir_ins instr;
		ir_if _if;
		ir_while _while;
	};
};

// Build a new instruction, chaining it to `p`.
ir_body** ir_make_instr(ir_body** p, vm_opcode_t code, uint8_t op1, uint32_t op2, ir_body* following) {
	*p = malloc(sizeof(ir_body));
	(*p)->kind = IR_INSTR;
	(*p)->instr.opcode = code;
	(*p)->instr.op1 = op1;
	(*p)->instr.op2 = op2;
	(*p)->next = following;
	return &(*p)->next;
}


// Load the value contained at address `addr` inside the register `reg`, chaining it `p`
ir_body** ir_load_data(ir_body** p, uint32_t addr, uint8_t reg) {
	p = ir_make_instr(p, LOAD, reg, addr, NULL);
	return p;
}

// Load the variable `name` inside the register `reg`, chaining it `p
ir_body** ir_load_var(ir_body** p, const char* name, ts* ts, uint8_t reg) {
	uint32_t addr = ts_get(ts, name);
	return ir_load_data(p, addr, reg);
}

// Store the content of `reg` into the memory
ir_body** ir_push_register_data(ir_body** p, uint8_t reg, ts* ts) {
	p = ir_make_instr(p, STORE, reg, ts_gen_tmp(ts), NULL);
	return p;
}


ir_body* ir_build_tree(ast_body* ast) {
	// create symbol table
	ts* ts = ts_make();
	ir_body p;
	ir_build_instrs(&(p.next), ast, ts);
	ts_free(ts);
	return p.next;
}

ir_body* ir_build_body(ast_body* ast, ts* ts) {
	ir_body p;
	ir_build_instrs(&(p.next), ast, ts);
	return p.next;
}

ir_body** ir_build_instr(ir_body** p, ast_instr* ast, ts* ts) {
	switch(ast->det) {
		case ASSIGN:
			p = ir_build_assign(p, ast->assign, ts);
			break;
		case DECL:
			p = ir_build_decl(p, ast->decl, ts);
			break;
		case OP_PRINT:
			p = ir_build_print(p, ast->print, ts);
			break;
	}
	return p;
}

uint32_t ir_get_number_of_instr(ir_body* p) {
	uint32_t result = 0;
	while(p != NULL) {
		result++;
		p = p->next;
	}
	return result;
}

ir_body** ir_get_end(ir_body* p) {
	ir_body* copy = p;
	while(copy->next != NULL)
		copy = copy->next;
	return &(copy->next);
}


/*
 * [EXPR]
 *
 * [THEN]
 *      [BODY]
 * [ELSE]
 *      [BODY]
 * [END]
 */
ir_body** ir_build_if(ir_body** k, ast_if* _if, ts* ts) {
	*k = malloc(sizeof(ir_body));
	(*k)->kind = IR_IF;
	(*k)->next = NULL;

	// Build the then body
	ts_increase_depth(ts);
	ir_body* _then = ir_build_body(_if->_then, ts);
	ts_decrease_depth(ts);
	(*k)->_if._then = _then;

	ir_body* cond = malloc(sizeof(ir_body));
	ir_build_expr(&cond, _if->cond, ts, 0);
	(*k)->_if.cond = cond;

	if(_if->_else != NULL) {
		// Build the else body
		ts_increase_depth(ts);
		ir_body* _else = ir_build_body(_if->_else, ts);
		ts_decrease_depth(ts);
		(*k)->_if._else = _else;
	}


	return &((*k)->next);
};

ir_body** ir_build_while(ir_body** k, ast_while* _while, ts* ts) {
    *k = malloc(sizeof(ir_body));
    (*k)->kind = IR_WHILE;
    (*k)->next = NULL;
	// Generate the body of the while loop
	ts_increase_depth(ts);
	ir_body* body = ir_build_body(_while->body, ts);
	ts_decrease_depth(ts);
    (*k)->_while._while = body;



	// Generate the while header
    ir_body* cond = malloc(sizeof(ir_body));
	ir_build_expr(&cond, _while->cond, ts, 0);
    (*k)->_while.cond = cond;
    return &((*k)->next);
}

ir_body** ir_build_instrs(ir_body** p, ast_body* ast, ts* ts) {
	// p = ir_build_instr(p, ast->instr, ts);
	if(ast != NULL) {
		switch(ast->det) {
			case INSTR: {
				p = ir_build_instr(p, ast->instr, ts);
				break;
			}
			case IF: {
				p = ir_build_if(p, ast->_if, ts);
				/*printf("================= \n");
				ir_print_debug(*p);
				printf("================= \n");*/
				break;
			}
			case WHILE: {
				p = ir_build_while(p, ast->_while, ts);
				break;
			}
		}
		// print_ast(ast->next);
		p = ir_build_instrs(p, ast->next, ts);
	}
	return p;
}

ir_body** ir_build_print(ir_body** p, ast_print* ast, ts* ts) {
	// Load the var in R0
	p = ir_load_var(p, ast->id->name, ts, 0);
	// Print the variable
	p = ir_make_instr(p, PRINT, 0, 0, NULL);
	return p;
}

ir_body** ir_build_expr(ir_body** p, ast_expr* ast, ts* ts, int tmpVar) {
	switch(ast->det) {
		case OP: {
			if(ast->op->left == NULL) {
				// We only evaluate the right side, and don't need a temp var
				p = ir_build_expr(p, ast->op->right, ts, 0);
			} else {
				// Evaluate the right side
				p = ir_build_expr(p, ast->op->right, ts, 1);
				// Evaluate the left side
				p = ir_build_expr(p, ast->op->left, ts, 0);
				// Retrieve the evaluation results and store it in r0 and r1
				// p = ir_load_data(p, ts_pop_tmp(ts), 0);
				p = ir_load_data(p, ts_pop_tmp(ts), 1);
			}
			// Perform the operation
			switch(ast->op->op) {
				case OP_ADD: {
					p = ir_make_instr(p, ADD, 0, 1, NULL);
					break;
				}
				case OP_AND: {
					p = ir_make_instr(p, AND, 0, 1, NULL);
					break;
				}
				case OP_OR: {
					p = ir_make_instr(p, OR, 0, 1, NULL);
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
					// OP_EQUAL, OP_DIFF, OP_SUP, OP_INF, OP_SUPEQ, OP_INFEQ
				case OP_EQUAL: {
					p = ir_make_instr(p, EQ, 0, 1, NULL);
					break;
				}
				case OP_DIFF: {
					p = ir_make_instr(p, EQ, 0, 1, NULL);
					p = ir_make_instr(p, NOT, 0, 0, NULL);
					break;
				}
				case OP_SUP: {
					p = ir_make_instr(p, SUP, 0, 1, NULL);
					break;
				}
				case OP_INF: {
					p = ir_make_instr(p, INF, 0, 1, NULL);
					break;
				}
				case OP_SUPEQ: {
					p = ir_make_instr(p, SUPEQ, 0, 1, NULL);
					break;
				}
				case OP_INFEQ: {
					p = ir_make_instr(p, INFEQ, 0, 1, NULL);
					break;
				}
				case OP_NOT: { // To be used for logical operations only
					p = ir_make_instr(p, NOT, 0, 0, NULL);
				}
			}
			// Store the result
			if(tmpVar) {
				p = ir_push_register_data(p, 0, ts);
			}
			return p;
		}
		case ID:
			// Retrieve the data associated with the ID
			p = ir_load_var(p, ast->id->name, ts, 0);
			// Push it in as a temporary variable in the symbol table, so that it can be retrieved during operation
			// evaluation
			if(tmpVar) {
				p = ir_push_register_data(p, 0, ts);
			}
			return p;
		case LIT: {
			// Store the literral content in r0
			p = ir_make_instr(p, MOVE, 0, ast->literral, NULL);
			// printf("putting %d in litteral \n", ast->literral);
			// Push r0 as a temporary variable
			if(tmpVar) {
				p = ir_push_register_data(p, 0, ts);
			}
			return p;
		}
	}
	return p;
}

ir_body** ir_build_decl(ir_body** p, ast_decl* ast, ts* ts) {
	// Add the new symbol to the symbol table
	ts_add(ts, ast->id->name, ast->type, 0);
	// Generate expr evaluation
	p = ir_build_expr(p, ast->expr, ts, 0);
	// Retrieve the result pushed from the evaluation
	// p = ir_load_data(p, ts_pop_tmp(ts), 0);
	// Associate the result with the variable
	p = ir_make_instr(p, STORE, 0, ts_get(ts, ast->id->name), NULL);
	return p;
}

ir_body** ir_build_assign(ir_body** p, ast_assign* ast, ts* ts) {
	// Evaluate the expression
	p = ir_build_expr(p, ast->expr, ts, 0);
	// Retrieve the result pushed from the evaluation
	// p = ir_load_data(p, ts_pop_tmp(ts), 0);
	// Associate the result with the variable
	p = ir_make_instr(p, STORE, 0, ts_get(ts, ast->id->name), NULL);
	return p;
}

void ir_print_debug(ir_body* root, const char* ident) {
	int index = 0;
	while(root != NULL) {
        printf("%s", ident);
        if(root->kind == IR_INSTR) {
			printf("%d (%#x) | ", index, index);
			index++;
			switch(root->instr.opcode) {
				case MOVE: {
					printf("%s %s%d %#x \n", vm_opcode_to_str(root->instr.opcode), "r", root->instr.op1, root->instr.op2);
					break;
				}
				case LOAD: {
					printf("%s r%d [%#x] \n", vm_opcode_to_str(root->instr.opcode), root->instr.op1, root->instr.op2);
					break;
				}
				case STORE: {
					printf("%s r%d [%#x] \n", vm_opcode_to_str(root->instr.opcode), root->instr.op1, root->instr.op2);
					break;
				}
				case JMPCRELADD: {
					printf("%s r%d @%d \n", vm_opcode_to_str(root->instr.opcode), root->instr.op1, root->instr.op2);
					break;
				}
				case JMPRELADD: {
					printf("%s r%d @%d \n", vm_opcode_to_str(root->instr.opcode), root->instr.op1, root->instr.op2);
					break;
				}
				case JMPRELSUB: {
					printf("%s r%d @%#x \n", vm_opcode_to_str(root->instr.opcode), root->instr.op1, root->instr.op2);
					break;
				}
				case JMPCRELSUB: {
					printf("%s r%d @%#x \n", vm_opcode_to_str(root->instr.opcode), root->instr.op1, root->instr.op2);
					break;
				}
				default: {
					printf("%s r%d r%u \n", vm_opcode_to_str(root->instr.opcode), root->instr.op1, root->instr.op2);
					break;
				}
			}
		}
		if(root->kind == IR_IF) {
			char new_ident[80];
			strcpy(new_ident, ident);
			strcat(new_ident, "  ");
			printf("[IF]\n");

			ir_print_debug(root->_if.cond, new_ident);
			printf("[THEN]\n");
			ir_print_debug(root->_if._then, new_ident);
			if(root->_if._else != NULL) {
				printf("[ELSE]\n");
				ir_print_debug(root->_if._else, new_ident);
			}
			printf("[ENDIF]\n");
		}
        if(root->kind == IR_WHILE) {
            char new_ident[80];
            strcpy(new_ident, ident);
            strcat(new_ident, "  ");
            printf("[WHILE]\n");

            ir_print_debug(root->_while.cond, new_ident);
            printf("[DO]\n");
            ir_print_debug(root->_while._while, new_ident);
            printf("[ENDWHILE]\n");
        }
		root = root->next;
	}
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

void ir_opt_remove_contiguous_str_ld(ir_body* start) {
	while(start != NULL) {
		if(start->instr.opcode == STORE) {
			uint32_t addr = start->instr.op2;
			ir_body* aux = start->next;
			if(aux != NULL && aux->instr.opcode == LOAD && aux->instr.op2 == addr) {
				start->next = aux->next;
			}
		}
		start = start->next;
	}
}
/*
ir_body* ir_optimization(ir_body* start) {
    ir_opt_remove_contiguous_str_ld(start);
}
*/

/* Concatenates first and second together, returning the last element
 * First
 * | Instr
 * | Instr
 * | Instr
 * v
 * Second
 * | Instr
 * | Instr
 * | Instr <- Returned pointer
 * v
 * NULL
 */
ir_body* ir_concat(ir_body* first, ir_body* second) {
	while(first->next != NULL) {
		first = first->next;
	}
	first->next = second;
	while(first->next != NULL) {
		first = first->next;
	}
	return first;
}

ir_body* ir_get_last(ir_body* root, uint32_t* nb_elem) {
	nb_elem = 0;
	while(root->next != NULL) {
		root = root->next;
		nb_elem += 1;
	}

	return root;
}

ir_body* ir_flatten(ir_body* root) {
    printf("FLATTENING START\n");
	ir_body* beginning = root;
	ir_body* prev = NULL;
	while(root != NULL) {
		switch(root->kind) {
			case IR_INSTR: {
			    //printf("%#x, %#x, %#x\n", root->instr.opcode,root->instr.op1, root->instr.op2);
				prev = root;
				root = root->next;
				break;
			}
			case IR_WHILE: {
			    // Flatten nested code
                root->_while.cond = ir_flatten(root->_while.cond);
                root->_while._while = ir_flatten(root->_while._while);
                // Link the previous instruction to the condition, if there is a previous instruction
                if (prev != NULL) {
                    prev->next = root->_while.cond;
                } else {
                    beginning = root->_while.cond;
                }

                uint32_t while_size = ir_get_number_of_instr(root->_while._while);
                uint32_t expr_size = ir_get_number_of_instr(root->_while.cond);

                ir_body** p = ir_get_end(root->_while.cond);
                p = ir_make_instr(p, JMPCRELADD, 0, while_size + 2, root->_while._while);
                // Chain the body to the header
                ir_print_debug(root->_while._while,"----- ");
                p = ir_get_end(*p);
                p = ir_make_instr(p, JMPRELSUB, 0, while_size + expr_size + 2 + 1, NULL);


                *p = root->next;
                prev = root;
                root = root->next;

				break;
			}
			case IR_IF: {

			    printf("IF\n");
			    // Flatten the whole IF node through recursive call
                root->_if.cond = ir_flatten(root->_if.cond);
                root->_if._then = ir_flatten(root->_if._then);
                root->_if._else = ir_flatten(root->_if._else);

				// Link the previous instruction to the condition, if there is a previous instruction
				if (prev != NULL) {
                    prev->next = root->_if.cond;
                } else {
				    beginning = root->_if.cond;
				}

				// Chain the JMP call at the end of the condition evaluation
				uint32_t then_size = ir_get_number_of_instr(root->_if._then) + 2;
				ir_body** p = ir_get_end(root->_if.cond);
				p = ir_make_instr(p, JMPCRELADD, 0, then_size, NULL);
				// Chain the THEN body after the JMP
				*p = root->_if._then;
				p = ir_get_end(root->_if._then);

				if(root->_if._else != NULL) {
					uint32_t else_size = ir_get_number_of_instr(root->_if._else) + 1;
					// Add the jump over the else body
					p = ir_make_instr(p, JMPRELADD, 0, else_size, NULL);
					// Chain the else body
					*p = root->_if._else;
					p = ir_get_end(root->_if._else);
				}

				// Chain the rest of the code after the if evaluation
				*p = root->next;
				prev = root;
				root = root->next;

				break;
			}
		}
	}
	printf("FLATTENING DONE\n");

	return beginning;
}

void free_ir(ir_body* root) {
	if(root->next != NULL) {
		free_ir(root->next);
	}
	free(root);
}