#include "ast.h"
#include "printer.h"

VariableValueNode *VariableValueNode_new(char *VName, char *FName) {
    VariableValueNode *node = (VariableValueNode *) malloc(sizeof(VariableValueNode));
    node->VariableName = VName;
    node->FieldName = FName;
    node->base.nodeType = VARIABLE_VALUE_NODE;
    return node;
}

StringLiteralNode *StringLiteralNode_new(char *Val) {
    StringLiteralNode *node = (StringLiteralNode *) malloc(sizeof(StringLiteralNode));
    node->Value = Val;
    node->base.nodeType = STRING_LITERAL_NODE;
    return node;
}

BoolLiteralNode *BoolLiteralNode_new(int Val) {
    BoolLiteralNode *node = (BoolLiteralNode *) malloc(sizeof(BoolLiteralNode));
    node->Value = Val;
    node->base.nodeType = BOOL_LITERAL_NODE;
    return node;
}

IntLiteralNode *IntLiteralNode_new(int Val) {
    IntLiteralNode *node = (IntLiteralNode *) malloc(sizeof(IntLiteralNode));
    node->Value = Val;
    node->base.nodeType = INT_LITERAL_NODE;
    return node;
}

FloatLiteralNode *FloatLiteralNode_new(float Val) {
    FloatLiteralNode *node = (FloatLiteralNode *) malloc(sizeof(FloatLiteralNode));
    node->Value = Val;
    node->base.nodeType = FLOAT_LITERAL_NODE;
    return node;
}

FilterNode *FilterNode_new(ValueNode *Left, ValueNode *Right, FilterCheckOperation Op) {
    FilterNode *node = (FilterNode *) malloc(sizeof(FilterNode));
    node->RHS = Right;
    node->LHS = Left;
    node->Operation = Op;
    node->base.nodeType = FILTER_NODE;
    return node;
}

FilterByPassNode *FilterByPassNode_new(FilterNode *F) {
    FilterByPassNode *node = (FilterByPassNode *) malloc(sizeof(FilterByPassNode));
    node->Wrapped = F;
    node->base.nodeType = FILTER_BY_PASS_NODE;
    return node;
}

NotOperationNode *NotOperationNode_new(LogicalExpressionNode *Op) {
    NotOperationNode *node = (NotOperationNode *) malloc(sizeof(NotOperationNode));
    node->base.nodeType = NOT_OPERATION_NODE;
    node->Operand = Op;
    return node;
}

AndOperationNode *AndOperationNode_new(LogicalExpressionNode *Left, LogicalExpressionNode *Right) {
    AndOperationNode *node = (AndOperationNode *) malloc(sizeof(AndOperationNode));
    node->base.base.nodeType = AND_OPERATION_NODE;
    node->base.RHS = Right;
    node->base.LHS = Left;
    return node;
}

OrOperationNode *OrOperationNode_new(LogicalExpressionNode *Left, LogicalExpressionNode *Right) {
    OrOperationNode *node = (OrOperationNode *) malloc(sizeof(OrOperationNode));
    node->base.nodeType = OR_OPERATION_NODE;
    node->base.RHS = Right;
    node->base.LHS = Left;
    return node;
}

PredicateNode *PredicateNode_new(LogicalExpressionNode *Expr) {
    PredicateNode *node = (PredicateNode *) malloc(sizeof(PredicateNode));
    node->base.nodeType = PREDICATE_NODE;
    node->Body = Expr;
    return node;
}

AttributeListNode *AttributeListNode_new() {
    AttributeListNode *node = (AttributeListNode *) malloc(sizeof(AttributeListNode));
    node->base.nodeType = ATTRIBUTE_LIST_NODE;
    node->AttrList = NULL;
    node->Values = NULL;
    node->size = 0;
    return node;
}


int AttributeListNode_addAttribute(AttributeListNode *node, char *name, ValueNode *Value) {
    for (int i = 0; i < node->size; i++) {
        if (strcmp(node->AttrList[i], name) == 0) {
            return 0;
        }
    }
    node->size++;
    node->AttrList = (char **) realloc(node->AttrList, node->size * sizeof(char *));
    node->Values = (ValueNode **) realloc(node->Values, node->size * sizeof(ValueNode *));
    node->AttrList[node->size - 1] = name;
    node->Values[node->size - 1] = Value;
    return 1;
}


VariableMatchNode *VariableMatchNode_new(char *Var, char *Scheme) {
    VariableMatchNode *node = (VariableMatchNode *) malloc(sizeof(VariableMatchNode));
    node->nodeType = ANY_VARIABLE_MATCH_NODE;
    node->VariableName = Var;
    node->SchemeName = Scheme;
    return node;
}


VariablePatternMatchNode *VariablePatternMatchNode_new(char *Var, char *Scheme, AttributeListNode *AttrList) {
    VariablePatternMatchNode *node = (VariablePatternMatchNode *) malloc(sizeof(VariablePatternMatchNode));
    node->base.nodeType = VARIABLE_PATTERN_MATCH_NODE;
    node->base.VariableName = Var;
    node->base.SchemeName = Scheme;
    node->Pattern = AttrList;
    return node;
}

VariableFilterMatchNode *VariableFilterMatchNode_new(char *Var, char *Scheme, PredicateNode *Filters) {
    VariableFilterMatchNode *node = (VariableFilterMatchNode *) malloc(sizeof(VariableFilterMatchNode));
    node->base.nodeType = VARIABLE_FILTER_MATCH_NODE;
    node->base.VariableName = Var;
    node->base.SchemeName = Scheme;
    node->Predicate = Filters;
    return node;
}

RelationMatchNode *RelationMatchNode_new(char *Var, char *Rel, RelationDirection Dir) {
    RelationMatchNode *node = (RelationMatchNode *) malloc(sizeof(RelationMatchNode));
    node->nodeType = RELATION_MATCH_NODE;
    node->VariableName = Var;
    node->RelationName = Rel;
    node->Direction = Dir;
    return node;
}


MatchExpressionNode *MatchExpressionNode_new(VariableMatchNode *Node) {
    MatchExpressionNode *node = (MatchExpressionNode *) malloc(sizeof(MatchExpressionNode));
    node->base.nodeType = MATCH_EXPRESSION_NODE;
    node->LeftNode = Node;
    node->RightNode = NULL;
    node->Relation = NULL;
    return node;
}

MatchExpressionNode *MatchExpressionNode_new2(VariableMatchNode *Left, VariableMatchNode *Right) {
    MatchExpressionNode *node = (MatchExpressionNode *) malloc(sizeof(MatchExpressionNode));
    node->base.nodeType = MATCH_EXPRESSION_NODE;
    node->LeftNode = Left;
    node->RightNode = Right;
    node->Relation = RelationMatchNode_new("", "", ANY);
    return node;
}

MatchExpressionNode *
MatchExpressionNode_new3(VariableMatchNode *Left, VariableMatchNode *Right, RelationMatchNode *Rel) {
    MatchExpressionNode *node = (MatchExpressionNode *) malloc(sizeof(MatchExpressionNode));
    node->base.nodeType = MATCH_EXPRESSION_NODE;
    node->LeftNode = Left;
    node->RightNode = Right;
    node->Relation = Rel;
    return node;
}

ReturnExpressionNode *ReturnExpressionNode_new() {
    ReturnExpressionNode *node = (ReturnExpressionNode *) malloc(sizeof(ReturnExpressionNode));
    node->base.nodeType = RETURN_EXPRESSION_NODE;
    node->Values = NULL;
    node->size = 0;
    return node;
}

void ReturnExpressionNode_addElement(ReturnExpressionNode *node, ValueNode *Val) {
    node->size++;
    node->Values = (ValueNode **) realloc(node->Values, node->size * sizeof(ValueNode *));
    node->Values[node->size - 1] = Val;
}

SetExpressionNode *SetExpressionNode_new(VariableValueNode *Destination, ValueNode *Source) {
    SetExpressionNode *node = (SetExpressionNode *) malloc(sizeof(SetExpressionNode));
    node->nodeType = SET_EXPRESSION_NODE;
    node->Dest = Destination;
    node->Src = Source;
    return node;
}

DeleteExpressionNode *DeleteExpressionNode_new(char *Name) {
    DeleteExpressionNode *node = (DeleteExpressionNode *) malloc(sizeof(DeleteExpressionNode));
    node->base.nodeType = DELETE_EXPRESSION_NODE;
    node->VariableName = Name;
    return node;
}

CreateExpressionNode *CreateExpressionNode_new(VariableMatchNode *Node) {
    CreateExpressionNode *node = (CreateExpressionNode *) malloc(sizeof(CreateExpressionNode));
    node->base.nodeType = CREATE_EXPRESSION_NODE;
    node->LeftNode = Node;
    node->RightNode = NULL;
    node->Relation = NULL;
    return node;
}

CreateExpressionNode *
CreateExpressionNode_new2(VariableMatchNode *Left, VariableMatchNode *Right, RelationMatchNode *Rel) {
    CreateExpressionNode *node = (CreateExpressionNode *) malloc(sizeof(CreateExpressionNode));
    node->base.nodeType = CREATE_EXPRESSION_NODE;
    node->LeftNode = Left;
    node->RightNode = Right;
    node->Relation = Rel;
    return node;
}


RequestNode *RequestNode_new(ExpressionNode *Expr) {
    RequestNode *node = (RequestNode *) malloc(sizeof(RequestNode));
    node->Expressions = (ExpressionNode **) malloc(sizeof(ExpressionNode *));
    node->Expressions[0] = Expr;
    node->size = 1;
    node->nodeType = REQUEST_NODE;
    return node;
}


extern void RequestNode_addExpr(RequestNode *node, ExpressionNode *Expr) {
    node->size++;
    node->Expressions = (ExpressionNode **) realloc(node->Expressions, node->size * sizeof(ExpressionNode *));
    node->Expressions[node->size - 1] = Expr;
}


void insert(RequestNode *v) {
    printf("Something was inserted to controllers. Check results\n");
    printAST(v, 0);
    printf("}\n");
}