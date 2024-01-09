/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 48 "lang.y"

  #include "include.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  static struct row_entry* cons(const char* name, struct row_entry* first_child) {
    struct row_entry* answer = malloc(sizeof(struct row_entry));
    answer->name = strdup(name);
    answer->first_child = first_child;
    answer->next_sibling = NULL;
    return answer;
  }

  static void display(struct row_entry* node, int count_tabs) {
    if(node == NULL) return;
    for(int i = 0; i < count_tabs; i++) {
      printf("\t");
    }
    printf("%s\n", node->name);
    display(node->first_child, count_tabs + 1);
    display(node->next_sibling, count_tabs);
  }
  static void free_row_entry(struct row_entry* node) {
    if(node == NULL) return;
    free_row_entry(node->first_child);
    free_row_entry(node->next_sibling);
    free(node->name);
    free(node);
  }
  extern int yylex();
  extern int yylex_destroy();

#line 105 "lang.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "lang.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NOT = 3,                        /* NOT  */
  YYSYMBOL_PLUS = 4,                       /* PLUS  */
  YYSYMBOL_MINUS = 5,                      /* MINUS  */
  YYSYMBOL_MULT = 6,                       /* MULT  */
  YYSYMBOL_DIV = 7,                        /* DIV  */
  YYSYMBOL_MOD = 8,                        /* MOD  */
  YYSYMBOL_EQUAL = 9,                      /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 10,                 /* NOT_EQUAL  */
  YYSYMBOL_LT = 11,                        /* LT  */
  YYSYMBOL_LE = 12,                        /* LE  */
  YYSYMBOL_GT = 13,                        /* GT  */
  YYSYMBOL_GE = 14,                        /* GE  */
  YYSYMBOL_ASSIGNMENT = 15,                /* ASSIGNMENT  */
  YYSYMBOL_AND = 16,                       /* AND  */
  YYSYMBOL_OR = 17,                        /* OR  */
  YYSYMBOL_L_BRACKET = 18,                 /* L_BRACKET  */
  YYSYMBOL_R_BRACKET = 19,                 /* R_BRACKET  */
  YYSYMBOL_L_SQUARE_BRACKET = 20,          /* L_SQUARE_BRACKET  */
  YYSYMBOL_R_SQUARE_BRACKET = 21,          /* R_SQUARE_BRACKET  */
  YYSYMBOL_L_PARANTHESIS = 22,             /* L_PARANTHESIS  */
  YYSYMBOL_R_PARANTHESIS = 23,             /* R_PARANTHESIS  */
  YYSYMBOL_SEMICOLON = 24,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_APOSTROPHE = 26,                /* APOSTROPHE  */
  YYSYMBOL_COLON = 27,                     /* COLON  */
  YYSYMBOL_PERIOD = 28,                    /* PERIOD  */
  YYSYMBOL_LET = 29,                       /* LET  */
  YYSYMBOL_IF = 30,                        /* IF  */
  YYSYMBOL_ELSE = 31,                      /* ELSE  */
  YYSYMBOL_WHILE = 32,                     /* WHILE  */
  YYSYMBOL_PRINT = 33,                     /* PRINT  */
  YYSYMBOL_READ_I32 = 34,                  /* READ_I32  */
  YYSYMBOL_READ_U32 = 35,                  /* READ_U32  */
  YYSYMBOL_READ_STR = 36,                  /* READ_STR  */
  YYSYMBOL_READ_BOOL = 37,                 /* READ_BOOL  */
  YYSYMBOL_READ_F32 = 38,                  /* READ_F32  */
  YYSYMBOL_I32 = 39,                       /* I32  */
  YYSYMBOL_U32 = 40,                       /* U32  */
  YYSYMBOL_STR = 41,                       /* STR  */
  YYSYMBOL_BOOL = 42,                      /* BOOL  */
  YYSYMBOL_F32 = 43,                       /* F32  */
  YYSYMBOL_ARRAY = 44,                     /* ARRAY  */
  YYSYMBOL_TRUE = 45,                      /* TRUE  */
  YYSYMBOL_FALSE = 46,                     /* FALSE  */
  YYSYMBOL_IDENTIFIER = 47,                /* IDENTIFIER  */
  YYSYMBOL_CONSTANT = 48,                  /* CONSTANT  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_accept = 50,                    /* accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_statement = 52,                 /* statement  */
  YYSYMBOL_type = 53,                      /* type  */
  YYSYMBOL_decl_statement = 54,            /* decl_statement  */
  YYSYMBOL_assignment_statement = 55,      /* assignment_statement  */
  YYSYMBOL_input = 56,                     /* input  */
  YYSYMBOL_output = 57,                    /* output  */
  YYSYMBOL_output_expression = 58,         /* output_expression  */
  YYSYMBOL_conditional = 59,               /* conditional  */
  YYSYMBOL_loop = 60,                      /* loop  */
  YYSYMBOL_operator = 61,                  /* operator  */
  YYSYMBOL_expression = 62,                /* expression  */
  YYSYMBOL_term = 63                       /* term  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   119

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  98

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   101,   101,   102,   103,   106,   107,   108,   109,   110,
     111,   112,   115,   116,   117,   118,   119,   120,   124,   127,
     129,   130,   131,   132,   133,   136,   139,   140,   143,   144,
     147,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   166,   167,   168,   169,   172,
     173,   174,   175,   176
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NOT", "PLUS", "MINUS",
  "MULT", "DIV", "MOD", "EQUAL", "NOT_EQUAL", "LT", "LE", "GT", "GE",
  "ASSIGNMENT", "AND", "OR", "L_BRACKET", "R_BRACKET", "L_SQUARE_BRACKET",
  "R_SQUARE_BRACKET", "L_PARANTHESIS", "R_PARANTHESIS", "SEMICOLON",
  "COMMA", "APOSTROPHE", "COLON", "PERIOD", "LET", "IF", "ELSE", "WHILE",
  "PRINT", "READ_I32", "READ_U32", "READ_STR", "READ_BOOL", "READ_F32",
  "I32", "U32", "STR", "BOOL", "F32", "ARRAY", "TRUE", "FALSE",
  "IDENTIFIER", "CONSTANT", "$accept", "accept", "program", "statement",
  "type", "decl_statement", "assignment_statement", "input", "output",
  "output_expression", "conditional", "loop", "operator", "expression",
  "term", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -42,     3,    57,   -42,   -42,   -41,    13,    13,   -14,    -6,
     -42,   -10,    -5,    -1,     6,   -42,   -42,   -17,    13,    13,
      13,   -42,   -42,   -42,   -42,     9,   102,    14,    13,     2,
     -42,   -42,   -42,   -42,    54,   -42,   -42,     8,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,    13,   -42,   -21,   -42,    11,    12,    19,
      20,    22,   -42,   -42,   -42,   -42,   -42,   -42,    25,   -42,
     -42,    -4,   -42,    33,   -42,    13,    28,    30,    31,    32,
      44,    54,    39,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
      47,    55,    13,   -42,    51,    45,   -42,   -42
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     5,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,    10,    11,     0,     0,     0,
       0,    51,    52,    49,    50,     0,    47,     0,     0,     0,
       6,     7,     8,     9,     0,    45,    48,     0,     3,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,     0,     3,     0,    26,     0,     0,     0,
       0,     0,    19,    12,    13,    14,    15,    16,     0,    18,
      53,     0,    46,     0,    25,     0,     0,     0,     0,     0,
       0,     0,    28,    30,    27,    20,    21,    22,    23,    24,
       0,     0,     0,     3,     0,     0,    17,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -37,   -42,    -2,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,    -7,   -42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    10,    69,    11,    12,    13,    14,    55,
      15,    16,    53,    25,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      27,    71,    74,     3,    75,    18,    17,    19,    28,    29,
      34,    35,    36,    37,    30,    82,    18,    73,    19,    31,
       4,    56,    62,    32,    20,     5,     6,    38,     7,     8,
      33,    70,    54,    76,    77,    20,    57,    58,    59,    60,
      61,    78,    79,     9,    80,    81,    72,    21,    22,    23,
      24,    85,    83,    86,    87,    88,    95,     4,    21,    22,
      23,    24,     5,     6,    97,     7,     8,    89,    84,     4,
      91,    92,    96,    93,     5,     6,     0,     7,     8,    90,
       9,     4,     0,     0,     0,    94,     5,     6,     0,     7,
       8,     0,     9,    63,    64,    65,    66,    67,    68,     0,
       0,     0,     0,     0,     9,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,     0,    51,    52
};

static const yytype_int8 yycheck[] =
{
       7,    38,    23,     0,    25,     3,    47,     5,    22,    15,
      27,    18,    19,    20,    24,    19,     3,    54,     5,    24,
      24,    28,    29,    24,    22,    29,    30,    18,    32,    33,
      24,    23,    18,    22,    22,    22,    34,    35,    36,    37,
      38,    22,    22,    47,    22,    20,    53,    45,    46,    47,
      48,    23,    19,    23,    23,    23,    93,    24,    45,    46,
      47,    48,    29,    30,    19,    32,    33,    23,    75,    24,
      31,    24,    21,    18,    29,    30,    -1,    32,    33,    81,
      47,    24,    -1,    -1,    -1,    92,    29,    30,    -1,    32,
      33,    -1,    47,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    47,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    16,    17
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,    24,    29,    30,    32,    33,    47,
      52,    54,    55,    56,    57,    59,    60,    47,     3,     5,
      22,    45,    46,    47,    48,    62,    63,    62,    22,    15,
      24,    24,    24,    24,    27,    62,    62,    62,    18,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    16,    17,    61,    18,    58,    62,    34,    35,    36,
      37,    38,    62,    39,    40,    41,    42,    43,    44,    53,
      23,    51,    62,    51,    23,    25,    22,    22,    22,    22,
      22,    20,    19,    19,    62,    23,    23,    23,    23,    23,
      53,    31,    24,    18,    62,    51,    21,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    53,    53,    53,    53,    53,    53,    54,    55,
      56,    56,    56,    56,    56,    57,    58,    58,    59,    59,
      60,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    62,    62,    63,
      63,    63,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     6,     4,     3,
       5,     5,     5,     5,     5,     4,     1,     3,     5,     9,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     1,     2,     1,
       1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* accept: program  */
#line 101 "lang.y"
                                                  { display((yyvsp[0].row), 0); free_row_entry((yyvsp[0].row)); }
#line 1221 "lang.tab.c"
    break;

  case 3: /* program: %empty  */
#line 102 "lang.y"
                                                  { (yyval.row) = cons("program", NULL); }
#line 1227 "lang.tab.c"
    break;

  case 4: /* program: program statement  */
#line 103 "lang.y"
                                                  { (yyval.row) = cons("program", (yyvsp[-1].row)); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1233 "lang.tab.c"
    break;

  case 5: /* statement: SEMICOLON  */
#line 106 "lang.y"
                                                  { (yyval.row) = cons("statement", (yyvsp[0].row)); }
#line 1239 "lang.tab.c"
    break;

  case 6: /* statement: decl_statement SEMICOLON  */
#line 107 "lang.y"
                                                  { (yyval.row) = cons("statement", (yyvsp[-1].row)); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1245 "lang.tab.c"
    break;

  case 7: /* statement: assignment_statement SEMICOLON  */
#line 108 "lang.y"
                                                  { (yyval.row) = cons("statement", (yyvsp[-1].row)); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1251 "lang.tab.c"
    break;

  case 8: /* statement: input SEMICOLON  */
#line 109 "lang.y"
                                                  { (yyval.row) = cons("statement", (yyvsp[-1].row)); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1257 "lang.tab.c"
    break;

  case 9: /* statement: output SEMICOLON  */
#line 110 "lang.y"
                                                  { (yyval.row) = cons("statement", (yyvsp[-1].row)); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1263 "lang.tab.c"
    break;

  case 10: /* statement: conditional  */
#line 111 "lang.y"
                                                  { (yyval.row) = cons("statement", (yyvsp[0].row)); }
#line 1269 "lang.tab.c"
    break;

  case 11: /* statement: loop  */
#line 112 "lang.y"
                                                  { (yyval.row) = cons("statement", (yyvsp[0].row)); }
#line 1275 "lang.tab.c"
    break;

  case 12: /* type: I32  */
#line 115 "lang.y"
                                                  { (yyval.row) = cons("type", (yyvsp[0].row)); }
#line 1281 "lang.tab.c"
    break;

  case 13: /* type: U32  */
#line 116 "lang.y"
                                                  { (yyval.row) = cons("type", (yyvsp[0].row)); }
#line 1287 "lang.tab.c"
    break;

  case 14: /* type: STR  */
#line 117 "lang.y"
                                                  { (yyval.row) = cons("type", (yyvsp[0].row)); }
#line 1293 "lang.tab.c"
    break;

  case 15: /* type: BOOL  */
#line 118 "lang.y"
                                                  { (yyval.row) = cons("type", (yyvsp[0].row)); }
#line 1299 "lang.tab.c"
    break;

  case 16: /* type: F32  */
#line 119 "lang.y"
                                                  { (yyval.row) = cons("type", (yyvsp[0].row)); }
#line 1305 "lang.tab.c"
    break;

  case 17: /* type: ARRAY L_SQUARE_BRACKET type SEMICOLON expression R_SQUARE_BRACKET  */
#line 120 "lang.y"
                                                                        { (yyval.row) = cons("type", (yyvsp[-5].row)); (yyvsp[-5].row)->next_sibling = (yyvsp[-4].row); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1311 "lang.tab.c"
    break;

  case 18: /* decl_statement: LET IDENTIFIER COLON type  */
#line 124 "lang.y"
                                                        { (yyval.row) = cons("decl_statement", (yyvsp[-3].row)); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1317 "lang.tab.c"
    break;

  case 19: /* assignment_statement: IDENTIFIER ASSIGNMENT expression  */
#line 127 "lang.y"
                                                        { (yyval.row) = cons("assignment_statement", (yyvsp[-2].row)); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1323 "lang.tab.c"
    break;

  case 20: /* input: IDENTIFIER ASSIGNMENT READ_I32 L_PARANTHESIS R_PARANTHESIS  */
#line 129 "lang.y"
                                                                              { (yyval.row) = cons("input", (yyvsp[-4].row)); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1329 "lang.tab.c"
    break;

  case 21: /* input: IDENTIFIER ASSIGNMENT READ_U32 L_PARANTHESIS R_PARANTHESIS  */
#line 130 "lang.y"
                                                                              { (yyval.row) = cons("input", (yyvsp[-4].row)); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1335 "lang.tab.c"
    break;

  case 22: /* input: IDENTIFIER ASSIGNMENT READ_STR L_PARANTHESIS R_PARANTHESIS  */
#line 131 "lang.y"
                                                                              { (yyval.row) = cons("input", (yyvsp[-4].row)); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1341 "lang.tab.c"
    break;

  case 23: /* input: IDENTIFIER ASSIGNMENT READ_BOOL L_PARANTHESIS R_PARANTHESIS  */
#line 132 "lang.y"
                                                                              { (yyval.row) = cons("input", (yyvsp[-4].row)); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1347 "lang.tab.c"
    break;

  case 24: /* input: IDENTIFIER ASSIGNMENT READ_F32 L_PARANTHESIS R_PARANTHESIS  */
#line 133 "lang.y"
                                                                              { (yyval.row) = cons("input", (yyvsp[-4].row)); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1353 "lang.tab.c"
    break;

  case 25: /* output: PRINT L_PARANTHESIS output_expression R_PARANTHESIS  */
#line 136 "lang.y"
                                                              { (yyval.row) = cons("output", (yyvsp[-3].row)); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1359 "lang.tab.c"
    break;

  case 26: /* output_expression: expression  */
#line 139 "lang.y"
                                                              { (yyval.row) = cons("output_expression", (yyvsp[0].row)); }
#line 1365 "lang.tab.c"
    break;

  case 27: /* output_expression: output_expression COMMA expression  */
#line 140 "lang.y"
                                                              { (yyval.row) = cons("output_expression", (yyvsp[-2].row)); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1371 "lang.tab.c"
    break;

  case 28: /* conditional: IF expression L_BRACKET program R_BRACKET  */
#line 143 "lang.y"
                                                              { (yyval.row) = cons("conditional", (yyvsp[-4].row)); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1377 "lang.tab.c"
    break;

  case 29: /* conditional: IF expression L_BRACKET program R_BRACKET ELSE L_BRACKET program R_BRACKET  */
#line 144 "lang.y"
                                                                                        { (yyval.row) = cons("conditional", (yyvsp[-8].row)); (yyvsp[-8].row)->next_sibling = (yyvsp[-7].row); (yyvsp[-7].row)->next_sibling = (yyvsp[-6].row); (yyvsp[-6].row)->next_sibling = (yyvsp[-5].row); (yyvsp[-5].row)->next_sibling = (yyvsp[-4].row); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1383 "lang.tab.c"
    break;

  case 30: /* loop: WHILE expression L_BRACKET program R_BRACKET  */
#line 147 "lang.y"
                                                    { (yyval.row) = cons("loop", (yyvsp[-4].row)); (yyvsp[-4].row)->next_sibling = (yyvsp[-3].row); (yyvsp[-3].row)->next_sibling = (yyvsp[-2].row); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1389 "lang.tab.c"
    break;

  case 31: /* operator: NOT  */
#line 150 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1395 "lang.tab.c"
    break;

  case 32: /* operator: PLUS  */
#line 151 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1401 "lang.tab.c"
    break;

  case 33: /* operator: MINUS  */
#line 152 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1407 "lang.tab.c"
    break;

  case 34: /* operator: MULT  */
#line 153 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1413 "lang.tab.c"
    break;

  case 35: /* operator: DIV  */
#line 154 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1419 "lang.tab.c"
    break;

  case 36: /* operator: MOD  */
#line 155 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1425 "lang.tab.c"
    break;

  case 37: /* operator: EQUAL  */
#line 156 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1431 "lang.tab.c"
    break;

  case 38: /* operator: NOT_EQUAL  */
#line 157 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1437 "lang.tab.c"
    break;

  case 39: /* operator: LT  */
#line 158 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1443 "lang.tab.c"
    break;

  case 40: /* operator: LE  */
#line 159 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1449 "lang.tab.c"
    break;

  case 41: /* operator: GT  */
#line 160 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1455 "lang.tab.c"
    break;

  case 42: /* operator: GE  */
#line 161 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1461 "lang.tab.c"
    break;

  case 43: /* operator: AND  */
#line 162 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1467 "lang.tab.c"
    break;

  case 44: /* operator: OR  */
#line 163 "lang.y"
                            { (yyval.row) = cons("operator", (yyvsp[0].row)); }
#line 1473 "lang.tab.c"
    break;

  case 45: /* expression: NOT expression  */
#line 166 "lang.y"
                                          { (yyval.row) = cons("expression", (yyvsp[-1].row)); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1479 "lang.tab.c"
    break;

  case 46: /* expression: term operator expression  */
#line 167 "lang.y"
                                          { (yyval.row) = cons("expression", (yyvsp[-2].row)); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row);}
#line 1485 "lang.tab.c"
    break;

  case 47: /* expression: term  */
#line 168 "lang.y"
                                          { (yyval.row) = cons("expression", (yyvsp[0].row)); }
#line 1491 "lang.tab.c"
    break;

  case 48: /* expression: MINUS expression  */
#line 169 "lang.y"
                                          { (yyval.row) = cons("expression", (yyvsp[-1].row)); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1497 "lang.tab.c"
    break;

  case 49: /* term: IDENTIFIER  */
#line 172 "lang.y"
                                                    { (yyval.row) = cons("term", (yyvsp[0].row)); }
#line 1503 "lang.tab.c"
    break;

  case 50: /* term: CONSTANT  */
#line 173 "lang.y"
                                                    { (yyval.row) = cons("term", (yyvsp[0].row)); }
#line 1509 "lang.tab.c"
    break;

  case 51: /* term: TRUE  */
#line 174 "lang.y"
                                                    { (yyval.row) = cons("term", (yyvsp[0].row)); }
#line 1515 "lang.tab.c"
    break;

  case 52: /* term: FALSE  */
#line 175 "lang.y"
                                                    { (yyval.row) = cons("term", (yyvsp[0].row)); }
#line 1521 "lang.tab.c"
    break;

  case 53: /* term: L_PARANTHESIS expression R_PARANTHESIS  */
#line 176 "lang.y"
                                                    { (yyval.row) = cons("term", (yyvsp[-2].row)); (yyvsp[-2].row)->next_sibling = (yyvsp[-1].row); (yyvsp[-1].row)->next_sibling = (yyvsp[0].row); }
#line 1527 "lang.tab.c"
    break;


#line 1531 "lang.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 178 "lang.y"


int yyerror(char *s) {
  fprintf(stderr, "Error: %s\n", s); 
  return 0; 
}

int main() {
  yyparse();
  yylex_destroy();
  return 0;
}
