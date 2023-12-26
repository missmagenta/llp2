#include <stdio.h>
#include "ast.h"
#include "printer.h"

static void addSpaces(int level) {
    for (int i = 0; i < level; ++i) {
        printf(" ");
    }
}

void INode_print(struct INode* node, int level, FILE* out) {
    if (node != NULL && node->print != NULL) {
        node->print(node, level, out);
    }
}

void VariableValueNode_print(struct INode* node, int level, FILE* out) {
    VariableValueNode* vNode = (VariableValueNode*)node;
    printf("Variable value node: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", vNode->VariableName);
    addSpaces(level + 4);
    printf("Field name: %s\n", vNode->FieldName);
    addSpaces(level);
    printf("}\n");
}

void StringLiteralNode_print(struct INode* node, int level, FILE* out) {
    StringLiteralNode* snode = (StringLiteralNode*)node;
    printf("String Literal node: {\n");
    addSpaces(level + 4);
    printf("Value: %s\n", snode->Value);
    addSpaces(level);
    printf("}\n");
}

void BoolLiteralNode_print(int level, int Value) {
    printf("Bool Literal node: {\n");
    addSpaces(level + 4);
    printf("Value: %d\n", Value);
    addSpaces(level);
    printf("}\n");
}

void IntLiteralNode_print(int level, int Value) {
    printf("Int Literal node: {\n");
    addSpaces(level + 4);
    printf("Value: %d\n", Value);
    addSpaces(level);
    printf("}\n");
}

void FloatLiteralNode_print(int level, float Value) {
    printf("Float Literal node: {\n");
    addSpaces(level + 4);
    printf("Value: %f\n", Value);
    addSpaces(level);
    printf("}\n");
}

void FilterNode_print(int level, const char* Operation, const char* LHS, const char* RHS) {
    printf("Filter node: {\n");
    addSpaces(level + 4);
    printf("Left part: %s\n", LHS);
    addSpaces(level + 4);
    printf("Operation: %s\n", Operation);
    addSpaces(level + 4);
    printf("Right part: %s\n", RHS);
    addSpaces(level);
    printf("}\n");
}

void FilterByPassNode_print(int level, const char* Wrapped) {
    printf("Filter bypass: {\n");
    addSpaces(level + 4);
    printf("Wrapped filter: %s\n", Wrapped);
    addSpaces(level);
    printf("}\n");
}

void NotOperationNode_print(int level, const char* Operand) {
    printf("NOT: {\n");
    addSpaces(level + 4);
    printf("Operand: %s\n", Operand);
    addSpaces(level);
    printf("}\n");
}

void AndOperationNode_print(int level, const char* LHS, const char* RHS) {
    printf("AND: {\n");
    addSpaces(level + 4);
    printf("Left operand: %s\n", LHS);
    addSpaces(level + 4);
    printf("Right operand: %s\n", RHS);
    addSpaces(level);
    printf("}\n");
}

void OrOperationNode_print(int level, const char* LHS, const char* RHS) {
    printf("OR: {\n");
    addSpaces(level + 4);
    printf("Left operand: %s\n", LHS);
    addSpaces(level + 4);
    printf("Right operand: %s\n", RHS);
    addSpaces(level);
    printf("}\n");
}

void PredicateNode_print(int level, const char* Body) {
    printf("Predicate: {\n");
    addSpaces(level + 4);
    printf("expr: %s\n", Body);
    addSpaces(level);
    printf("}\n");
}

void AttributeListNode_print(int level, const char* AttrList) {
    printf("Attribute List: {\n");
    printf("Attribute name: %s\n", AttrList);
    addSpaces(level);
    printf("}\n");
}

void VariableMatchNode_print(int level, const char* VariableName, const char* SchemeName) {
    printf("Any variable match: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", VariableName);
    addSpaces(level + 4);
    printf("Scheme name: %s\n", SchemeName);
    addSpaces(level);
    printf("}\n");
}

void VariablePatternMatchNode_print(int level, const char* VariableName, const char* SchemeName, const char* Pattern) {
    printf("Variable pattern match: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", VariableName);
    addSpaces(level + 4);
    printf("Scheme name: %s\n", SchemeName);
    addSpaces(level + 4);
    printf("Pattern: %s\n", Pattern);
    addSpaces(level);
    printf("}\n");
}

void VariableFilterMatchNode_print(int level, const char* VariableName, const char* SchemeName, const char* Predicate) {
    printf("Variable filter match: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", VariableName);
    addSpaces(level + 4);
    printf("Scheme name: %s\n", SchemeName);
    addSpaces(level + 4);
    printf("Filter: %s\n", Predicate);
    addSpaces(level);
    printf("}\n");
}

void RelationMatchNode_print(int level, const char* VariableName, const char* RelationName, const char* Direction) {
    printf("Relation match: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", VariableName);
    addSpaces(level + 4);
    printf("Relation: %s\n", RelationName);
    addSpaces(level + 4);
    printf("Direction: %s\n", Direction);
    addSpaces(level);
    printf("}\n");
}

void MatchExpressionNode_print(int level, const char* LeftNode, const char* Relation, const char* RightNode) {
    printf("Match expression: {\n");
    addSpaces(level + 4);
    printf("Left node: %s\n", LeftNode);
    if (Relation != NULL) {
        addSpaces(level + 4);
        printf("Relation: %s\n", Relation);
    }
    if (RightNode != NULL) {
        addSpaces(level + 4);
        printf("Right node: %s\n", RightNode);
    }
    addSpaces(level);
    printf("}\n");
}

void ReturnExpressionNode_print(struct INode* node, int level, FILE* out) {
    ReturnExpressionNode* rNode = (ReturnExpressionNode*)node;
    printf("Return Expression: {\n");
    addSpaces(level);
    printf("}\n");
}

void SetExpressionNode_print(int level, const char* Dest, const char* Src) {
    printf("Set Expression: {\n");
    addSpaces(level + 4);
    printf("Destination: %s\n", Dest);
    addSpaces(level + 4);
    printf("Source: %s\n", Src);
    addSpaces(level);
    printf("}\n");
}

void DeleteExpressionNode_print(int level, const char* VariableName) {
    printf("Delete Expresssion {\n");
    addSpaces(level + 4);
    printf("Variable: %s\n", VariableName);
    addSpaces(level);
    printf("}\n");
}

void CreateExpressionNode_print(int level, const char* LeftNode, const char* Relation, const char* RightNode) {
    printf("Create expression: {\n");
    addSpaces(level + 4);
    printf("Left node: %s\n", LeftNode);
    if (Relation != NULL) {
        addSpaces(level + 4);
        printf("Relation: %s\n", Relation);
    }
    if (RightNode != NULL) {
        addSpaces(level + 4);
        printf("Right node: %s\n", RightNode);
    }
    addSpaces(level);
    printf("}\n");
}

void RequestNode_print(struct INode* node, int level, FILE* out) {
    printf("Request: {\n");
    addSpaces(level);
    printf("}\n");
}

void printNodeWithIndent(int level, void (*nodePrint)(int, ...)) {
    nodePrint(level);
}


void insert(RequestNode *v) {
    printf("Something was inserted to controllers. Check results\n");
    v->base.print = RequestNode_print;
    INode_print(&(v->base), 0, stdout);
}





