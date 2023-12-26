
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
#line 1 "src/lib/parser/parser.y"

  #include "src/lib/ast.h"



/* Line 1676 of yacc.c  */
#line 46 "parser.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MATCH_KEYWORD = 258,
     WHERE_KEYWORD = 259,
     RETURN_KEYWORD = 260,
     CREATE_KEYWORD = 261,
     DELETE_KEYWORD = 262,
     SET_KEYWORD = 263,
     AND_KEYWORD = 264,
     OR_KEYWORD = 265,
     NOT_KEYWORD = 266,
     GREATER_CMP = 267,
     GREATER_OR_EQUAL_CMP = 268,
     LESS_CMP = 269,
     LESS_OR_EQUAL_CMP = 270,
     EQUAL_CMP = 271,
     CONTAINS_OP = 272,
     ASSIGNMENT = 273,
     DASH = 274,
     RIGHT_ARROW = 275,
     LEFT_ARROW = 276,
     DOUBLE_DASH = 277,
     COLON = 278,
     SCOLON = 279,
     PERIOD = 280,
     COMMA = 281,
     LPAR = 282,
     RPAR = 283,
     LBRACKET = 284,
     RBRACKET = 285,
     LBRACE = 286,
     RBRACE = 287,
     END_OF_FILE = 288,
     STRING_LITERAL = 289,
     INT_LITERAL = 290,
     FLOAT_LITERAL = 291,
     BOOL_LITERAL = 292,
     NAME = 293
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 22 "src/lib/parser/parser.y"

    INode                    *iNode;
    RequestNode              *requestNode;
    ExpressionNode           *expressionNode;
    MatchExpressionNode      *matchExpressionNode;
    CreateExpressionNode     *createExpressionNode;
    SetExpressionNode        *setExpressionNode;
    ReturnExpressionNode     *returnExpressionNode;
    DeleteExpressionNode     *deleteExpressionNode;
    VariableMatchNode        *variableMatchNode;
    RelationMatchNode        *relationMatchNode;
    ValueNode                *value;
    FilterNode               *filterNode;
    PredicateNode            *predicateNode;
    LogicalExpressionNode    *logicalExpressionNode;
    AttributeListNode        *attributeListNode;
    char                     *name;
    char                     *string;
    int                      integer;
    float                    real;
    bool                     boolean;



/* Line 1676 of yacc.c  */
#line 126 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


