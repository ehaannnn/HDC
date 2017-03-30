/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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
     PLUSASSIGN = 258,
     MINUSASSIGN = 259,
     DIVASSIGN = 260,
     REMASSIGN = 261,
     ASSIGN = 262,
     MULASSIGN = 263,
     SHIFTL = 264,
     SHIFTR = 265,
     LESS = 266,
     GRET = 267,
     LESSEQ = 268,
     GRETEQ = 269,
     EQUAL = 270,
     NEQUAL = 271,
     AND = 272,
     OR = 273,
     NUM = 274,
     INC = 275,
     DEC = 276,
     ID = 277,
     INT = 278,
     CHAR = 279,
     VOID = 280,
     VECTOR = 281,
     BYTE = 282,
     IF = 283,
     ELSE = 284,
     MAIN = 285,
     FOR = 286,
     IN = 287,
     WHILE = 288,
     PRINTI = 289,
     PRINTC = 290,
     INPUTI = 291,
     INPUTC = 292,
     RETURN = 293,
     UMINUS = 294
   };
#endif
/* Tokens.  */
#define PLUSASSIGN 258
#define MINUSASSIGN 259
#define DIVASSIGN 260
#define REMASSIGN 261
#define ASSIGN 262
#define MULASSIGN 263
#define SHIFTL 264
#define SHIFTR 265
#define LESS 266
#define GRET 267
#define LESSEQ 268
#define GRETEQ 269
#define EQUAL 270
#define NEQUAL 271
#define AND 272
#define OR 273
#define NUM 274
#define INC 275
#define DEC 276
#define ID 277
#define INT 278
#define CHAR 279
#define VOID 280
#define VECTOR 281
#define BYTE 282
#define IF 283
#define ELSE 284
#define MAIN 285
#define FOR 286
#define IN 287
#define WHILE 288
#define PRINTI 289
#define PRINTC 290
#define INPUTI 291
#define INPUTC 292
#define RETURN 293
#define UMINUS 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 10 "hdc.y"

  char* sval;
  int ival;
  Program *pval;



/* Line 1685 of yacc.c  */
#line 137 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


