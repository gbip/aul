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
};

struct ast_body {
    ast_instr* instr;
    ast_body* next;
};

#define CREATE_MAKE_UNION_INSTR(type, deter, typeArg) \
ast_instr* ast_make_instr_##type(typeArg arg) { \
    ast_instr* result = malloc(sizeof(ast_instr));\
    result->det = deter; \
    result->type = arg;\
    return result; \
}

CREATE_MAKE_UNION_INSTR(decl, DECL, ast_decl*);
CREATE_MAKE_UNION_INSTR(print, PRINT,ast_print*);
CREATE_MAKE_UNION_INSTR(assign, ASSIGN,ast_assign*);

/* MAKERS */

ast_body* ast_make_body(ast_instr* instr, ast_body* next) {
    ast_body* result = malloc(sizeof(ast_body));
    result->instr = instr;
    result->next = next;
    return result;
}

void ast_body_set_next(ast_body* body, ast_body* next) {
    body->next = next;
}

id* ast_make_id(char *name) {
    id* result = malloc(sizeof(id));
    result->name = name;
    return result;
}

ast_print* ast_make_print(id *anId) {
    ast_print* result = malloc(sizeof(ast_print));
    result->id = anId;
    return result;
}

ast_assign* ast_make_assign(id *anId, ast_expr *anExpr) {
    ast_assign* result = malloc(sizeof(ast_assign));
    result->id = anId;
    result->expr = anExpr;
    return result;
}

ast_decl* ast_make_decl(id *anId, type_t aType, ast_expr *anExpr) {
    ast_decl* result = malloc(sizeof(ast_decl));
    result->id = anId;
    result->type = aType;
    result->expr = anExpr;
    return result;
}

ast_op* ast_make_op(ast_expr *leftExpr, op operation, ast_expr *right) {
    ast_op* result = malloc(sizeof(ast_op));
    result->left = leftExpr;
    result->right = right;
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
            switch(expression->op->op) {
                case ADD:
                    print_offset(offset_nb);
                    printf("[ADD]\n");
                    print_expr(expression->op->left, offset_nb+4);
                    print_expr(expression->op->right, offset_nb+4);
                    break;
                case SUB:
                    print_offset(offset_nb);
                    printf("[SUB]\n");
                    print_expr(expression->op->left, offset_nb+4);
                    print_expr(expression->op->right, offset_nb+4);
                    break;
                case DIV:
                    print_offset(offset_nb);
                    printf("[DIV]\n");
                    print_expr(expression->op->left, offset_nb+4);
                    print_expr(expression->op->right, offset_nb+4);
                    break;
                case MUL:
                    print_offset(offset_nb);
                    printf("[MUL]\n");
                    print_expr(expression->op->left, offset_nb+4);
                    print_expr(expression->op->right, offset_nb+4);
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
        case EXPR: // utile seulement pour les ( expr )
            print_offset(offset_nb);
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
                    break;
                default:
                    print_offset(offset_nb);
                    printf("ERROR\n");
                    break;
            }
            break;
        case PRINT :
            print_offset(offset_nb);
            printf("[PRINT] print %s \n", node->print->id->name);
            break;
        case ASSIGN :
            print_offset(offset_nb);
            printf("[ASSIGN] %s\n",node->decl->id->name);
            if(node->decl->expr == NULL) {
                printf(";\n");
            }
            else {
                print_expr(node->decl->expr,offset_nb+4);
            }
            break;
        default:
            print_offset(offset_nb);
            printf("ERROR ! \n");
            break;
    }
}

void print_ast(struct ast_body* body) {
    printf("printing tree \n");
    int i = 0;
    ast_body* iter = body;
    ast_instr* tree;
    while(iter != NULL) {
        tree = iter->instr;
        print_node(tree,i);
        iter = iter->next;
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
    ast_free(tree->following);
}
*/

#define CREATE_MAKE_UNION(type, code, deter, field) \
    ast_expr* ast_make_expr_##type  (code field) { \
        ast_expr* result = malloc(sizeof(ast_expr)); \
        result->det = deter; \
        result->field = field; \
        return result;\
    }

CREATE_MAKE_UNION(op,ast_op*,OP,op);
CREATE_MAKE_UNION(lit,lit,LIT,literral);
CREATE_MAKE_UNION(id,id*,ID,id);
CREATE_MAKE_UNION(expr,ast_expr*,EXPR,expr);