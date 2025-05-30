
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BEGIN_PROGRAM = 258,
     END_PROGRAM = 259,
     BEGIN_VARDECL = 260,
     END_VARDECL = 261,
     BEGIN_K = 262,
     END_K = 263,
     INT_TYPE = 264,
     CHAR_TYPE = 265,
     COLON = 266,
     SEMICOLON = 267,
     COMMA = 268,
     PRINT = 269,
     SCAN = 270,
     STRING_FORMAT = 271,
     INPUT_FORMAT = 272,
     IF = 273,
     ELSE = 274,
     WHILE = 275,
     FOR = 276,
     DO = 277,
     TO = 278,
     INC = 279,
     DEC = 280,
     ASSIGN = 281,
     ADD_ASSIGN = 282,
     SUB_ASSIGN = 283,
     MUL_ASSIGN = 284,
     DIV_ASSIGN = 285,
     MOD_ASSIGN = 286,
     PLUS = 287,
     MINUS = 288,
     MULTIPLY = 289,
     DIVIDE = 290,
     MODULO = 291,
     LT = 292,
     GT = 293,
     LE = 294,
     GE = 295,
     NE = 296,
     LPAREN = 297,
     RPAREN = 298,
     LBRACE = 299,
     RBRACE = 300,
     LBRACKET = 301,
     RBRACKET = 302,
     INT_CONST = 303,
     CHAR_CONST = 304,
     STRING_CONST = 305,
     BASE_INT = 306,
     IDENTIFIER = 307,
     ERROR = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


