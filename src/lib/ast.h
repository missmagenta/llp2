#ifndef LLP_AST_H
#define LLP_AST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct INode {
    void (*print)(struct INode* node, int level, FILE* out);
} INode;

typedef struct ExpressionNode {
    INode base;
    void (*print)(struct INode* node, int level, FILE* out);
} ExpressionNode;

typedef struct ValueNode {
    INode base;
    void (*print)(struct INode* node, int level, FILE* out);
} ValueNode;

typedef struct VariableValueNode {
    ValueNode base;
    char* VariableName;
    char* FieldName;
    void (*print)(int level, const char* VariableName, const char* FieldName);
} VariableValueNode;

VariableValueNode* VariableValueNode_new(char* VName, char* FName);

typedef struct StringLiteralNode {
    ValueNode base;
    char* Value;
    void (*print)(int level, const char* Value);
} StringLiteralNode;

StringLiteralNode* StringLiteralNode_new(char* Val);

typedef struct BoolLiteralNode {
    ValueNode base;
    int Value;
    void (*print)(int level, int Value);
} BoolLiteralNode;

BoolLiteralNode* BoolLiteralNode_new(int Val);

typedef struct IntLiteralNode {
    ValueNode base;
    int Value;
    void (*print)(int level, int Value);
} IntLiteralNode;

IntLiteralNode* IntLiteralNode_new(int Value);

typedef struct FloatLiteralNode {
    ValueNode base;
    float Value;
    void (*print)(int level, float Value);
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
    void(*print)(int level, const char* Operation, const char* LHS, const char* RHS);
} FilterNode;

FilterNode* FilterNode_new(ValueNode* Left, ValueNode* Right, FilterCheckOperation Op);

typedef struct LogicalExpressionNode {
    INode base;
} LogicalExpressionNode;

typedef struct FilterByPassNode {
    LogicalExpressionNode base;
    FilterNode* Wrapped;
    void(*print)(int level, const char* Wrapped);
} FilterByPassNode;

FilterByPassNode* FilterByPassNode_new(FilterNode* F);

typedef struct NotOperationNode {
    LogicalExpressionNode base;
    LogicalExpressionNode* Operand;
    void (*print)(int level, const char* Operand);
} NotOperationNode;

NotOperationNode* NotOperationNode_new(LogicalExpressionNode* Op);

typedef struct BinaryLogicalOperationNode {
    LogicalExpressionNode base;
    LogicalExpressionNode* RHS;
    LogicalExpressionNode* LHS;
} BinaryLogicalOperationNode;

typedef struct AndOperationNode {
    BinaryLogicalOperationNode base;
    void (*print)(int level, const char* LHS, const char* RHS);
} AndOperationNode;

AndOperationNode* AndOperationNode_new(LogicalExpressionNode* Left, LogicalExpressionNode* Right);

typedef struct OrOperationNode {
    BinaryLogicalOperationNode base;
    void (*print)(int level, const char* LHS, const char* RHS);
} OrOperationNode;

OrOperationNode* OrOperationNode_new(LogicalExpressionNode* Left, LogicalExpressionNode* Right);

typedef struct PredicateNode {
    INode base;
    LogicalExpressionNode* Body;
    void(*print)(int level, const char* Body);
} PredicateNode;


PredicateNode* PredicateNode_new(LogicalExpressionNode* Expr);

typedef struct AttributeListNode {
    INode base;
    char** AttrList;
    ValueNode** Values;
    int size;
    void (*print)(int level, const char* AttrList);
} AttributeListNode;

AttributeListNode* AttributeListNode_new();

int AttributeListNode_addAttribute(AttributeListNode* node, char* name, ValueNode* Value);

typedef struct VariableMatchNode {
    INode base;
    char* VariableName;
    char* SchemeName;
    void (*print) (int level, const char* VariableName, const char* SchemeName);
} VariableMatchNode;

VariableMatchNode* VariableMatchNode_new(char* Var, char* Scheme);

typedef struct VariablePatternMatchNode {
    VariableMatchNode base;
    AttributeListNode* Pattern;
    void (*print)(int level, const char* VariableName, const char* SchemeName, const char* Pattern);
} VariablePatternMatchNode;

VariablePatternMatchNode* VariablePatternMatchNode_new(char* Var, char* Scheme, AttributeListNode* AttrList);

typedef struct VariableFilterMatchNode {
    VariableMatchNode base;
    PredicateNode* Predicate;
    void (*print)(int level, const char* VariableName, const char* SchemeName, const char* Predicate);
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
    void (*print)(int level, const char* VariableName, const char* RelationName, const char* Direction);
    RelationDirection Direction;
} RelationMatchNode;

RelationMatchNode* RelationMatchNode_new(char* Var, char* Rel, RelationDirection Dir);

typedef struct MatchExpressionNode {
    ExpressionNode base;
    VariableMatchNode* LeftNode;
    VariableMatchNode* RightNode;
    RelationMatchNode* Relation;
    void (*print)(int level, const char* LeftNode, const char* Relation, const char* RightNode);
} MatchExpressionNode;

MatchExpressionNode* MatchExpressionNode_new(VariableMatchNode* Node);

MatchExpressionNode* MatchExpressionNode_new2(VariableMatchNode* Left, VariableMatchNode* Right);

MatchExpressionNode* MatchExpressionNode_new3(VariableMatchNode* Left, VariableMatchNode* Right, RelationMatchNode* Rel);

typedef struct ReturnExpressionNode {
    ExpressionNode base;
    ValueNode** Values;
    int size;
    void (*print)(struct INode* node, int level, FILE* out);
} ReturnExpressionNode;

ReturnExpressionNode* ReturnExpressionNode_new();

void ReturnExpressionNode_addElement(ReturnExpressionNode* node, ValueNode* Val);

typedef struct SetExpressionNode {
    ExpressionNode base;
    VariableValueNode* Dest;
    ValueNode* Src;
    void (*print)(int level, const char* Dest, const char* Src);
} SetExpressionNode;

SetExpressionNode* SetExpressionNode_new(VariableValueNode* Destination, ValueNode* Source);

typedef struct DeleteExpressionNode {
    ExpressionNode base;
    char* VariableName;
    void(*print)(int level, const char* VariableName);
} DeleteExpressionNode;

DeleteExpressionNode* DeleteExpressionNode_new(char* Name);

typedef struct CreateExpressionNode {
    ExpressionNode base;
    VariableMatchNode* LeftNode;
    VariableMatchNode* RightNode;
    RelationMatchNode* Relation;
    void(*print)(int level, const char* LeftNode, const char* Relation, const char* RightNode);

} CreateExpressionNode;

CreateExpressionNode* CreateExpressionNode_new(VariableMatchNode* Node);

CreateExpressionNode* CreateExpressionNode_new2(VariableMatchNode* Left, VariableMatchNode* Right, RelationMatchNode* Rel);

typedef struct RequestNode {
    INode base;
    ExpressionNode** Expressions;
    int size;
    void (*print)(struct INode* node, int level, FILE* out);
} RequestNode;

RequestNode* RequestNode_new(ExpressionNode* Expr);

extern void RequestNode_addExpr(RequestNode* node, ExpressionNode* Expr);

#endif // LLP_AST_H
