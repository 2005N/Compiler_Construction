
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
extern FILE *yyin;
extern int no_of_placeholders;
extern int no_of_variables;
extern int no_of_commas;
extern int validvariables;

// Import the values from lexer
extern char* idVal;
extern int intVal;
extern char charVal;
extern char* strVal;
extern char* baseIntVal;
extern char* baseVal;  // Added to store the base value too

void yyerror(const char* s);

// 3AC Generation code
int qind = 0;
struct quadruple {
    char operator[10];
    char operand1[20];
    char operand2[20];
    char result[20];
    int is_label;     // Flag to indicate if this is a label
    int is_if;        // Flag to indicate if this is an if statement
    int is_goto;      // Flag to indicate if this is a goto statement
} quad[100];

void addQuadruple(char op1[], char op[], char op2[], char result[]) {
    if (qind >= 100) {
        fprintf(stderr, "Quadruple array overflow\n");
        return;
    }
    
    if (op) strcpy(quad[qind].operator, op);
    else quad[qind].operator[0] = '\0';
    
    if (op1) strcpy(quad[qind].operand1, op1);
    else quad[qind].operand1[0] = '\0';
    
    if (op2) strcpy(quad[qind].operand2, op2);
    else quad[qind].operand2[0] = '\0';
    
    if (result) strcpy(quad[qind].result, result);
    else quad[qind].result[0] = '\0';
    
    quad[qind].is_label = 0;
    quad[qind].is_if = 0;
    quad[qind].is_goto = 0;
    
    qind++;
}

// Add a label to the quadruple table
void addLabel(char *label) {
    strcpy(quad[qind].result, label);
    quad[qind].operator[0] = '\0';
    quad[qind].operand1[0] = '\0';
    quad[qind].operand2[0] = '\0';
    quad[qind].is_label = 1;
    quad[qind].is_if = 0;
    quad[qind].is_goto = 0;
    qind++;
}

// Add a goto statement to the quadruple table
void addGoto(char *label) {
    strcpy(quad[qind].result, "goto");
    strcpy(quad[qind].operand1, label);
    quad[qind].operator[0] = '\0';
    quad[qind].operand2[0] = '\0';
    quad[qind].is_label = 0;
    quad[qind].is_if = 0;
    quad[qind].is_goto = 1;
    qind++;
}

void addIf(char *cond, char *label) {
    strcpy(quad[qind].result, "if");
    strcpy(quad[qind].operand1, cond);
    strcpy(quad[qind].operator, "==");
    strcpy(quad[qind].operand2, "0");
    quad[qind].is_label = 0;
    quad[qind].is_if = 1;
    quad[qind].is_goto = 0;
    
    qind++;
    
    // Add the goto part
    strcpy(quad[qind].result, "goto");
    strcpy(quad[qind].operand1, label);
    quad[qind].operator[0] = '\0';
    quad[qind].operand2[0] = '\0';
    quad[qind].is_label = 0;
    quad[qind].is_if = 0;
    quad[qind].is_goto = 1;
    
    qind++;
}

void display_Quad() {
    if (qind <= 0) {
        printf("Error: No quadruple to display\n");
        return;
    }
    
    int idx = qind - 1;
    
    if (quad[idx].is_label) {
        printf("%s:\n", quad[idx].result);
    } else if (quad[idx].is_if) {
        printf("if %s %s %s goto %s\n", 
               quad[idx].operand1, 
               quad[idx].operator, 
               quad[idx].operand2, 
               quad[idx+1].operand1);
    } else if (quad[idx].is_goto) {
        printf("goto %s\n", quad[idx].operand1);
    } else {
        // Normal quadruple with assignment
        if (quad[idx].operator[0]) {
            printf("%s := %s %s %s\n", 
                  quad[idx].result, 
                  quad[idx].operand1, 
                  quad[idx].operator, 
                  quad[idx].operand2);
        } else if (quad[idx].operand1[0]) { // Check if operand1 exists
            printf("%s := %s\n", 
                  quad[idx].result, 
                  quad[idx].operand1);
        }
    }
}

// Function to print entire quad table with proper formatting
void print_Quad_Table() {
    printf("\n..............3AC Code.............\n");
    for (int i = 0; i < qind; i++) {
        if (quad[i].is_label) {
            printf("%s:\n", quad[i].result);
        } else if (quad[i].is_if) {
            printf("if %s %s %s goto %s\n", 
                   quad[i].operand1, 
                   quad[i].operator, 
                   quad[i].operand2, 
                   quad[i+1].operand1);
            i++; // Skip the goto part since we've included it
        } else if (quad[i].is_goto) {
            printf("goto %s\n", quad[i].operand1);
        } else {
            // Normal quadruple with assignment
            if (quad[i].operator[0]) {
                printf("%s := %s %s %s\n", 
                      quad[i].result, 
                      quad[i].operand1, 
                      quad[i].operator, 
                      quad[i].operand2);
            } else if (quad[i].operand1[0]) { // Check if operand1 exists
                printf("%s := %s\n", 
                      quad[i].result, 
                      quad[i].operand1);
            }
        }
    }
}
int temp_count = 1;
// Function to generate temporary variable names
char* newTemp() {
    char *temp = malloc(10); // Dynamically allocate
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

// For handling labels in control structures
int label_count = 1;
char* newLabel() {
    char *label = malloc(10); // Dynamically allocate
    sprintf(label, "L%d", label_count++);
    return label;
}

// Stack implementation for expression handling
int tos = -1;
struct stack {
    char c[20];
} stk[100];

void push(char *c) {
    strcpy(stk[++tos].c, c);
}

char* pop() {
    if (tos < 0) {
        fprintf(stderr, "Stack underflow error\n");
        // Return a safe default value instead of crashing
        return "";
    }
    return stk[tos--].c;
}



/* Line 189 of yacc.c  */
#line 281 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 395 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 407 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   206

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  167

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    12,    13,    16,    23,    33,    35,
      37,    38,    43,    46,    49,    52,    55,    58,    61,    64,
      67,    70,    73,    77,    81,    85,    89,    93,    97,   104,
     109,   115,   120,   126,   129,   133,   138,   144,   149,   155,
     158,   162,   163,   164,   174,   175,   182,   183,   184,   193,
     194,   195,   207,   208,   209,   221,   224,   227,   231,   233,
     235,   237,   239,   241,   243,   247,   251,   253,   257,   261,
     265,   267,   272,   274,   276,   278,   282
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,     3,    56,    60,     4,    -1,     5,    57,
       6,    -1,    -1,    58,    57,    -1,    40,    52,    13,    59,
      41,    12,    -1,    40,    52,    44,    46,    45,    13,    59,
      41,    12,    -1,     9,    -1,    10,    -1,    -1,     7,    61,
      60,     8,    -1,    61,    60,    -1,    62,    12,    -1,    63,
      12,    -1,    65,    12,    -1,    67,    12,    -1,    71,    12,
      -1,    74,    12,    -1,    80,    12,    -1,    79,    12,    -1,
       1,    12,    -1,    52,    24,    83,    -1,    52,    25,    83,
      -1,    52,    26,    83,    -1,    52,    27,    83,    -1,    52,
      28,    83,    -1,    52,    29,    83,    -1,    52,    44,    83,
      45,    24,    83,    -1,    14,    40,    48,    41,    -1,    14,
      40,    48,    64,    41,    -1,    14,    40,    49,    41,    -1,
      14,    40,    49,    64,    41,    -1,    13,    52,    -1,    13,
      52,    64,    -1,    15,    40,    48,    41,    -1,    15,    40,
      48,    66,    41,    -1,    15,    40,    50,    41,    -1,    15,
      40,    50,    66,    41,    -1,    13,    52,    -1,    13,    52,
      66,    -1,    -1,    -1,    16,    40,    81,    41,    68,    60,
      69,    17,    60,    -1,    -1,    16,    40,    81,    41,    70,
      60,    -1,    -1,    -1,    18,    72,    40,    81,    41,    20,
      73,    60,    -1,    -1,    -1,    19,    52,    24,    83,    75,
      21,    83,    76,    80,    20,    60,    -1,    -1,    -1,    19,
      52,    24,    83,    77,    21,    83,    78,    79,    20,    60,
      -1,    23,    83,    -1,    22,    83,    -1,    83,    82,    83,
      -1,    35,    -1,    36,    -1,    37,    -1,    38,    -1,    39,
      -1,    84,    -1,    83,    30,    84,    -1,    83,    31,    84,
      -1,    85,    -1,    84,    32,    85,    -1,    84,    33,    85,
      -1,    84,    34,    85,    -1,    52,    -1,    52,    44,    83,
      45,    -1,    46,    -1,    47,    -1,    48,    -1,    40,    83,
      41,    -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   255,   255,   258,   261,   262,   265,   266,   275,   276,
     279,   280,   281,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   295,   300,   307,   314,   321,   328,   335,   344,
     350,   360,   370,   386,   392,   400,   406,   416,   426,   443,
     449,   458,   471,   457,   484,   483,   502,   515,   501,   532,
     549,   531,   575,   592,   574,   621,   631,   643,   652,   653,
     654,   655,   656,   659,   663,   669,   677,   681,   687,   693,
     701,   705,   715,   721,   727,   733,   737
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BEGIN_PROGRAM", "END_PROGRAM",
  "BEGIN_VARDECL", "END_VARDECL", "BEGIN_K", "END_K", "INT_TYPE",
  "CHAR_TYPE", "COLON", "SEMICOLON", "COMMA", "PRINT", "SCAN", "IF",
  "ELSE", "WHILE", "FOR", "DO", "TO", "INC", "DEC", "ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "MODULO", "LT", "GT", "LE", "GE", "NE", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "INT_CONST",
  "CHAR_CONST", "STRING_CONST", "STRING_FORMAT", "INPUT_FORMAT",
  "BASE_INT", "IDENTIFIER", "ERROR", "$accept", "program",
  "vardecl_section", "var_declarations", "var_declaration", "type",
  "statements", "statement", "assignment", "print_statement", "print_vars",
  "scan_statement", "scan_vars", "if_statement", "@1", "$@2", "@3",
  "while_statement", "@4", "$@5", "for_statement", "@6", "@7", "@8", "@9",
  "dec_statement", "inc_statement", "condition", "relational_op",
  "expression", "term", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    57,    57,    58,    58,    59,    59,
      60,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    62,    62,    62,    62,    62,    63,
      63,    63,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    68,    69,    67,    70,    67,    72,    73,    71,    75,
      76,    74,    77,    78,    74,    79,    80,    81,    82,    82,
      82,    82,    82,    83,    83,    83,    84,    84,    84,    84,
      85,    85,    85,    85,    85,    85,    85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     0,     2,     6,     9,     1,     1,
       0,     4,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     6,     4,
       5,     4,     5,     2,     3,     4,     5,     4,     5,     2,
       3,     0,     0,     9,     0,     6,     0,     0,     8,     0,
       0,    11,     0,     0,    11,     2,     2,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     3,     3,
       1,     4,     1,     1,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,     0,     0,     4,     0,
       0,     0,     0,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     5,    21,     0,     0,     0,     0,     0,     0,     0,
      72,    73,    74,    76,    70,    56,    63,    66,    55,     0,
       0,     0,     0,     0,     0,     0,     2,    12,    13,    14,
      15,    16,    17,    18,    20,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    22,    23,    24,    25,    26,    27,
       0,     8,     9,     0,     0,    11,     0,    29,     0,    31,
       0,     0,    35,     0,    37,     0,    41,    58,    59,    60,
      61,    62,     0,     0,    49,    75,     0,    64,    65,    67,
      68,    69,     0,     0,     0,    33,    30,    32,    39,    36,
      38,     0,     0,    57,     0,     0,     0,    71,     0,     6,
       0,    34,    40,    42,    45,    47,     0,     0,    28,     0,
       0,     0,    50,    53,     0,     0,    48,     0,     0,     7,
      43,     0,     0,     0,     0,    51,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     4,     7,     8,    93,    19,    20,    21,    22,
      98,    23,   103,    24,   131,   150,   132,    25,    37,   151,
      26,   135,   157,   136,   158,    27,    28,    73,   112,    74,
      46,    47
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
      25,     2,    63,     9,    51,   -72,    27,    66,     9,    75,
      28,    57,    62,    64,   -72,    65,    90,    90,    81,    71,
       4,   106,   107,   108,   109,   111,   114,   115,   116,     1,
     -72,   -72,   -72,    70,   -18,   -33,    90,    89,   121,    90,
     -72,   -72,   -72,   -72,    95,    69,    49,   -72,    69,    90,
      90,    90,    90,    90,    90,    90,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   104,   100,   146,    -7,
      19,    20,    35,   117,   142,    90,    90,    60,    90,    90,
      90,    90,    90,    90,    69,    69,    69,    69,    69,    69,
     -21,   -72,   -72,   119,   112,   -72,   110,   -72,   120,   -72,
     122,   113,   -72,   128,   -72,   135,   170,   -72,   -72,   -72,
     -72,   -72,    90,   143,    69,   -72,    23,    49,    49,   -72,
     -72,   -72,   159,   174,   175,   176,   -72,   -72,   177,   -72,
     -72,   133,   152,    69,   167,   171,   172,   -72,    90,   -72,
     104,   -72,   -72,   -72,   -72,   -72,    90,    90,    69,   150,
     178,   152,    69,    69,   182,   152,   -72,   179,   173,   -72,
     -72,   180,   183,   152,   152,   -72,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   189,   -72,    58,   -20,   192,   -72,   -72,
     -66,   -72,   -71,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,    41,    48,   131,   -72,   -14,
      36,    13
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -45
static const yytype_int16 yytable[] =
{
      57,   105,    45,    48,   100,     9,    96,     3,   -10,    79,
      80,    10,   -10,    68,    66,    71,   -10,    72,    11,    12,
      13,   -10,    14,    15,   122,    77,    16,    17,     1,     9,
      69,    70,    96,   101,    97,    84,    85,    86,    87,    88,
      89,    90,    11,    12,    13,    67,    14,    15,   101,     6,
      16,    17,     9,    79,    80,   -10,    18,   142,    10,   141,
      99,   102,   114,     5,   116,    11,    12,    13,   137,    14,
      15,     9,    30,    16,    17,    56,   104,    10,   -10,    29,
      18,    81,    82,    83,    11,    12,    13,    32,    14,    15,
      79,    80,    16,    17,   119,   120,   121,    34,   133,    79,
      80,   115,    35,    18,    36,    49,    50,    51,    52,    53,
      54,   143,   144,    91,    92,   117,   118,    38,    58,    59,
      60,    61,    18,    62,   148,    55,    63,    64,    65,    75,
      39,   156,   152,   153,     9,   160,    40,    41,    42,    78,
      10,    43,    44,   165,   166,    76,    94,    11,    12,    13,
     -10,    14,    15,     9,    95,    16,    17,   124,   106,    10,
     123,   126,   125,   127,   -10,   128,    11,    12,    13,   129,
      14,    15,    79,    80,    16,    17,   130,   107,   108,   109,
     110,   111,   -44,   138,   134,    18,   139,   145,   140,    96,
     101,   154,   146,   147,   159,   155,    17,    31,   149,   162,
     163,    16,    33,   164,    18,   161,   113
};

static const yytype_uint8 yycheck[] =
{
      20,    72,    16,    17,    70,     1,    13,     5,     4,    30,
      31,     7,     8,    33,    13,    48,    12,    50,    14,    15,
      16,    17,    18,    19,    45,    39,    22,    23,     3,     1,
      48,    49,    13,    13,    41,    49,    50,    51,    52,    53,
      54,    55,    14,    15,    16,    44,    18,    19,    13,    40,
      22,    23,     1,    30,    31,     4,    52,   128,     7,   125,
      41,    41,    76,     0,    78,    14,    15,    16,    45,    18,
      19,     1,     6,    22,    23,     4,    41,     7,     8,    52,
      52,    32,    33,    34,    14,    15,    16,    12,    18,    19,
      30,    31,    22,    23,    81,    82,    83,    40,   112,    30,
      31,    41,    40,    52,    40,    24,    25,    26,    27,    28,
      29,   131,   132,     9,    10,    79,    80,    52,    12,    12,
      12,    12,    52,    12,   138,    44,    12,    12,    12,    40,
      40,   151,   146,   147,     1,   155,    46,    47,    48,    44,
       7,    51,    52,   163,   164,    24,    46,    14,    15,    16,
      17,    18,    19,     1,     8,    22,    23,    45,    41,     7,
      41,    41,    52,    41,    12,    52,    14,    15,    16,    41,
      18,    19,    30,    31,    22,    23,    41,    35,    36,    37,
      38,    39,    12,    24,    41,    52,    12,    20,    13,    13,
      13,    41,    21,    21,    12,    17,    23,     8,   140,   158,
      20,    22,    10,    20,    52,   157,    75
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    55,     5,    56,     0,    40,    57,    58,     1,
       7,    14,    15,    16,    18,    19,    22,    23,    52,    60,
      61,    62,    63,    65,    67,    71,    74,    79,    80,    52,
       6,    57,    12,    61,    40,    40,    40,    72,    52,    40,
      46,    47,    48,    51,    52,    83,    84,    85,    83,    24,
      25,    26,    27,    28,    29,    44,     4,    60,    12,    12,
      12,    12,    12,    12,    12,    12,    13,    44,    60,    48,
      49,    48,    50,    81,    83,    40,    24,    83,    44,    30,
      31,    32,    33,    34,    83,    83,    83,    83,    83,    83,
      83,     9,    10,    59,    46,     8,    13,    41,    64,    41,
      64,    13,    41,    66,    41,    66,    41,    35,    36,    37,
      38,    39,    82,    81,    83,    41,    83,    84,    84,    85,
      85,    85,    45,    41,    45,    52,    41,    41,    52,    41,
      41,    68,    70,    83,    41,    75,    77,    45,    24,    12,
      13,    64,    66,    60,    60,    20,    21,    21,    83,    59,
      69,    73,    83,    83,    41,    17,    60,    76,    78,    12,
      60,    80,    79,    20,    20,    60,    60
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:

/* Line 1455 of yacc.c  */
#line 267 "parser.y"
    {
                      // Generate 3AC for array declaration
                      char size[10];
                      sprintf(size, "%d", (yyvsp[(4) - (9)].num));
                      addQuadruple("array", size, "", (yyvsp[(2) - (9)].id));
                  ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 292 "parser.y"
    { yyerrok; ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 296 "parser.y"
    {
               // Generate 3AC for simple assignment
               addQuadruple((yyvsp[(3) - (3)].attr).place, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {
               // Generate 3AC for += operator
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "+", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 308 "parser.y"
    {
               // Generate 3AC for -= operator
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "-", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 315 "parser.y"
    {
               // Generate 3AC for *= operator
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "*", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 322 "parser.y"
    {
               // Generate 3AC for /= operator
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "/", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    {
               // Generate 3AC for %= operator
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].id), "%", (yyvsp[(3) - (3)].attr).place, temp);
               addQuadruple(temp, "", "", (yyvsp[(1) - (3)].id));
           ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 336 "parser.y"
    {
               // Generate 3AC for array assignment
               char index_str[20];
               sprintf(index_str, "%s[%s]", (yyvsp[(1) - (6)].id), (yyvsp[(3) - (6)].attr).place);
               addQuadruple((yyvsp[(6) - (6)].attr).place, "", "", index_str);
           ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
    {
                    // Generate 3AC for print with string constant
                    addQuadruple("print", (yyvsp[(3) - (4)].str), "", "_");
                    (yyval.attr).place[0] = '\0'; // Initialize place
                ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 351 "parser.y"
    {
                    if (no_of_placeholders > 0) {
                        fprintf(stderr, "Error: String constant contains @ but placeholders not expected\n");
                        YYERROR;
                    }
                    // Generate 3AC for print with multiple variables
                    addQuadruple("print", (yyvsp[(3) - (5)].str), "", "_");
                    (yyval.attr).place[0] = '\0'; // Initialize place
                ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 361 "parser.y"
    {
                    if (no_of_placeholders > 0) {
                        fprintf(stderr, "Error: Format string contains @ but no variables provided\n");
                        YYERROR;
                    }
                    // Generate 3AC for print with format string
                    addQuadruple("printf", (yyvsp[(3) - (4)].str), "", "_");
                    (yyval.attr).place[0] = '\0'; // Initialize place
                ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 371 "parser.y"
    {
                    if (no_of_placeholders != no_of_variables || !validvariables) {
                        fprintf(stderr, "Error: Number of placeholders (%d) does not match number of variables (%d)\n", 
                                no_of_placeholders, no_of_variables);
                        YYERROR;
                    }
                    no_of_placeholders = 0;
                    no_of_variables = 0;
                    validvariables = 1;
                    // Generate 3AC for printf with variables
                    addQuadruple("printf", (yyvsp[(3) - (5)].str), "", "_");
                    (yyval.attr).place[0] = '\0'; // Initialize place
                ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 387 "parser.y"
    { 
               no_of_variables++; 
               // Generate 3AC for print variable
               addQuadruple("param", (yyvsp[(2) - (2)].id), "", "_");
           ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 393 "parser.y"
    { 
               no_of_variables++; 
               // Generate 3AC for print variable
               addQuadruple("param", (yyvsp[(2) - (3)].id), "", "_");
           ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 401 "parser.y"
    {
                   // Generate 3AC for scan
                   addQuadruple("scan", (yyvsp[(3) - (4)].str), "", "_");
                   (yyval.attr).place[0] = '\0'; // Initialize place
               ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 407 "parser.y"
    {
                   if (no_of_placeholders > 0) {
                       fprintf(stderr, "Error: String constant contains @ but placeholders not expected\n");
                       YYERROR;
                   }
                   // Generate 3AC for scan with multiple variables
                   addQuadruple("scan", (yyvsp[(3) - (5)].str), "", "_");
                   (yyval.attr).place[0] = '\0'; // Initialize place
               ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {
                   if (no_of_placeholders > 0) {
                       fprintf(stderr, "Error: Input format contains @ but no variables provided\n");
                       YYERROR;
                   }
                   // Generate 3AC for scan with format
                   addQuadruple("scanf", (yyvsp[(3) - (4)].str), "", "_");
                   (yyval.attr).place[0] = '\0'; // Initialize place
               ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 427 "parser.y"
    {
                   if (no_of_placeholders != no_of_variables || !validvariables || 
                       (no_of_commas != no_of_placeholders-1 && no_of_placeholders != 0)) {
                       fprintf(stderr, "Error: Invalid scan statement\n");
                       YYERROR;
                   }
                   no_of_placeholders = 0;
                   no_of_variables = 0;
                   no_of_commas = 0;
                   validvariables = 1;
                   // Generate 3AC for scanf with variables
                   addQuadruple("scanf", (yyvsp[(3) - (5)].str), "", "_");
                   (yyval.attr).place[0] = '\0'; // Initialize place
               ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 444 "parser.y"
    { 
              no_of_variables++; 
              // Generate 3AC for scan variable
              addQuadruple("read", "", "", (yyvsp[(2) - (2)].id));
          ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 450 "parser.y"
    { 
              no_of_variables++; 
              // Generate 3AC for scan variable
              addQuadruple("read", "", "", (yyvsp[(2) - (3)].id));
          ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 458 "parser.y"
    {
                 // Create labels before processing statements
                 char *else_label = newLabel();
                 char *end_label = newLabel();
                 
                 // If condition is false, jump to else_label
                 addIf((yyvsp[(3) - (4)].attr).place, else_label);
                 
                 // Save these labels for later use
                 (yyval.attr).true_label = strdup(else_label);
                 (yyval.attr).false_label = strdup(end_label);
             ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 471 "parser.y"
    {
                 // After if-body, jump to end
                 addGoto((yyvsp[(5) - (6)].attr).false_label);
                 
                 // Add the else label
                 addLabel((yyvsp[(5) - (6)].attr).true_label);
             ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 479 "parser.y"
    {
                 // Add the end label after both branches are processed
                 addLabel((yyvsp[(5) - (9)].attr).false_label);
             ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 484 "parser.y"
    {
                 // Create a single end label for the simple if
                 char *end_label = newLabel();
                 
                 // If condition is false, jump to end_label
                 addIf((yyvsp[(3) - (4)].attr).place, end_label);
                 
                 // Save this label for later use
                 (yyval.attr).next_label = strdup(end_label);
             ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 495 "parser.y"
    {
                 // Add the end label after if body
                 addLabel((yyvsp[(5) - (6)].attr).next_label);
             ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 502 "parser.y"
    {
                    // Create labels for the while loop
                    char *loop_start = newLabel();
                    char *loop_end = newLabel();
                    
                    // Add the loop start label BEFORE evaluating condition
                    addLabel(loop_start);
                    
                    // Save labels for later use
                    (yyval.attr).loop_start = strdup(loop_start);
                    (yyval.attr).loop_end = strdup(loop_end);
                ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 515 "parser.y"
    {
                    // If condition is false, goto loop_end
                    // This places the condition check BEFORE the loop body
                    addIf((yyvsp[(4) - (6)].attr).place, (yyvsp[(2) - (6)].attr).loop_end);
                ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 521 "parser.y"
    {
                    // Jump back to loop start for next iteration
                    addGoto((yyvsp[(2) - (8)].attr).loop_start);
                    
                    // Add the loop end label
                    addLabel((yyvsp[(2) - (8)].attr).loop_end);
                ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 532 "parser.y"
    {
                  // Initialize loop variable
                  addQuadruple((yyvsp[(4) - (4)].attr).place, "", "", (yyvsp[(2) - (4)].id));
                  
                  // Create labels
                  char *loop_start = newLabel();
                  char *loop_end = newLabel();
                  
                  // Add loop start label
                  addLabel(loop_start);
                  
                  // Save loop variable and labels
                  (yyval.attr).loop_var = strdup((yyvsp[(2) - (4)].id));
                  (yyval.attr).loop_start = strdup(loop_start);
                  (yyval.attr).loop_end = strdup(loop_end);
              ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 549 "parser.y"
    {
                  char *upper = newTemp();
                  addQuadruple((yyvsp[(7) - (7)].attr).place, "", "", upper);
                  (yyval.attr).upper = strdup(upper);
                  
                  // Generate condition - check if loop var <= upper bound (negated from > for addIf)
                  char *cond_temp = newTemp();
                  addQuadruple((yyvsp[(5) - (7)].attr).loop_var, "<=", (yyval.attr).upper, cond_temp);
                  
                  // Use the proper addIf function to create a combined if-goto
                  addIf(cond_temp, (yyvsp[(5) - (7)].attr).loop_end);
              ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 562 "parser.y"
    {
                  // Apply increment
                  char *temp = newTemp();
                  addQuadruple((yyvsp[(5) - (11)].attr).loop_var, "+", (yyvsp[(9) - (11)].attr).step, temp);
                  addQuadruple(temp, "", "", (yyvsp[(5) - (11)].attr).loop_var);
                  
                  // Loop back to start
                  addGoto((yyvsp[(5) - (11)].attr).loop_start);
                  
                  // Add end label
                  addLabel((yyvsp[(5) - (11)].attr).loop_end);
              ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 575 "parser.y"
    {
                  // Initialize loop variable
                  addQuadruple((yyvsp[(4) - (4)].attr).place, "", "", (yyvsp[(2) - (4)].id));
                  
                  // Create labels
                  char *loop_start = newLabel();
                  char *loop_end = newLabel();
                  
                  // Add loop start label
                  addLabel(loop_start);
                  
                  // Save loop variable and labels
                  (yyval.attr).loop_var = strdup((yyvsp[(2) - (4)].id));
                  (yyval.attr).loop_start = strdup(loop_start);
                  (yyval.attr).loop_end = strdup(loop_end);
              ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 592 "parser.y"
    {
                  // Store upper bound in a temp
                  char *upper = newTemp();
                  addQuadruple((yyvsp[(7) - (7)].attr).place, "", "", upper);
                  (yyval.attr).upper = strdup(upper);
                  
                  // Generate condition - check if loop var > upper bound
                  char *cond_temp = newTemp();
                  addQuadruple((yyvsp[(5) - (7)].attr).loop_var, ">", (yyval.attr).upper, cond_temp);
                  
                  // Exit loop if condition is true (loop var > upper bound)
                  addQuadruple(cond_temp, "==", "1", "if");
                  addGoto((yyvsp[(5) - (7)].attr).loop_end);
              ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 607 "parser.y"
    {
                  // Apply decrement
                  char *temp = newTemp();
                  addQuadruple((yyvsp[(5) - (11)].attr).loop_var, "-", (yyvsp[(9) - (11)].attr).place, temp);
                  addQuadruple(temp, "", "", (yyvsp[(5) - (11)].attr).loop_var);
                  
                  // Loop back to start
                  addGoto((yyvsp[(5) - (11)].attr).loop_start);
                  
                  // Add end label
                  addLabel((yyvsp[(5) - (11)].attr).loop_end);
              ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 622 "parser.y"
    {
                  // Store the decrement value in place
                  strcpy((yyval.attr).place, (yyvsp[(2) - (2)].attr).place);
                  
                  // Also store in step for for-loop
                  (yyval.attr).step = strdup((yyvsp[(2) - (2)].attr).place);
              ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 632 "parser.y"
    {
                  // Store the increment value in place
                  strcpy((yyval.attr).place, (yyvsp[(2) - (2)].attr).place);
                  
                  // Also store in step for for-loop
                  (yyval.attr).step = strdup((yyvsp[(2) - (2)].attr).place);
              ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 644 "parser.y"
    {
              // Generate 3AC for condition
              char *temp = newTemp();
              addQuadruple((yyvsp[(1) - (3)].attr).place, (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].attr).place, temp);
              strcpy((yyval.attr).place, temp);
          ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 652 "parser.y"
    { (yyval.id) = strdup("<"); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 653 "parser.y"
    { (yyval.id) = strdup(">"); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 654 "parser.y"
    { (yyval.id) = strdup("<="); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 655 "parser.y"
    { (yyval.id) = strdup(">="); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 656 "parser.y"
    { (yyval.id) = strdup("<>"); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 660 "parser.y"
    {
               strcpy((yyval.attr).place, (yyvsp[(1) - (1)].attr).place);
           ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 664 "parser.y"
    {
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].attr).place, "+", (yyvsp[(3) - (3)].attr).place, temp);
               strcpy((yyval.attr).place, temp);
           ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 670 "parser.y"
    {
               char *temp = newTemp();
               addQuadruple((yyvsp[(1) - (3)].attr).place, "-", (yyvsp[(3) - (3)].attr).place, temp);
               strcpy((yyval.attr).place, temp);
           ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 678 "parser.y"
    {
         strcpy((yyval.attr).place, (yyvsp[(1) - (1)].attr).place);
     ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 682 "parser.y"
    {
         char *temp = newTemp();
         addQuadruple((yyvsp[(1) - (3)].attr).place, "*", (yyvsp[(3) - (3)].attr).place, temp);
         strcpy((yyval.attr).place, temp);
     ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 688 "parser.y"
    {
         char *temp = newTemp();
         addQuadruple((yyvsp[(1) - (3)].attr).place, "/", (yyvsp[(3) - (3)].attr).place, temp);
         strcpy((yyval.attr).place, temp);
     ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 694 "parser.y"
    {
         char *temp = newTemp();
         addQuadruple((yyvsp[(1) - (3)].attr).place, "%", (yyvsp[(3) - (3)].attr).place, temp);
         strcpy((yyval.attr).place, temp);
     ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 702 "parser.y"
    {
           strcpy((yyval.attr).place, (yyvsp[(1) - (1)].id));
       ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 706 "parser.y"
    {
           char array_ref[20];
           sprintf(array_ref, "%s[%s]", (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].attr).place);
           
           char *temp = newTemp();
           addQuadruple(array_ref, "", "", temp);
           
           strcpy((yyval.attr).place, temp);
       ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 716 "parser.y"
    {
           char int_str[10];
           sprintf(int_str, "%d", (yyvsp[(1) - (1)].num));
           strcpy((yyval.attr).place, int_str);
       ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 722 "parser.y"
    {
           char char_str[5];
           sprintf(char_str, "'%c'", charVal);
           strcpy((yyval.attr).place, char_str);
       ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 728 "parser.y"
    {
           char *temp = newTemp();
           addQuadruple((yyvsp[(1) - (1)].str), "", "", temp);
           strcpy((yyval.attr).place, temp);
       ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 734 "parser.y"
    {
           strcpy((yyval.attr).place, (yyvsp[(2) - (3)].attr).place);
       ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 738 "parser.y"
    {
           strcpy((yyval.attr).place, baseIntVal);
       ;}
    break;



/* Line 1455 of yacc.c  */
#line 2471 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 743 "parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error opening file %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    yyparse();
    
    // Print the complete 3AC table
    print_Quad_Table();
    
    printf("\nOutput: Successfully parsed and generated 3AC code\n");
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return 0;
}
