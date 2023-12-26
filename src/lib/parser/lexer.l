%option yylineno
%option noyywrap nounput batch

%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "D:/VT-3-year/low-level/llp2/ast.h"
    #include "parser.tab.h"
    #define YY_NO_UNPUT 1

    extern FILE* yyin;

    void init_flex(FILE* infile) {
      yyrestart(infile);
    }
%}


WS        [ \t\n]+
NAME      [A-Za-z][A-Za-z0-9_]*
INTEGER   -?[1-9][0-9]*
FLOAT     -?[0-9]+\.[0-9]+
STRING    \"[^"]*\"
COMMENT \/\/.*\n


%%
"MATCH"|"match"        {return MATCH_KEYWORD       ;}
"WHERE"|"where"        {return WHERE_KEYWORD       ;}
"RETURN"|"return"      {return RETURN_KEYWORD      ;}
"CREATE"|"create"      {return CREATE_KEYWORD      ;}
"DELETE"|"delete"      {return DELETE_KEYWORD      ;}
"SET"|"set"            {return SET_KEYWORD         ;}
"AND"|"and"            {return AND_KEYWORD         ;}
"OR"|"or"              {return OR_KEYWORD          ;}
"NOT"|"not"            {return NOT_KEYWORD         ;}
">"                    {return GREATER_CMP         ;}
">="                   {return GREATER_OR_EQUAL_CMP;}
"<"                    {return LESS_CMP            ;}
"<="                   {return LESS_OR_EQUAL_CMP   ;}
"=="                   {return EQUAL_CMP           ;}
"contains"             {return CONTAINS_OP         ;}
"="                    {return ASSIGNMENT          ;}
"-"                    {return DASH                ;}
"--"                   {return DOUBLE_DASH         ;}
"->"                   {return RIGHT_ARROW         ;}
"<-"                   {return LEFT_ARROW          ;}
":"                    {return COLON               ;}
";"                    {return SCOLON              ;}
"."                    {return PERIOD              ;}
","                    {return COMMA               ;}
"("                    {return LPAR                ;}
")"                    {return RPAR                ;}
"["                    {return LBRACKET            ;}
"]"                    {return RBRACKET            ;}
"{"                    {return LBRACE              ;}
"}"                    {return RBRACE              ;}
"true"|"false"         {return BOOL_LITERAL        ;}
{INTEGER}              {yylval.integer = atoi(yytext); return INT_LITERAL         ;}
{FLOAT}                {yylval.real = atof(yytext);    return FLOAT_LITERAL       ;}
{STRING}               {yylval.string = strdup(yytext);        return STRING_LITERAL      ;}
{NAME}                 {yylval.string = strdup(yytext);        return NAME                ;}
<<EOF>>                {return END_OF_FILE         ;}
{COMMENT}              // dp nothing
{WS}                   // do nothing

. {
    return (int) yytext[0];
}

%%

