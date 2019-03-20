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
    type_t type;
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
            {$$ = ast_make_instr_assign($1,NULL);}
        | DECL
            {$$ = ast_make_instr_decl($1,NULL);}
        | PRINT
            {$$ = ast_make_instr_print($1,NULL);}
;


PRINT :
        tPRINT tPARO tID tPARF
        {
            $$ = ast_make_print($3);
        }
;

DECL :
        DECLKW tID tEGAL EXPR
            {
                $$ = ast_make_decl($2,$1,$4);
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
                $$ = ast_make_assign($1,$3);
            }
;

EXPR :
        tLITT
            {$$ = ast_make_expr_lit($1);}
        | tID
            {$$ = ast_make_expr_id($1);}
        | tLITTEXP
            {$$ = ast_make_expr_lit($1);}
        | tPARO EXPR tPARF
            {$$ = ast_make_expr_expr($2);}
        | EXPR OP EXPR
            {$$ = ast_make_expr_op(ast_make_op($1,$2,$3));}
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

