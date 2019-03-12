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
    ast_instr* ast_instr;
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
%type <ast_instr> LINE

%start S

%%

S :
        tMAIN tPARO tPARF tACCO BODY tACCF
;

BODY : INSTRS;

INSTRS :
        LINE tENDL INSTRS
            {}|
;

LINE :
        ASSIGN
            {$$ = make_ast_instr_assign($1);}
        | DECL
            {$$ = make_ast_instr_decl($1);}
        | PRINT
            {$$ = make_ast_instr_print($1);}
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
            {$$ = make_ast_expr_lit($1);}
        | tID
            {$$ = make_ast_expr_id($1);}
        | tLITTEXP
            {$$ = make_ast_expr_lit($1);}
        | tPARO EXPR tPARF
            {$$ = make_ast_expr_expr($2);}
        | EXPR OP EXPR
            {$$ = make_ast_expr_op(make_ast_op($1,$2,$3));}
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

