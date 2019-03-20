/* A Bison parser, made by GNU Bison 3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_HOME_PAUL_REPOS_AUL_CMAKE_BUILD_DEBUG_SRC_SYNTAX_H_INCLUDED
# define YY_YY_HOME_PAUL_REPOS_AUL_CMAKE_BUILD_DEBUG_SRC_SYNTAX_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 6 "/home/paul/repos/aul/cmake-build-debug/../src/syntax.y" /* yacc.c:1906  */
#include "ast.h"

#line 50 "/home/paul/repos/aul/cmake-build-debug/../src/syntax.h" /* yacc.c:1906  */

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
#line 9 "/home/paul/repos/aul/cmake-build-debug/../src/syntax.y" /* yacc.c:1906  */

    int intValue;
    id* idValue;
    ast_expr* ast_expr;
    ast_print* ast_print;
    ast_decl* ast_decl;
    ast_assign* ast_assign;
    ast_instr* ast_instr;
    type_t type;
    ast_body* ast_body;

#line 95 "/home/paul/repos/aul/cmake-build-debug/../src/syntax.h" /* yacc.c:1906  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_PAUL_REPOS_AUL_CMAKE_BUILD_DEBUG_SRC_SYNTAX_H_INCLUDED  */