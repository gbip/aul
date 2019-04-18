//
// Created by paul on 12/03/19.
//

#include "co_ast.h"
#include "../aul_utils.h"

ast_body* ast;
int init = 0;

/* IF */
struct ast_if {
    ast_expr* cond;
    ast_body* _then;
    ast_body* _else;
};

/* WHILE */
struct ast_while {
    ast_expr* cond;
    ast_body* body;
};

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
    ast_body_det det;
    union {
        ast_instr* instr;
        ast_if* _if;
        ast_while* _while;
    };
	ast_body* next;
};

#define CREATE_MAKE_UNION_INSTR(type, deter, typeArg)  \
	ast_instr* ast_make_instr_##type(typeArg arg) {    \
		ast_instr* result = malloc(sizeof(ast_instr)); \
		result->det = deter;                           \
		result->type = arg;                            \
		return result;                                 \
	}

CREATE_MAKE_UNION_INSTR(decl, DECL, ast_decl*);
CREATE_MAKE_UNION_INSTR(print, OP_PRINT, ast_print*);
CREATE_MAKE_UNION_INSTR(assign, ASSIGN, ast_assign*);

ast_body* get_ast() {
	return ast;
}

void set_ast(ast_body* new_ast) {
	ast = new_ast;
}

/* MAKERS */

ast_body* ast_make_body_instr(ast_instr *instr, ast_body *next) {
	ast_body* result = malloc(sizeof(ast_body));
	result->det = INSTR;
	result->instr = instr;
	result->next = next;
	return result;
}

ast_body* ast_make_body_if(ast_if* _if, ast_body* next) {
    ast_body* result = malloc(sizeof(ast_body));
    result->det = IF;
    result->_if = _if;
    result->next = next;
    return result;
}

ast_if* ast_make_if(ast_expr* cond, ast_body* then, ast_body* _else) {
    ast_if* result = malloc(sizeof(ast_if));
    result->cond = cond;
    result->_else = _else;
    result->_then = then;
    return result;
}

ast_body* ast_make_body_while(ast_while* _while, ast_body* next) {
    ast_body* result = malloc(sizeof(ast_body));
    result->det = WHILE;
    result->_while = _while;
    result->next = next;
    return result;
}
ast_while* ast_make_while(ast_expr* cond, ast_body* body) {
    ast_while* result = malloc(sizeof(ast_while));
    result->cond = cond;
    result->body= body;
    return result;
}

void ast_body_set_next(ast_body* body, ast_body* next) {
	body->next = next;
}

id* ast_make_id(char* name) {
	id* result = malloc(sizeof(id));
	result->name = name;
	return result;
}

ast_print* ast_make_print(id* anId) {
	ast_print* result = malloc(sizeof(ast_print));
	result->id = anId;
	return result;
}

ast_assign* ast_make_assign(id* anId, ast_expr* anExpr) {
	ast_assign* result = malloc(sizeof(ast_assign));
	result->id = anId;
	result->expr = anExpr;
	return result;
}

ast_decl* ast_make_decl(id* anId, co_type_t aType, ast_expr* anExpr) {
	ast_decl* result = malloc(sizeof(ast_decl));
	result->id = anId;
	result->type = aType;
	result->expr = anExpr;
	return result;
}

ast_op* ast_make_op(ast_expr* leftExpr, op operation, ast_expr* right) {
	ast_op* result = malloc(sizeof(ast_op));
	result->left = leftExpr;
	if(result->left == NULL) {
		switch(operation) {
			case OP_SUB : // Cas - EXPR
				result->left = ast_make_expr_lit(0);
				break;
			case OP_NOT: // Cas NOT EXPR
				//TODO
				break;
			default :
				printf("OP GENERATION ERROR !");
				exit(1);


		}
	}
	result->right = right;
	result->op = operation;
	return result;
}

void print_offset(int nb) {
	while(nb > 0) {
		printf(" ");
		nb--;
	}
}

void print_expr(ast_expr* expression, int offset_nb) {
    if(expression != NULL) {
        switch (expression->det) {
            case OP:
                switch (expression->op->op) {
                    case OP_AND:
                        print_offset(offset_nb);
                        printf("[OP_AND]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_OR:
                        print_offset(offset_nb);
                        printf("[OP_OR]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_ADD:
                        print_offset(offset_nb);
                        printf("[OP_ADD]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_SUB:
                        print_offset(offset_nb);
                        printf("[SUB]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_DIV:
                        print_offset(offset_nb);
                        printf("[DIV]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_MUL:
                        print_offset(offset_nb);
                        printf("[MUL]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_DIFF:
                        print_offset(offset_nb);
                        printf("[!=]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_EQUAL:
                        print_offset(offset_nb);
                        printf("[==]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_INF:
                        print_offset(offset_nb);
                        printf("[<]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_SUP:
                        print_offset(offset_nb);
                        printf("[>]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_SUPEQ:
                        print_offset(offset_nb);
                        printf("[>=]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_INFEQ:
                        print_offset(offset_nb);
                        printf("[<=]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        print_expr(expression->op->right, offset_nb + 4);
                        break;
                    case OP_NOT:
                        print_offset(offset_nb);
                        printf("[NOT]\n");
                        print_expr(expression->op->left, offset_nb + 4);
                        break;
                    default:
                        print_offset(offset_nb);
                        printf("ERROR\n");
                        break;
                }
                break;
            case LIT:
                print_offset(offset_nb);
                printf("[LIT] %d\n", expression->literral);
                break;
            case ID:
                print_offset(offset_nb);
                printf("[ID] %s\n", expression->id->name);
                break;
            default:
                print_offset(offset_nb);
                printf("ERROR\n");
                break;
        }
    }
}

void print_node(ast_instr* node, int offset_nb) {
	switch(node->det) {
		case DECL:
			switch(node->decl->type) {
				case INT:
					print_offset(offset_nb);
					printf("[DECL] int %s\n", node->decl->id->name);
					if(!(node->decl->expr == NULL)) {
						print_expr(node->decl->expr, offset_nb + 4);
					}
					break;
				case CONST:
					print_offset(offset_nb);
					printf("[DECL] const %s\n", node->decl->id->name);
					if(!(node->decl->expr == NULL)) {
						print_expr(node->decl->expr, offset_nb + 4);
					}
					break;
				default:
					print_offset(offset_nb);
					printf("ERROR\n");
					break;
			}
			break;
		case OP_PRINT:
			print_offset(offset_nb);
			printf("[PRINT] print %s \n", node->print->id->name);
			break;
		case ASSIGN:
			print_offset(offset_nb);
			printf("[ASSIGN] %s\n", node->assign->id->name);
			if(!(node->assign->expr == NULL)) {
				print_expr(node->assign->expr, offset_nb + 4);
			}
			break;
		default:
			print_offset(offset_nb);
			printf("ERROR ! \n");
			break;
	}
}

void print_ast_priv(struct ast_body* body, int i);

void print_if(ast_if* node, int offset_nb) {
	print_offset(offset_nb);
	printf("[IF]  \n");
	print_expr(node->cond, offset_nb + 4);
    print_offset(offset_nb);
	printf("[THEN] \n");
	print_ast_priv(node->_then, offset_nb + 4);
	if(node->_else != NULL) {
        print_offset(offset_nb);
		printf("[ELSE] \n");
		print_ast_priv(node->_else, offset_nb + 4);
	}
}

void print_while(ast_while* node, int offset_nb) {
	print_offset(offset_nb);
	printf("[WHILE]  \n");
	print_expr(node->cond, offset_nb + 4);
	print_offset(offset_nb);
	printf("[DO] \n");
	print_ast_priv(node->body, offset_nb + 4);
}

void print_ast_priv(struct ast_body* body, int i) { //i is the initial offset
	ast_body* iter = body;
	ast_instr* tree;
	while(iter != NULL) {
		switch(iter->det) {
			case INSTR :
				tree = iter->instr;
				print_node(tree, i);
				break;
			case IF :
				print_if(iter->_if,i);
				break;
			case WHILE:
				print_while(iter->_while,i);
				break;
		}
		iter = iter->next;
	}
}

void print_ast(struct ast_body* body) {
	printf("--------------------\n");
	print_ast_priv(body, 0);
	printf("--------------------\n");
}

/* FREERS */

void free_ast_expr(ast_expr* tree);

void free_ast_op(ast_op* tree) {
	if(tree != NULL) {
		free_ast_expr(tree->left);
		free_ast_expr(tree->right);
		free(tree);
	}
}

void free_id(id* tree) {
	if(tree != NULL) {
		if(tree->name != NULL) {
		    free(tree->name);
		}
		free(tree);
	}
}
void free_ast_expr(ast_expr* tree) {
	if(tree != NULL) {
		switch(tree->det) {
			case OP:
				free_ast_op(tree->op);
				break;
			case ID:
				free_id(tree->id);
				break;
			case LIT:
				break;
			default:
				break;
		}
		free(tree);
	}
}


void free_ast_decl(ast_decl* tree) {
	if(tree != NULL) {
		free_ast_expr(tree->expr);
		free_id(tree->id);
		free(tree);
	}
}

void free_ast_print(ast_print* tree) {
	if(tree != NULL) {
		free_id(tree->id);
		free(tree);
	}
}

void free_ast_assign(ast_assign* tree) {
	if(tree != NULL) {
		free_ast_expr(tree->expr);
		free_id(tree->id);
		free(tree);
	}
}

void free_ast_instr(ast_instr* tree) {
	if(tree != NULL) {
		switch(tree->det) {
			case DECL:
				free_ast_decl(tree->decl);
				break;
			case OP_PRINT:
				free_ast_print(tree->print);
				break;
			case ASSIGN:
				free_ast_assign(tree->assign);
				break;
			default:
				break;
		}
		free(tree);
	}
}

void free_ast_if(struct ast_if* tree) {
    free_ast_expr(tree->cond);
    free_ast(tree->_then);
    free_ast(tree->_else);
    free(tree);
}

void free_ast_while(struct ast_while* tree) {
    free_ast_expr(tree->cond);
    free_ast(tree->body);
    free(tree);
}

void free_ast(struct ast_body* tree) {
	if(tree != NULL) {
	    switch(tree->det) {
	        case IF:
	            free_ast_if(tree->_if);
	            break;
	        case INSTR:
                free_ast_instr(tree->instr);
	            break;
	        case WHILE:
	            free_ast_while(tree->_while);
	            break;
	    }
		if(tree->next != NULL) {
			free_ast(tree->next);
		}
		free(tree);
	}
}


#define CREATE_MAKE_UNION(type, code, deter, field)  \
	ast_expr* ast_make_expr_##type(code field) {     \
		ast_expr* result = malloc(sizeof(ast_expr)); \
		result->det = deter;                         \
		result->field = field;                       \
		return result;                               \
	}

CREATE_MAKE_UNION(op, ast_op*, OP, op);
CREATE_MAKE_UNION(lit, lit, LIT, literral);
CREATE_MAKE_UNION(id, id*, ID, id);