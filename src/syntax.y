%{
    #include "ast.h"
    #include <stdlib.h>

    ast_instr* ast;
%}

%code requires {#include "ast.h"}

%union
{
    int intValue;
    id* idValue;
    ast_expr* ast_expr;
    ast_print* ast_print;
    ast_decl* ast_decl;
    ast_assign* ast_assign;
    type type;
    op op;
}

%token tMAIN
%token tPRINT
%token tACCO
%token tACCF
%token tPARO
%token tMOINS
%token tPARF
%token tSEP
%token tPLUS
%token tDIV
%token tMUL
%token tINT
%token tCONST
%token tEGAL
%token tENDL
%token <intValue> tLITT
%token <intValue> tLITTEXP
%token <idValue> tID

%type <ast_expr> EXPR
%type <op> OP
%type <type> DECLKW
%type <ast_print> PRINT
%type <ast_decl> DECL
%type <ast_assign> ASSIGN


%start S

%%

S :
        tMAIN tPARO tPARF tACCO BODY tACCF
;

BODY :
        LINE tENDL BODY |
;

LINE :
        ASSIGN
        | DECL
        | PRINT
;


PRINT :
        tPRINT tPARO tID tPARF
        {
            $$ = make_ast_print($3);
        }
;

DECL :
        DECLKW tID tEGAL EXPR
            {
                $$ = make_ast_decl($2,$1,$4);
            }
;

DECLKW :
        tINT
            {
                $$ = INT;
            }
        | tCONST
            {
                $$ = CONST;
            }
;

ASSIGN :
        tID tEGAL EXPR
            {
                $$ = make_ast_assign($1,$3);
            }
;

EXPR :
        tLITT
            {$$ = make_ast_expr($1,LIT);}
        | tID
            {$$ = make_ast_expr($1,ID);}
        | tLITTEXP
            {$$ = make_ast_expr($1,LIT);}
        | tPARO EXPR tPARF
            {$$ = make_ast_expr($2,EXPR);}
        | EXPR OP EXPR
            {$$ = make_ast_expr(make_ast_op($1,$2,$3),OP);}
;

OP :
        tMOINS
            {$$ = SUB;}
        | tPLUS
            {$$ = ADD;}
        | tMUL
            {$$ = MUL;}
        | tDIV
            {$$ = DIV;}
;

