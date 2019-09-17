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

#ifndef YY_YY_2_TAB_H_INCLUDED
# define YY_YY_2_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LITERAL = 258,
    SEMICOLON = 259,
    COMMA = 260,
    COLON = 261,
    ASSIGN = 262,
    LT = 263,
    GT = 264,
    LTE = 265,
    GTE = 266,
    EQUAL = 267,
    NOTEQUAL = 268,
    ADD = 269,
    MULTIPLY = 270,
    SUBTRACT = 271,
    DIVIDE = 272,
    COMP_AND = 273,
    COMP_DAND = 274,
    VOID = 275,
    COMP_OR = 276,
    COMP_DOR = 277,
    LP = 278,
    RP = 279,
    LC = 280,
    RC = 281,
    LSB = 282,
    RSB = 283,
    CHAR = 284,
    INT = 285,
    UINT = 286,
    SIGNED = 287,
    UNSIGNED = 288,
    SHORT = 289,
    LONG = 290,
    FLOAT = 291,
    DOUBLE = 292,
    REGISTER = 293,
    CONST = 294,
    IF = 295,
    ELSE = 296,
    FOR = 297,
    WHILE = 298,
    DO = 299,
    SWITCH = 300,
    CASE = 301,
    DEFAULT = 302,
    BREAK = 303,
    CONTINUE = 304,
    ENUM = 305,
    TYPEDEF = 306,
    EXTERN = 307,
    RETURN = 308,
    UNION = 309,
    GOTO = 310,
    ID = 311,
    NUM = 312,
    MOD = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_2_TAB_H_INCLUDED  */
