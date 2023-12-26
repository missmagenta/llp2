%code requires {
  #include "D:/VT-3-year/low-level/llp2/ast.h"
}

%{
    #include <stdio.h>
    #include <stdbool.h>
    #include <math.h>
    #include <string.h>
    #include "parser.tab.h"
    #include "D:/VT-3-year/low-level/llp2/ast.h"
    #include "src/lib/printer.h"

    extern void yyerror(const char *s);
    extern int yylex(void);

    extern FILE *yyin;

%}

%union
{
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
}

%token
    MATCH_KEYWORD
    WHERE_KEYWORD
    RETURN_KEYWORD
    CREATE_KEYWORD
    DELETE_KEYWORD
    SET_KEYWORD
    AND_KEYWORD
    OR_KEYWORD
    NOT_KEYWORD
    GREATER_CMP
    GREATER_OR_EQUAL_CMP
    LESS_CMP
    LESS_OR_EQUAL_CMP
    EQUAL_CMP
    CONTAINS_OP
    ASSIGNMENT
    DASH
    RIGHT_ARROW
    LEFT_ARROW
    DOUBLE_DASH
    COLON
    SCOLON
    PERIOD
    COMMA
    LPAR
    RPAR
    LBRACKET
    RBRACKET
    LBRACE
    RBRACE
    END_OF_FILE
;

%token <string>     STRING_LITERAL
%token <integer>    INT_LITERAL
%token <real>       FLOAT_LITERAL
%token <boolean>    BOOL_LITERAL
%token <name>       NAME

%nterm <requestNode>              REQUEST
%nterm <requestNode>              REQUEST_B
%nterm <matchExpressionNode>      MATCH_EXPRESSION
%nterm <variableMatchNode>        VARIABLE_MATCH
%nterm <relationMatchNode>        ANY_RELATION_MATCH
%nterm <relationMatchNode>        RELATION_MATCH
%nterm <returnExpressionNode>     RETURN_EXPRESSION
%nterm <value>                    VALUE
%nterm <createExpressionNode>     CREATE_EXPRESSION
%nterm <setExpressionNode>        SET_EXPRESSION
%nterm <deleteExpressionNode>     DELETE_EXPRESSION
%nterm <filterNode>               FILTER
%nterm <predicateNode>            PREDICATE
%nterm <logicalExpressionNode>    LOGICAL_EXPRESSION
%nterm <attributeListNode>        ATTRIBUTE_LIST

%left OR_KEYWORD
%left AND_KEYWORD
%left NOT_KEYWORD

%start REQUEST

%%
REQUEST: REQUEST_B SCOLON              { insert($1); return 0; }
       | REQUEST_B END_OF_FILE         { insert($1); return 0; }
;


REQUEST_B: MATCH_EXPRESSION            { $$ = RequestNode_new((ExpressionNode*)$1); }
         | CREATE_EXPRESSION           { $$ = RequestNode_new((ExpressionNode*)$1); }
         | REQUEST_B MATCH_EXPRESSION  { $$ = $1; RequestNode_addExpr($$, (ExpressionNode*)$2); }
         | REQUEST_B SET_EXPRESSION    { $$ = $1; RequestNode_addExpr($$, (ExpressionNode*)$2); }
         | REQUEST_B CREATE_EXPRESSION { $$ = $1; RequestNode_addExpr($$, (ExpressionNode*)$2); }
         | REQUEST_B DELETE_EXPRESSION { $$ = $1; RequestNode_addExpr($$, (ExpressionNode*)$2); }
         | REQUEST_B RETURN_EXPRESSION { $$ = $1; RequestNode_addExpr($$, (ExpressionNode*)$2); }
;

MATCH_EXPRESSION: MATCH_KEYWORD VARIABLE_MATCH                                       { $$ = MatchExpressionNode_new($2);         }
                | MATCH_KEYWORD VARIABLE_MATCH RELATION_MATCH VARIABLE_MATCH         { $$ = MatchExpressionNode_new3($2, $4, $3); }
                | MATCH_KEYWORD VARIABLE_MATCH ANY_RELATION_MATCH VARIABLE_MATCH     { $$ = MatchExpressionNode_new2($2, $4); }
;

VARIABLE_MATCH: LPAR NAME COLON NAME PREDICATE RPAR                    { $$ = (VariableMatchNode *)VariableFilterMatchNode_new($2, $4, $5);  }
              | LPAR NAME COLON NAME LBRACE ATTRIBUTE_LIST RBRACE RPAR { $$ = (VariableMatchNode *)VariablePatternMatchNode_new($2, $4, $6); }
              | LPAR NAME COLON NAME RPAR                              { $$ = VariableMatchNode_new($2, $4); }
              | LPAR NAME RPAR                                         { $$ = VariableMatchNode_new($2, ""); }
;

RELATION_MATCH: DASH LBRACKET NAME COLON NAME RBRACKET RIGHT_ARROW { $$ = RelationMatchNode_new($3, $5, FORWARD); }
              | LEFT_ARROW LBRACKET NAME COLON NAME RBRACKET DASH  { $$ = RelationMatchNode_new($3, $5, REVERSE); }
;

ANY_RELATION_MATCH: DOUBLE_DASH { $$ = RelationMatchNode_new("", "", ANY); }
;

PREDICATE: WHERE_KEYWORD LOGICAL_EXPRESSION { $$ = PredicateNode_new($2); }
;

LOGICAL_EXPRESSION: LOGICAL_EXPRESSION AND_KEYWORD LOGICAL_EXPRESSION { $$ = (LogicalExpressionNode *)AndOperationNode_new($1, $3); }
                  | LOGICAL_EXPRESSION OR_KEYWORD LOGICAL_EXPRESSION  { $$ = (LogicalExpressionNode *)OrOperationNode_new($1, $3);  }
                  | NOT_KEYWORD LOGICAL_EXPRESSION                    { $$ = (LogicalExpressionNode *)NotOperationNode_new($2);     }
                  | FILTER                                            { $$ = (LogicalExpressionNode *)FilterByPassNode_new($1);     }
;

FILTER: VALUE LESS_CMP VALUE             { $$ = FilterNode_new($1, $3, LESS);             }
      | VALUE LESS_OR_EQUAL_CMP VALUE    { $$ = FilterNode_new($1, $3, LESS_OR_EQUAL);    }
      | VALUE GREATER_CMP VALUE          { $$ = FilterNode_new($1, $3, GREATER);          }
      | VALUE GREATER_OR_EQUAL_CMP VALUE { $$ = FilterNode_new($1, $3, GREATER_OR_EQUAL); }
      | VALUE EQUAL_CMP VALUE            { $$ = FilterNode_new($1, $3, EQUAL);            }
      | VALUE CONTAINS_OP VALUE          { $$ = FilterNode_new($1, $3, CONTAINS);         }
;

SET_EXPRESSION: SET_KEYWORD NAME PERIOD NAME ASSIGNMENT VALUE { $$ = SetExpressionNode_new(VariableValueNode_new($2, $4), $6); }
;

DELETE_EXPRESSION: DELETE_KEYWORD NAME { $$ = DeleteExpressionNode_new($2); }
;

RETURN_EXPRESSION: RETURN_EXPRESSION COMMA VALUE { $$ = $1; ReturnExpressionNode_addElement($$, $3);                         }
                 | RETURN_KEYWORD VALUE          { $$ = ReturnExpressionNode_new(); ReturnExpressionNode_addElement($$, $2); }

ATTRIBUTE_LIST: NAME COLON VALUE COMMA ATTRIBUTE_LIST { $$ = $5; AttributeListNode_addAttribute($$, $1, $3);                      }
              | NAME COLON VALUE                      { $$ = AttributeListNode_new(); AttributeListNode_addAttribute($$, $1, $3); }
;

CREATE_EXPRESSION: CREATE_KEYWORD VARIABLE_MATCH { $$ = CreateExpressionNode_new($2); }
                 | CREATE_KEYWORD VARIABLE_MATCH RELATION_MATCH VARIABLE_MATCH { $$ = CreateExpressionNode_new2($2, $4, $3); }
;

VALUE: NAME             { $$ = (ValueNode *)VariableValueNode_new($1, ""); }
     | BOOL_LITERAL     { $$ = (ValueNode *)BoolLiteralNode_new($1);       }
     | INT_LITERAL      { $$ = (ValueNode *)IntLiteralNode_new($1);        }
     | FLOAT_LITERAL    { $$ = (ValueNode *)FloatLiteralNode_new($1);      }
     | STRING_LITERAL   { $$ = (ValueNode *)StringLiteralNode_new($1);     }
     | NAME PERIOD NAME { $$ = (ValueNode *)VariableValueNode_new($1, $3); }
;
%%


void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}

int main(int argc, char *argv[]) {
  --argc;
  ++argv;
  if (argc == 0) {
    printf("Usage: ./parser <file.graphql>\n");
    return 1;
  }

  FILE *file = fopen(argv[0], "r");
  if (file == NULL) {
    printf("Unable to open file: %s\n", argv[0]);
    return 1;
  }
  yyin = file;
  if (yyparse()) {
    printf("Parsing failed\n");
  }
  else {
    printf("No syntax errors\n");
  }
}

