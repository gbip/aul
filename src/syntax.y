%{
    #include "ast.h"
    #include <stdlib.h>

    ast_instr* ast;
%}

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
%token tLITT
%token tLITTEXP
%token tID

%start S

%%

S : tMAIN tPARO tPARF tACCO BODY tACCF ;

BODY : LINE tENDL BODY | ;

LINE : ASSIGN | DECL | PRINT ;

PRINT : tPRINT tPARO tID tPARF ;

DECL : DECLKW tID tEGAL EXPR ;

DECLKW :  tINT | tCONST ;

ASSIGN : tID tEGAL EXPR ;

EXPR : tLITT
    | tID
    | tLITTEXP
    | tPARO EXPR tPARF
    | EXPR OP EXPR

OP : tMOINS
| tPLUS
| tMUL
| tDIV