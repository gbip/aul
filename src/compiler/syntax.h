/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_HOME_JULIEN_PROJET_INFO_AUL_SRC_COMPILER_SYNTAX_H_INCLUDED
# define YY_YY_HOME_JULIEN_PROJET_INFO_AUL_SRC_COMPILER_SYNTAX_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 6 "/home/julien/projet_info/aul/src/compiler/syntax.y" /* yacc.c:1909  */
#include "co_ast.h"

#line 47 "/home/julien/projet_info/aul/src/compiler/syntax.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tMAIN = 258,
    tPRINT = 259,
    tACCO = 260,
    tACCF = 261,
    tPARO = 262,
    tMOINS = 263,
    tPARF = 264,
    tSEP = 265,
    tPLUS = 266,
    tDIV = 267,
    tMUL = 268,
    tINT = 269,
    tCONST = 270,
    tEGAL = 271,
    tENDL = 272,
    tLITT = 273,
    tLITTEXP = 274,
    tID = 275
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 9 "/home/julien/projet_info/aul/src/compiler/syntax.y" /* yacc.c:1909  */

    int intValue;
    id* idValue;
    ast_expr* ast_expr;
    ast_print* ast_print;
    ast_decl* ast_decl;
    ast_assign* ast_assign;
    ast_instr* ast_instr;
    co_type_t type;
    ast_body* ast_body;

#line 92 "/home/julien/projet_info/aul/src/compiler/syntax.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_JULIEN_PROJET_INFO_AUL_SRC_COMPILER_SYNTAX_H_INCLUDED  */
