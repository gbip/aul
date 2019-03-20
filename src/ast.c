//
// Created by paul on 12/03/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

/* EXPR */
struct ast_expr {
    union {
        ast_op* op; // opération sur deux expressions
        id* id; // type atomique
        lit literral; // type atomique
        ast_expr* expr; // autre expression
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
    type_t type;
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

    // Following instruction
    ast_instr* following;
};


#define CREATE_MAKE_UNION_INSTR(type, deter, typeArg) \
ast_instr* make_ast_instr_##type(typeArg arg, ast_instr* next_instr) { \
    ast_instr* result = malloc(sizeof(ast_instr));\
    result->det = deter; \
    result->type = arg;\
    result->following = next_instr;\
    return result; \
}

CREATE_MAKE_UNION_INSTR(decl, DECL, ast_decl*);
CREATE_MAKE_UNION_INSTR(print, PRINT,ast_print*);
CREATE_MAKE_UNION_INSTR(assign, ASSIGN,ast_assign*);

/* MAKERS */

id* make_id(char* name) {
    id* result = malloc(sizeof(id));
    result->name = name;
    return result;
}

ast_print* make_ast_print(id* anId) {
    ast_print* result = malloc(sizeof(ast_print));
    result->id = anId;
    return result;
}

ast_assign* make_ast_assign(id* anId, ast_expr* anExpr) {
    ast_assign* result = malloc(sizeof(ast_assign));
    result->id = anId;
    result->expr = anExpr;
    return result;
}

ast_decl* make_ast_decl(id* anId, type_t aType, ast_expr* anExpr) {
    ast_decl* result = malloc(sizeof(ast_decl));
    result->id = anId;
    result->type = aType;
    result->expr = anExpr;
    return result;
}

ast_op* make_ast_op(ast_expr* leftExpr, op operation, ast_expr* rightExpr) {
    ast_op* result = malloc(sizeof(ast_op));
    result->left = leftExpr;
    result->right = rightExpr;
    result->op = operation;
    return result;
}

void print_offset(int nb) {
    while(nb>0) {
        printf(" ");
        nb--;
    }
}

void print_expr(ast_expr* expression, int offset_nb) {
    switch(expression->det) {
        case OP:
            print_offset(offset_nb);
            break;
        case LIT:
            print_offset(offset_nb);
            printf("[LIT] %d\n", expression->literral);
            break;
        case EXPR:
            print_offset(offset_nb);
            break;
        case ID:
            print_offset(offset_nb);
            printf("[ID] %d\n", expression->id->name);
            break;
        default:
            printf("ERROR\n");
            break;
    }
}

void print_node(ast_instr* node, int offset_nb) {
    switch(node->det) {
        case DECL :
            switch(node->decl->type) {
                case INT:
                    print_offset(offset_nb);
                    printf("[DECL] int %s\n",node->decl->id->name);
                    if(node->decl->expr == NULL) {
                        printf(";\n");
                    }
                    else {
                        print_expr(node->decl->expr,offset_nb+4);
                    }
                    break;
                case CONST:
                    print_offset(offset_nb);
                    printf("[DECL] const %s\n",node->decl->id->name);
                    if(node->decl->expr == NULL) {
                        printf(";\n");
                    }
                    else {
                        print_expr(node->decl->expr,offset_nb+4);
                    }
                default:
                    break;
            }
            break;
        case PRINT :
            print_offset(offset_nb);
            printf("[PRINT] print %s \n", node->print->id->name);
        case ASSIGN :
            print_offset(offset_nb);
            printf("[ASSIGN] %s\n",node->decl->id->name);
            if(node->decl->expr == NULL) {
                printf(";\n");
            }
            else {
                print_expr(node->decl->expr,offset_nb+1);
            }
        default:
            printf("ERROR ! \n");
    }
}

void print_ast(struct ast_instr* tree) {
    printf("printing tree \n");
    int i = 0;
    while(tree != NULL) {
        print_node(tree,i);
        tree = tree->following;
        i+=4;
    }
}

/* FREERS */
/*
void free_ast_expr(ast_expr* tree);

void free_ast_op(ast_op* tree) {
    free_ast_expr(tree->left);
    free_ast_expr(tree->right);
    free(tree);
}

void free_ast_expr(ast_expr* tree) {
    switch(tree->det) {
        case OP:
            free_ast_op(tree->expr);
            break;
        case ID:
            free(tree->expr);
            break;
        case EXPR:
            free_ast_expr(tree->expr);
            break;
    }
    free(tree);
}

void free_ast_decl(ast_decl* tree) {
    free_ast_expr(tree->expr);
    free(tree->id);
    free(tree);
}

void free_ast_print(ast_print* tree) {
    free(tree->id);
    free(tree);
}

void free_ast_assign(ast_assign* tree) {
    free_ast_expr(tree->expr);
    free(tree->id);
    free(tree);
}

void free_ast(ast_instr* tree) {
    switch(tree->det) {
        case DECL:
            free_ast_decl(tree->instruction);
            break;
        case PRINT:
            free_ast_print(tree->instruction);
            break;
        case ASSIGN:
            free_ast_assign(tree->instruction);
            break;
        default:
            break;
    }
    free(tree);
    free_ast(tree->following);
}
*/

#define CREATE_MAKE_UNION(type, code, deter, field) \
    ast_expr* make_ast_expr_##type  (code field) { \
        ast_expr* result = malloc(sizeof(ast_expr)); \
        result->det = deter; \
        result->field = field; \
        return result;\
    }

CREATE_MAKE_UNION(op,ast_op*,OP,op);
CREATE_MAKE_UNION(lit,lit,LIT,literral);
CREATE_MAKE_UNION(id,id*,ID,id);
CREATE_MAKE_UNION(expr,ast_expr*,EXPR,expr);