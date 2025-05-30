
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
     IF = 271,
     ELSE = 272,
     WHILE = 273,
     FOR = 274,
     DO = 275,
     TO = 276,
     INC = 277,
     DEC = 278,
     ASSIGN = 279,
     ADD_ASSIGN = 280,
     SUB_ASSIGN = 281,
     MUL_ASSIGN = 282,
     DIV_ASSIGN = 283,
     MOD_ASSIGN = 284,
     PLUS = 285,
     MINUS = 286,
     MULTIPLY = 287,
     DIVIDE = 288,
     MODULO = 289,
     LT = 290,
     GT = 291,
     LE = 292,
     GE = 293,
     NE = 294,
     LPAREN = 295,
     RPAREN = 296,
     LBRACE = 297,
     RBRACE = 298,
     LBRACKET = 299,
     RBRACKET = 300,
     INT_CONST = 301,
     CHAR_CONST = 302,
     STRING_CONST = 303,
     STRING_FORMAT = 304,
     INPUT_FORMAT = 305,
     BASE_INT = 306,
     IDENTIFIER = 307,
     ERROR = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 208 "parser.y"

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
        
        // Additional fields for for-loop
        char *loop_var;    // Loop variable
        char *upper;       // Upper bound
        char *step;        // Step value
        char *loop_start;  // Loop start label
        char *loop_end;    // Loop end label
    } attr;



/* Line 1676 of yacc.c  */
#line 130 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


