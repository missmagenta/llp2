#ifndef LLP2_PRINTER_H
#define LLP2_PRINTER_H

void VariableValueNode_print(VariableValueNode* node, int level);
void StringLiteralNode_print(ValueNode* valueNode, int level);
void BoolLiteralNode_print(ValueNode* valueNode, int level);
void IntLiteralNode_print(ValueNode* valueNode, int level);
void FloatLiteralNode_print(ValueNode* valueNode, int level);
void FilterNode_print(FilterNode* filterNode, int level);
void FilterByPassNode_print(FilterByPassNode* filterByPassNode, int level);
void NotOperationNode_print(LogicalExpressionNode* logicalExpressionNode, int level);
void AndOperationNode_print(BinaryLogicalOperationNode* binaryLogicalOperationNode, int level);
void OrOperationNode_print(BinaryLogicalOperationNode* binaryLogicalOperationNode, int level);
void PredicateNode_print(PredicateNode* predicateNode, int level);
void AttributeListNode_print(int level, AttributeListNode* attributeListNode);
void VariableMatchNode_print(VariableMatchNode* variableMatchNode, int level);
void VariablePatternMatchNode_print(VariableMatchNode* variableMatchNode, int level);
void VariableFilterMatchNode_print(VariableMatchNode* variableMatchNode, int level);
void RelationMatchNode_print(RelationMatchNode* relationMatchNode, int level);
void MatchExpressionNode_print(MatchExpressionNode* node, int level);
void ReturnExpressionNode_print(ReturnExpressionNode* returnExpressionNode, int level);
void DeleteExpressionNode_print(DeleteExpressionNode* deleteExpressionNode, int level);
void CreateExpressionNode_print(CreateExpressionNode* createExpressionNode, int level);
void SetExpressionNode_print(SetExpressionNode* setExpressionNode, int level);
const char* getOperationString(FilterCheckOperation operation);
const char* getDirectionString(RelationDirection direction);
void printAST(RequestNode *node, int depth);
void insert(RequestNode *v);

#endif //LLP2_PRINTER_H
