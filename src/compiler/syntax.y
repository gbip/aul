%{
    #include "co_ast.h"
    #include <stdlib.h>
%}

%code requires {#include "co_ast.h"}

%union
{
    int intValue;
    id* idValue;
    ast_expr* ast_expr;
    ast_print* ast_print;
    ast_decl* ast_decl;
    ast_assign* ast_assign;
    ast_instr* ast_instr;
    co_type_t type;
    ast_body* ast_body;
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
%type <type> DECLKW
%type <ast_print> PRINT
%type <ast_decl> DECL
%type <ast_assign> ASSIGN
%type <ast_instr> LINE
%type <ast_body> INSTRS MAIN BODY S

%left tPLUS tMOINS
%right tDIV tMUL

%start S

%%

S : MAIN
            {set_ast($1);}
;

MAIN :
        tMAIN tPARO tPARF tACCO BODY tACCF
            {$$ = $5;}
;

BODY :
        INSTRS
            {$$=$1;}
;

INSTRS :
        LINE tENDL INSTRS
            {$$ = ast_make_body($1,$3);}
        |
            {$$ = NULL;}
;

LINE :
        ASSIGN
            {$$ = ast_make_instr_assign($1);}
        | DECL
            {$$ = ast_make_instr_decl($1);}
        | PRINT
            {$$ = ast_make_instr_print($1);}
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
            {$$ = $2;}
        | EXPR tPLUS EXPR
            {$$ = ast_make_expr_op(ast_make_op($1,ADD,$3));}
        | EXPR tMOINS EXPR
            {$$ = ast_make_expr_op(ast_make_op($1,SUB,$3));}
        | EXPR tDIV EXPR
            {$$ = ast_make_expr_op(ast_make_op($1,DIV,$3));}
        | EXPR tMUL EXPR
            {$$ = ast_make_expr_op(ast_make_op($1,MUL,$3));}
;