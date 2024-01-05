#include <stdio.h>
#include "ast.h"
#include "printer.h"

const char *getOperationString(FilterCheckOperation operation) {
    switch (operation) {
        case EQUAL:
            return "EQUAL";
        case GREATER:
            return "GREATER";
        case GREATER_OR_EQUAL:
            return "GREATER_OR_EQUAL";
        case LESS:
            return "LESS";
        case LESS_OR_EQUAL:
            return "LESS_OR_EQUAL";
        case CONTAINS:
            return "CONTAINS";
        default:
            return "UNKNOWN_OPERATION";
    }
}

const char *getDirectionString(RelationDirection direction) {
    switch (direction) {
        case REVERSE:
            return "REVERSE";
        case FORWARD:
            return "FORWARD";
        case ANY:
            return "ANY";
    }
}

static void addSpaces(int level) {
    for (int i = 0; i < level; ++i) {
        printf(" ");
    }
}

void StringLiteralNode_print(ValueNode *node, int level) {
    StringLiteralNode *stringLiteralNode = (StringLiteralNode *) node;
    printf("String Literal node: {\n");
    addSpaces(level + 4);
    printf("Value: %s\n", stringLiteralNode->Value);
    addSpaces(level);
    printf("}\n");
}

void BoolLiteralNode_print(ValueNode *node, int level) {
    BoolLiteralNode *bNode = (BoolLiteralNode *) node;
    printf("Bool Literal node: {\n");
    addSpaces(level + 4);
    printf("Value: %d\n", bNode->Value);
    addSpaces(level);
    printf("}\n");
}

void IntLiteralNode_print(ValueNode *valueNode, int level) {
    IntLiteralNode *iNode = (IntLiteralNode *) valueNode;
    printf("Int Literal node: {\n");
    addSpaces(level + 4);
    printf("Value: %d\n", iNode->Value);
    addSpaces(level);
    printf("}\n");
}

void FloatLiteralNode_print(ValueNode *valueNode, int level) {
    FloatLiteralNode *floatLiteralNode = (FloatLiteralNode *) valueNode;
    printf("Float Literal node: {\n");
    addSpaces(level + 4);
    printf("Value: %f\n", floatLiteralNode->Value);
    addSpaces(level);
    printf("}\n");
}

void AttributeListNode_print(int level, AttributeListNode *attributeListNode) {
    printf("Attribute List: {\n");
    for (int i = 0; i < attributeListNode->size; i++) {
        addSpaces(level + 4);
        printf("Attribute name: %s\n", attributeListNode->AttrList[attributeListNode->size - 1 - i]);
        addSpaces(level + 4);
        printf("Value: ");
        switch (attributeListNode->Values[attributeListNode->size - 1]->nodeType) {
            case STRING_LITERAL_NODE:
                StringLiteralNode_print(attributeListNode->Values[attributeListNode->size - 1 - i], level + 4);
                break;
            case BOOL_LITERAL_NODE:
                BoolLiteralNode_print(attributeListNode->Values[attributeListNode->size - 1 - i], level + 4);
                break;
            case INT_LITERAL_NODE:
                IntLiteralNode_print(attributeListNode->Values[attributeListNode->size - 1 - i], level + 4);
                break;
            case FLOAT_LITERAL_NODE:
                FloatLiteralNode_print(attributeListNode->Values[attributeListNode->size - 1 - i], level + 4);
                break;
            case VARIABLE_VALUE_NODE:
                VariableValueNode_print(attributeListNode->Values[attributeListNode->size - 1 - i], level + 4);
                break;
        }
    }

    addSpaces(level);
    printf("}\n");
}

void NotOperationNode_print(LogicalExpressionNode *logicalExpressionNode, int level) {
    NotOperationNode *notOperationNode = (NotOperationNode *) logicalExpressionNode;
    printf("NOT: {\n");
    addSpaces(level + 4);
    printf("Operand: ");
    FilterByPassNode_print(notOperationNode->Operand, level + 4);
    addSpaces(level);
    printf("}\n");
}

void AndOperationNode_print(BinaryLogicalOperationNode *binaryLogicalOperationNode, int level) {
    printf("AND: {\n");
    addSpaces(level + 4);
    printf("Left operand: ");
    FilterByPassNode_print(binaryLogicalOperationNode->LHS, level + 4);
    addSpaces(level + 4);
    printf("Right operand: ");
    NotOperationNode_print(binaryLogicalOperationNode->RHS, level + 4);
    addSpaces(level);
    printf("}\n");
}

void OrOperationNode_print(BinaryLogicalOperationNode *binaryLogicalOperationNode, int level) {
    printf("OR: {\n");
    addSpaces(level + 4);
    printf("Left operand: %s\n", binaryLogicalOperationNode->LHS);
    addSpaces(level + 4);
    printf("Right operand: %s\n", binaryLogicalOperationNode->RHS);
    addSpaces(level);
    printf("}\n");
}

void FilterNode_print(FilterNode *filterNode, int level) {
    printf("Filter node: {\n");
    addSpaces(level + 4);
    printf("Left part: ");
    VariableValueNode_print(filterNode->LHS, level + 4);
    addSpaces(level + 4);
    printf("Operation: %s\n", getOperationString(filterNode->Operation));
    addSpaces(level + 4);
    printf("Right part: ");

    switch (filterNode->RHS->nodeType) {
        case INT_LITERAL_NODE:
            IntLiteralNode_print(filterNode->RHS, level + 4);
            break;
        case BOOL_LITERAL_NODE:
            BoolLiteralNode_print(filterNode->RHS, level + 4);
            break;
        case FLOAT_LITERAL_NODE:
            FloatLiteralNode_print(filterNode->RHS, level + 4);
            break;
        case STRING_LITERAL_NODE:
            StringLiteralNode_print(filterNode->RHS, level + 4);
    }
    addSpaces(level);
    printf("}\n");
}

void FilterByPassNode_print(FilterByPassNode *filterByPassNode, int level) {
    printf("Filter bypass: {\n");
    addSpaces(level + 4);
    printf("Wrapped filter: ");
    FilterNode_print(filterByPassNode->Wrapped, level + 4);
    addSpaces(level);
    printf("}\n");
}

void PredicateNode_print(PredicateNode *predicateNode, int level) {
    printf("Predicate: {\n");
    addSpaces(level + 4);
    printf("expr: ");
    switch (predicateNode->Body->nodeType) {
        case NOT_OPERATION_NODE:
            NotOperationNode_print(predicateNode->Body, level + 4);
            break;
        case AND_OPERATION_NODE:
            AndOperationNode_print((BinaryLogicalOperationNode *) predicateNode->Body, level + 4);
            break;
        case OR_OPERATION_NODE:
            OrOperationNode_print((BinaryLogicalOperationNode *) predicateNode->Body, level + 4);
            break;
        case FILTER_BY_PASS_NODE:
            FilterByPassNode_print((FilterByPassNode *) predicateNode->Body, level + 4);
            break;
    }
    addSpaces(level);
    printf("}\n");
}

void VariablePatternMatchNode_print(VariableMatchNode *variableMatchNode, int level) {
    VariablePatternMatchNode *variablePatternMatchNode = (VariablePatternMatchNode *) variableMatchNode;
    variablePatternMatchNode->nodeType = ATTRIBUTE_LIST_NODE;
    printf("Variable pattern match: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", variableMatchNode->VariableName);
    addSpaces(level + 4);
    printf("Scheme name: %s\n", variableMatchNode->SchemeName);
    addSpaces(level + 4);
    printf("Pattern: ");
    AttributeListNode_print(level + 4, variablePatternMatchNode->Pattern);
    addSpaces(level);
    printf("}\n");
}

void VariableFilterMatchNode_print(VariableMatchNode *variableMatchNode, int level) {
    VariableFilterMatchNode *variableFilterMatchNode = (VariableFilterMatchNode *) variableMatchNode;
    variableFilterMatchNode->nodeType = PREDICATE_NODE;
    printf("Variable filter match: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", variableMatchNode->VariableName);
    addSpaces(level + 4);
    printf("Scheme name: %s\n", variableMatchNode->SchemeName);
    addSpaces(level + 4);
    printf("Filter: ");
    PredicateNode_print(variableFilterMatchNode->Predicate, level + 4);
    addSpaces(level);
    printf("}\n");
}

void MatchExpressionNode_print(MatchExpressionNode *node, int level) {
    printf("Match expression: {\n");
    addSpaces(level + 4);
    printf("Left node: ");
    switch (node->LeftNode->nodeType) {
        case VARIABLE_PATTERN_MATCH_NODE:
            VariablePatternMatchNode_print(node->LeftNode, level + 4);
            break;
        case VARIABLE_FILTER_MATCH_NODE:
            VariableFilterMatchNode_print(node->LeftNode, level + 4);
            break;
        case ANY_VARIABLE_MATCH_NODE:
            VariableMatchNode_print(node->LeftNode, level + 4);
            break;
    }
    if (node->Relation != NULL) {
        addSpaces(level + 4);
        printf("Relation: ");
        RelationMatchNode_print(node->Relation, level + 4);
    }
    if (node->Relation != NULL) {
        addSpaces(level + 4);
        printf("Right node: ");
        switch (node->RightNode->nodeType) {
            case VARIABLE_PATTERN_MATCH_NODE:
                VariablePatternMatchNode_print(node->RightNode, level + 4);
                break;
            case VARIABLE_FILTER_MATCH_NODE:
                VariableFilterMatchNode_print(node->RightNode, level + 4);
                break;
            case ANY_VARIABLE_MATCH_NODE:
                VariableMatchNode_print(node->RightNode, level + 4);
                break;
        }
    }
    addSpaces(level);
    printf("}\n");
}

void VariableValueNode_print(VariableValueNode *node, int level) {
    VariableValueNode *vNode = (VariableValueNode *) node;
    printf("Variable value node: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", vNode->VariableName);
    addSpaces(level + 4);
    if (node->FieldName != NULL) {
        printf("Field name: %s\n", node->FieldName);
    } else {
        printf("Field name: \n");
    }
    addSpaces(level);
    printf("}\n");
}

void ReturnExpressionNode_print(ReturnExpressionNode *returnExpressionNode, int level) {
    printf("Return Expression: {\n");
    addSpaces(level + 4);
    VariableValueNode *val = (returnExpressionNode->Values);
    VariableValueNode_print((VariableValueNode *) returnExpressionNode->Values[0], level + 4);
    addSpaces(level);
    printf("}\n");
}

void DeleteExpressionNode_print(DeleteExpressionNode *deleteExpressionNode, int level) {
    printf("Delete Expresssion {\n");
    addSpaces(level + 4);
    printf("Variable: %s\n", deleteExpressionNode->VariableName);
    addSpaces(level);
    printf("}\n");
}

void SetExpressionNode_print(SetExpressionNode *setExpressionNode, int level) {
    printf("Set Expression: {\n");
    addSpaces(level + 4);
    printf("Destination: %s\n", setExpressionNode->Dest);
    addSpaces(level + 4);
    printf("Source: %s\n", setExpressionNode->Src);
    addSpaces(level);
    printf("}\n");
}

void VariableMatchNode_print(VariableMatchNode *variableMatchNode, int level) {
    printf("Any variable match: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", variableMatchNode->VariableName);
    addSpaces(level + 4);
    printf("Scheme name: %s\n", variableMatchNode->SchemeName);
    addSpaces(level);
    printf("}\n");
}

void RelationMatchNode_print(RelationMatchNode *relationMatchNode, int level) {
    printf("Relation match: {\n");
    addSpaces(level + 4);
    printf("Variable name: %s\n", relationMatchNode->VariableName);
    addSpaces(level + 4);
    printf("Relation: %s\n", relationMatchNode->RelationName);
    addSpaces(level + 4);
    printf("Direction: %s\n", getDirectionString(relationMatchNode->Direction));
    addSpaces(level);
    printf("}\n");
}

void CreateExpressionNode_print(CreateExpressionNode *createExpressionNode, int level) {
    printf("Create expression: {\n");
    addSpaces(level + 4);
    printf("Left node: ");
    VariablePatternMatchNode_print(createExpressionNode->LeftNode, level + 4);
    if (createExpressionNode->Relation != NULL) {
        addSpaces(level + 4);
        printf("Relation: ");
        RelationMatchNode_print(createExpressionNode->Relation, level + 4);
    }
    if (createExpressionNode->RightNode != NULL) {
        addSpaces(level + 4);
        printf("Right node: ");
        VariablePatternMatchNode_print(createExpressionNode->RightNode, level + 4);
    }
    addSpaces(level);
    printf("}\n");
}

void printAST(RequestNode *node, int depth) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }

    switch (node->nodeType) {
        case REQUEST_NODE:
            printf("Request: \n");
            addSpaces(depth + 4);
            for (int i = 0; i < node->size; i++) {
                ExpressionNode *val = node->Expressions[i];
                switch (node->Expressions[i]->nodeType) {
                    case MATCH_EXPRESSION_NODE: {
                        MatchExpressionNode_print(node->Expressions[i], depth + 4);
                        addSpaces(depth + 4);
                        break;
                    }

                    case RETURN_EXPRESSION_NODE: {
                        ReturnExpressionNode_print(node->Expressions[i], depth + 4);
                        break;
                    }

                    case DELETE_EXPRESSION_NODE:
                        DeleteExpressionNode_print(node->Expressions[i], depth + 4);
                        break;

                    case CREATE_EXPRESSION_NODE:
                        CreateExpressionNode_print(node->Expressions[i], depth + 4);
                        addSpaces(depth + 4);
                        break;

                    case SET_EXPRESSION_NODE:
                        SetExpressionNode_print(node->Expressions[i], depth + 4);
                        addSpaces(depth + 4);
                        break;
                }
            }
            break;
    }
}










