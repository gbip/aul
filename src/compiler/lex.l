%{
#include "../co_ast.h"
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

"if" {return tIF;}

"else" {return tELSE;}

"while" {return tWHILE;}

[A-Za-z]([A-Za-z0-9]|"_")*  {
    yylval.idValue = ast_make_id(strdup(yytext));
    return tID;
}

"+" {return tPLUS;}

"-" {return tMOINS;}

"*" {return tMUL;}

"/" {return tDIV;}

"=" {return tEGAL;}

";" {return tENDL;}

"==" {return tEQUALITY;}

"<" {return tINF;}

"<=" {return tINFEQ;}

">" {return tSUP;}

">=" {return tSUPEQ;}

"!=" {return tDIFF;}

"!" {return tNOT;}

[ \t\n]+ {}

"," {return tSEP;}

[0-9]+ {
    yylval.intValue = atoi(yytext);
    return tLITT;
}

[0-9]+."^".[0-9]+ {return tLITTEXP;}

"//".*$ ;

%%