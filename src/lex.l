%{
#include "syntax.h"
%}

%%
"main" {return tMAIN;}
"print" {return tPRINT;}
"const" {return tCONST;}
"int" {return tINT;}
"{" {return tACCO;}
"}" {return tACCF;}
"(" {return tPARO;}
")" {return tPARF;}
[A-Za-z]([A-Za-z0-9]|"_")*  {return tID;}
"+" {return tPLUS;}
"-" {return tMOINS;}
"*" {return tMUL;}
"/" {return tDIV;}
"=" {return tEGAL;}
";" {return tENDL;}
[ \t\n]+ {}
"," {return tSEP;}
[0-9]+ {return tLITT;}
[0-9]+."^".[0-9]+ {return tLITTEXP;}

%%