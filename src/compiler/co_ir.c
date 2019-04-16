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

struct ir_body {
    ir_body_kind kind;
	ir_body* next;
	union {
        ir_ins instr;
        ir_if _if;
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

ir_body* ir_build_body(ast_body* ast,ts* ts) {
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
    while (p != NULL) {
        result++;
        p = p->next;
    }
    return result;
}

ir_body** ir_get_end(ir_body* p) {
    ir_body* copy = p;
    while (copy->next != NULL)
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
ir_body** ir_build_if(ir_body** p, ast_if* _if, ts* ts) {
    // Build the then body
	ts_increase_depth(ts);
    ir_body* _then = ir_build_body(_if->_then,ts);
	ts_decrease_depth(ts);

    uint32_t then_size = ir_get_number_of_instr(_then) + 2;

    if(_if->_else != NULL) {
        // Build the else body
        ts_increase_depth(ts);
        ir_body *_else = ir_build_body(_if->_else, ts); /* printf("================= \n");
        print_ast(_if->_else);
        printf("================= \n");*/
        ts_decrease_depth(ts);
        uint32_t else_size = ir_get_number_of_instr(_else) + 1;
        /*printf("================= \n");
       printf("size _else : %d, size _then : %d \n", else_size, then_size);
       printf("================= \n");*/
        p = ir_build_expr(p, _if->cond, ts);
        // Load the expression result
        p = ir_load_data(p, ts_pop_tmp(ts), 0);
        p = ir_make_instr(p, JMPCRELADD, 0, then_size, NULL);
        *p = _then;
        p = ir_get_end(_then);
        p = ir_make_instr(p, JMPRELADD, 0, else_size, NULL);
        *p = _else;
        printf("================= \n");
        ir_print_debug(*p);
        printf("================= \n");
        return p;
    } else {
        p = ir_build_expr(p, _if->cond, ts);
        // Load the expression result
        p = ir_load_data(p, ts_pop_tmp(ts), 0);
        p = ir_make_instr(p, JMPCRELADD, 0, then_size, NULL);
        *p = _then;
        p = ir_get_end(_then);
        return p;
    }


};

ir_body** ir_build_while(ir_body** p, ast_while* _while, ts* ts) {
    // Generate the body of the while loop
	ts_increase_depth(ts);
    ir_body* body = ir_build_body(_while->body,ts);
	ts_decrease_depth(ts);
    uint32_t while_size = ir_get_number_of_instr(body);

    // Save the list pointer before generating the header
    ir_body** while_cond = p;


    // Generate the while header
    p = ir_build_expr(p, _while->cond, ts);


    /*printf("================= \n");
    ir_print_debug(*while_cond);
    printf("================= \n");*/

    uint32_t expr_size = ir_get_number_of_instr(*while_cond);

    p = ir_load_data(p, ts_pop_tmp(ts),0); // 1 instr
    p = ir_make_instr(p, JMPCRELADD, 0, while_size + 2, NULL); // 1 instr
    // Compute the header size
    //uint32_t while_header= ir_get_number_of_instr(while_cond);
    // Chain the body to the header
    *p = body;
    p = ir_get_end(body);
    p = ir_make_instr(p,JMPRELSUB, 0, while_size + expr_size + 2 + 2, NULL);
    printf("cond : %d & body : %d \n", expr_size , while_size);
    return p;

}

ir_body** ir_build_instrs(ir_body** p, ast_body* ast, ts* ts) {
	//p = ir_build_instr(p, ast->instr, ts);
	if(ast != NULL) {
        switch (ast->det) {
            case INSTR : {
                p = ir_build_instr(p, ast->instr, ts);
            break;
            }
            case IF : {
                p = ir_build_if(p, ast->_if, ts);
                /*printf("================= \n");
                ir_print_debug(*p);
                printf("================= \n");*/
                break;
            }
            case WHILE : {
                p = ir_build_while(p, ast->_while,ts);
                break;
            }
        }
        //print_ast(ast->next);
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
                    //OP_EQUAL, OP_DIFF, OP_SUP, OP_INF, OP_SUPEQ, OP_INFEQ
			    case OP_EQUAL : {
                    p = ir_make_instr(p, EQ, 0, 1, NULL);
                    break;
			    }
			    case OP_DIFF : {
			        p = ir_make_instr(p, EQ, 0, 1, NULL);
                    p = ir_make_instr(p, NOT , 0, 0, NULL);
                    break;
			    }
			    case OP_SUP : {
			        p = ir_make_instr(p, SUP, 0, 1, NULL);
			        break;
			    }
			    case OP_INF : {
			        p = ir_make_instr(p, INF, 0, 1, NULL);
			        break;
			    }
			    case OP_SUPEQ : {
			        p = ir_make_instr(p, SUPEQ, 0, 1, NULL);
			        break;
			    }
			    case OP_INFEQ : {
			        p = ir_make_instr(p, INFEQ, 0, 1, NULL);
			        break;
			    }
            }
			// Store the result
			p = ir_push_register_data(p, 0, ts);
			return p;
		}
		case ID:
			// Retrieve the data associated with the ID
			p = ir_load_var(p, ast->id->name, ts, 0);
			// Push it in as a temporary variable in the symbol table, so that it can be retrieved during operation
			// evaluation
			p = ir_push_register_data(p, 0, ts);
			return p;
		case LIT: {
			// Store the literral content in r0
			p = ir_make_instr(p, MOVE, 0, ast->literral, NULL);
			//printf("putting %d in litteral \n", ast->literral);
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
	// Retrieve the result pushed from the evaluation
	p = ir_load_data(p, ts_pop_tmp(ts), 0);
	// Associate the result with the variable
	p = ir_make_instr(p, STORE, 0, ts_get(ts, ast->id->name), NULL);
	return p;
}

void ir_print_debug(ir_body* root) {
    int index = 0;
	while(root != NULL) {
	    printf("%d (%#x) | ",index, index);
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
    while (start != NULL) {
        if (start->instr.opcode == STORE) {
            uint32_t addr = start->instr.op2;
            ir_body *aux = start->next;
            if (aux != NULL && aux->instr.opcode == LOAD && aux->instr.op2 == addr) {
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
void free_ir(ir_body* root) {
	if(root->next != NULL) {
		free_ir(root->next);
	}
	free(root);
}