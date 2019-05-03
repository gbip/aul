%{
    #include "../co_ast.h"
    #include <stdlib.h>
%}

%code requires {#include "../co_ast.h"}

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
%token tIF
%token tELSE
%token tDIFF
%token tSUP
%token tINF
%token tSUPEQ
%token tINFEQ
%token tEQUALITY
%token tNOT
%token tWHILE
%token tAND
%token tOR
%token tFOR

%token <intValue> tLITT
%token <intValue> tLITTEXP
%token <idValue> tID

%type <ast_expr> EXPR
%type <type> DECLKW
%type <ast_print> PRINT
%type <ast_decl> DECL
%type <ast_assign> ASSIGN
%type <ast_instr> INIT LINE
%type <ast_body> INSTRS MAIN BODY S GLOBAL_VARS

%left tPLUS tMOINS
%right tDIV tMUL

%start S

%%

S : MAIN
	{set_global_var_ast(NULL); set_ast($1);}
    | GLOBAL_VARS MAIN
        {set_global_var_ast($1); set_ast($2);}
;

GLOBAL_VARS : DECL tENDL
	{$$ = ast_make_body_instr(ast_make_instr_decl($1), NULL);}
	| DECL tENDL GLOBAL_VARS
	{$$ = ast_make_body_instr(ast_make_instr_decl($1),$3);}

MAIN :
        tMAIN tPARO tPARF tACCO BODY tACCF
            {$$ = $5;}
;

BODY :
        INSTRS
            {$$=$1;}
;

INSTRS :
	tIF tPARO EXPR tPARF tACCO INSTRS tACCF INSTRS
	    {$$ = ast_make_body_if(ast_make_if($3,$6,NULL),$8);}
	|
	tIF tPARO EXPR tPARF tACCO INSTRS tACCF tELSE tACCO INSTRS tACCF INSTRS
	    {$$ = ast_make_body_if(ast_make_if($3,$6,$10),$12);}
	|
        tWHILE tPARO EXPR tPARF tACCO INSTRS tACCF INSTRS
            {$$ = ast_make_body_while(ast_make_while($3,$6),$8);}
	|
	tFOR tPARO INIT tENDL EXPR tENDL ASSIGN tPARF tACCO INSTRS tACCF INSTRS
	    {$$ = ast_make_body_for(ast_make_for(ast_make_body_instr($3, NULL), $5, ast_make_body_instr(ast_make_instr_assign($7), NULL), $10),$12);}
	|
        LINE tENDL INSTRS
            {$$ = ast_make_body_instr($1,$3);}
        |
            {$$ = NULL;}
;


INIT :
	 ASSIGN
            {$$ = ast_make_instr_assign($1);}
        | DECL
            {$$ = ast_make_instr_decl($1);}
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
        | EXPR tDIV EXPR
            {$$ = ast_make_expr_op(ast_make_op($1,OP_DIV,$3));}
        | EXPR tMUL EXPR
             {$$ = ast_make_expr_op(ast_make_op($1,OP_MUL,$3));}
        | EXPR tPLUS EXPR
            {$$ = ast_make_expr_op(ast_make_op($1,OP_ADD,$3));}
        | EXPR tMOINS EXPR
            {$$ = ast_make_expr_op(ast_make_op($1,OP_SUB,$3));}
        | EXPR tDIFF EXPR
       	    {$$ = ast_make_expr_op(ast_make_op($1,OP_DIFF,$3));}
       	| EXPR tEQUALITY EXPR
       	    {$$ = ast_make_expr_op(ast_make_op($1,OP_EQUAL,$3));}
       	| EXPR tSUP EXPR
       	    {$$ = ast_make_expr_op(ast_make_op($1,OP_SUP,$3));}
       	| EXPR tINF EXPR
       	    {$$ = ast_make_expr_op(ast_make_op($1,OP_INF,$3));}
       	| EXPR tSUPEQ EXPR
       	    {$$ = ast_make_expr_op(ast_make_op($1,OP_SUPEQ,$3));}
       	| EXPR tINFEQ EXPR
       	    {$$ = ast_make_expr_op(ast_make_op($1,OP_INFEQ,$3));}
       	| tNOT tPARO EXPR tPARF
       	    {$$ = ast_make_expr_op(ast_make_op(NULL,OP_NOT,$3));}
       	| tMOINS EXPR
            {$$ = ast_make_expr_op(ast_make_op(NULL,OP_SUB,$2));}
        | EXPR tAND EXPR
             {$$ = ast_make_expr_op(ast_make_op($1,OP_AND,$3));}
        | EXPR tOR EXPR
             {$$ = ast_make_expr_op(ast_make_op($1,OP_OR,$3));}

;