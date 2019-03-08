%{
#include "syntax.h"
%}

%%
"main" {printf("tMAIN\n");return tMAIN;}
"print" {printf("tPRINT\n");return tPRINT;}
"const" {printf("tCONST\n");}
"int" {printf("tINT\n");}
"{" {printf("tACCO\n");}
"}" {printf("tACCF\n");}
"(" {printf("tPARO\n");}
")" {printf("tPARF\n");}
[A-Za-z]([A-Za-z0-9]|"_")*  {printf("tID\n");}
"+" {printf("tPLUS\n");}
"-" {printf("tMOINS\n");}
"*" {printf("tMUL\n");}
"/" {printf("tDIV\n");}
"=" {printf("tEGAL\n");}
";" {printf("tENDI\n");}
[ \t\n]+ {printf(".");}
"," {printf("tSEP\n");}
[0-9]+ {printf("tLITT\n");}
[0-9]+."^".[0-9]+ {printf("tLITTEXP");}

%%