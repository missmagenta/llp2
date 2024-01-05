#ifndef LLP_AST_H
#define LLP_AST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    STRING_LITERAL_NODE,
    VARIABLE_VALUE_NODE,
    VARIABLE_FILTER_MATCH_NODE,
    RELATION_MATCH_NODE,
    BOOL_LITERAL_NODE,
    INT_LITERAL_NODE,
    FLOAT_LITERAL_NODE,
    FILTER_NODE,
    FILTER_BY_PASS_NODE,
    NOT_OPERATION_NODE,
    AND_OPERATION_NODE,
    OR_OPERATION_NODE,
    PREDICATE_NODE,
    ATTRIBUTE_LIST_NODE,
    RETURN_EXPRESSION_NODE,
    VARIABLE_PATTERN_MATCH_NODE,
    ANY_VARIABLE_MATCH_NODE,
    MATCH_EXPRESSION_NODE,
    SET_EXPRESSION_NODE,
    DELETE_EXPRESSION_NODE,
    CREATE_EXPRESSION_NODE,
    INODE,
    REQUEST_NODE
} NodeType;

typedef struct INode {
    NodeType nodeType;
} INode;

typedef struct ExpressionNode {
    INode base;
    NodeType nodeType;
} ExpressionNode;

typedef struct ValueNode {
    INode base;
    NodeType nodeType;
} ValueNode;

typedef struct VariableValueNode {
    ValueNode base;
    char* VariableName;
    char* FieldName;
    NodeType nodeType;
} VariableValueNode;

VariableValueNode* VariableValueNode_new(char* VName, char* FName);

typedef struct StringLiteralNode {
    ValueNode base;
    char* Value;
    NodeType nodeType;
} StringLiteralNode;

StringLiteralNode* StringLiteralNode_new(char* Val);

typedef struct BoolLiteralNode {
    ValueNode base;
    int Value;
    NodeType nodeType;
} BoolLiteralNode;

BoolLiteralNode* BoolLiteralNode_new(int Val);

typedef struct IntLiteralNode {
    ValueNode base;
    int Value;
    NodeType nodeType;
} IntLiteralNode;

IntLiteralNode* IntLiteralNode_new(int Value);

typedef struct FloatLiteralNode {
    ValueNode base;
    float Value;
    NodeType nodeType;
} FloatLiteralNode;

FloatLiteralNode* FloatLiteralNode_new(float Val);

typedef enum FilterCheckOperation {
    EQUAL,
    GREATER,
    GREATER_OR_EQUAL,
    LESS,
    LESS_OR_EQUAL,
    CONTAINS
} FilterCheckOperation;

typedef struct FilterNode {
    INode base;
    ValueNode* RHS;
    ValueNode* LHS;
    FilterCheckOperation Operation;
    NodeType nodeType;
} FilterNode;

FilterNode* FilterNode_new(ValueNode* Left, ValueNode* Right, FilterCheckOperation Op);

typedef struct LogicalExpressionNode {
    INode base;
    NodeType nodeType;
} LogicalExpressionNode;

typedef struct FilterByPassNode {
    LogicalExpressionNode base;
    FilterNode* Wrapped;
    NodeType nodeType;
} FilterByPassNode;

FilterByPassNode* FilterByPassNode_new(FilterNode* F);

typedef struct NotOperationNode {
    LogicalExpressionNode base;
    LogicalExpressionNode* Operand;
    NodeType nodeType;
} NotOperationNode;

NotOperationNode* NotOperationNode_new(LogicalExpressionNode* Op);

typedef struct BinaryLogicalOperationNode {
    LogicalExpressionNode base;
    LogicalExpressionNode* RHS;
    LogicalExpressionNode* LHS;
    NodeType nodeType;
} BinaryLogicalOperationNode;

typedef struct AndOperationNode {
    BinaryLogicalOperationNode base;
    NodeType nodeType;
} AndOperationNode;

AndOperationNode* AndOperationNode_new(LogicalExpressionNode* Left, LogicalExpressionNode* Right);

typedef struct OrOperationNode {
    BinaryLogicalOperationNode base;
    NodeType nodeType;
} OrOperationNode;

OrOperationNode* OrOperationNode_new(LogicalExpressionNode* Left, LogicalExpressionNode* Right);

typedef struct PredicateNode {
    INode base;
    LogicalExpressionNode* Body;
    NodeType nodeType;
} PredicateNode;


PredicateNode* PredicateNode_new(LogicalExpressionNode* Expr);

typedef struct AttributeListNode {
    INode base;
    char** AttrList;
    ValueNode** Values;
    int size;
    NodeType nodeType;
} AttributeListNode;

AttributeListNode* AttributeListNode_new();

int AttributeListNode_addAttribute(AttributeListNode* node, char* name, ValueNode* Value);

typedef struct VariableMatchNode {
    INode base;
    char* VariableName;
    char* SchemeName;
    NodeType nodeType;
} VariableMatchNode;

VariableMatchNode* VariableMatchNode_new(char* Var, char* Scheme);

typedef struct VariablePatternMatchNode {
    VariableMatchNode base;
    AttributeListNode* Pattern;
    NodeType nodeType;
} VariablePatternMatchNode;

VariablePatternMatchNode* VariablePatternMatchNode_new(char* Var, char* Scheme, AttributeListNode* AttrList);

typedef struct VariableFilterMatchNode {
    VariableMatchNode base;
    PredicateNode* Predicate;
    NodeType nodeType;
} VariableFilterMatchNode;

VariableFilterMatchNode* VariableFilterMatchNode_new(char* Var, char* Scheme, PredicateNode* Filters);

typedef enum RelationDirection {
    FORWARD,
    REVERSE,
    ANY
} RelationDirection;

typedef struct RelationMatchNode {
    INode base;
    char* VariableName;
    char* RelationName;
    NodeType nodeType;
    RelationDirection Direction;
} RelationMatchNode;

RelationMatchNode* RelationMatchNode_new(char* Var, char* Rel, RelationDirection Dir);

typedef struct MatchExpressionNode {
    ExpressionNode base;
    VariableMatchNode* LeftNode;
    VariableMatchNode* RightNode;
    RelationMatchNode* Relation;
    NodeType nodeType;
} MatchExpressionNode;

MatchExpressionNode* MatchExpressionNode_new(VariableMatchNode* Node);

MatchExpressionNode* MatchExpressionNode_new2(VariableMatchNode* Left, VariableMatchNode* Right);

MatchExpressionNode* MatchExpressionNode_new3(VariableMatchNode* Left, VariableMatchNode* Right, RelationMatchNode* Rel);

typedef struct ReturnExpressionNode {
    ExpressionNode base;
    ValueNode** Values;
    int size;
    NodeType nodeType;
} ReturnExpressionNode;

ReturnExpressionNode* ReturnExpressionNode_new();

void ReturnExpressionNode_addElement(ReturnExpressionNode* node, ValueNode* Val);

typedef struct SetExpressionNode {
    ExpressionNode base;
    VariableValueNode* Dest;
    ValueNode* Src;
    NodeType nodeType;
} SetExpressionNode;

SetExpressionNode* SetExpressionNode_new(VariableValueNode* Destination, ValueNode* Source);

typedef struct DeleteExpressionNode {
    ExpressionNode base;
    char* VariableName;
    NodeType nodeType;
} DeleteExpressionNode;

DeleteExpressionNode* DeleteExpressionNode_new(char* Name);

typedef struct CreateExpressionNode {
    ExpressionNode base;
    VariableMatchNode* LeftNode;
    VariableMatchNode* RightNode;
    RelationMatchNode* Relation;
    NodeType nodeType;

} CreateExpressionNode;

CreateExpressionNode* CreateExpressionNode_new(VariableMatchNode* Node);

CreateExpressionNode* CreateExpressionNode_new2(VariableMatchNode* Left, VariableMatchNode* Right, RelationMatchNode* Rel);

typedef struct RequestNode {
    INode base;
    ExpressionNode** Expressions;
    int size;
    NodeType nodeType;
    int numChildren;
    struct RequestNode** children;
} RequestNode;

RequestNode* RequestNode_new(ExpressionNode* Expr);

extern void RequestNode_addExpr(RequestNode* node, ExpressionNode* Expr);

#endif // LLP_AST_H
