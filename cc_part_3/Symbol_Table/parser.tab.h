
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 708 "parser.y"

    #include "ast.h"



/* Line 1676 of yacc.c  */
#line 46 "parser.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     STRING_CONST = 259,
     STRING_FORMAT = 260,
     INPUT_FORMAT = 261,
     CHAR_CONST = 262,
     BASE_INT = 263,
     INT_CONST = 264,
     BEGIN_PROGRAM = 265,
     END_PROGRAM = 266,
     BEGIN_VARDECL = 267,
     END_VARDECL = 268,
     BEGIN_K = 269,
     END_K = 270,
     INT_TYPE = 271,
     CHAR_TYPE = 272,
     COLON = 273,
     SEMICOLON = 274,
     COMMA = 275,
     PRINT = 276,
     SCAN = 277,
     IF = 278,
     ELSE = 279,
     WHILE = 280,
     FOR = 281,
     DO = 282,
     TO = 283,
     INC = 284,
     DEC = 285,
     ASSIGN = 286,
     ADD_ASSIGN = 287,
     SUB_ASSIGN = 288,
     MUL_ASSIGN = 289,
     DIV_ASSIGN = 290,
     MOD_ASSIGN = 291,
     PLUS = 292,
     MINUS = 293,
     MULTIPLY = 294,
     DIVIDE = 295,
     MODULO = 296,
     LT = 297,
     GT = 298,
     LE = 299,
     GE = 300,
     NE = 301,
     LPAREN = 302,
     RPAREN = 303,
     LBRACE = 304,
     RBRACE = 305,
     LBRACKET = 306,
     RBRACKET = 307,
     ERROR = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 712 "parser.y"

    char *id;
    int num;
    char chr;
    char *str;
    
    // For 3AC code generation
    struct {
        char place[20];    // Place to store the result
        char *true_label;  // For boolean expressions
        char *false_label; // For boolean expressions
        char *next_label;  // For control flow
        int quad_index;    // Index in quad array
        ASTNode *node;     // AST node pointer
    } attr;

    // For AST nodes
    ASTNode *node;



/* Line 1676 of yacc.c  */
#line 138 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


