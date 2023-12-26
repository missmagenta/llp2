#ifndef LLP2_PRINTER_H
#define LLP2_PRINTER_H

void VariableValueNode_print(struct INode* node, int level, FILE* out);
void StringLiteralNode_print(struct INode* node, int level, FILE* out);
void BoolLiteralNode_print(int level, int Value);
void IntLiteralNode_print(int level, int Value);
void FloatLiteralNode_print(int level, float Value);
void FilterNode_print(int level, const char* Operation, const char* LHS, const char* RHS);
void FilterByPassNode_print(int level, const char* Wrapped);
void NotOperationNode_print(int level, const char* Operand);
void AndOperationNode_print(int level, const char* LHS, const char* RHS);
void OrOperationNode_print(int level, const char* LHS, const char* RHS);
void PredicateNode_print(int level, const char* Body);
void AttributeListNode_print(int level, const char* AttrList);
void VariableMatchNode_print(int level, const char* VariableName, const char* SchemeName);
void VariablePatternMatchNode_print(int level, const char* VariableName, const char* SchemeName, const char* Pattern);
void VariableFilterMatchNode_print(int level, const char* VariableName, const char* SchemeName, const char* Predicate);
void RelationMatchNode_print(int level, const char* VariableName, const char* RelationName, const char* Direction);
void MatchExpressionNode_print(int level, const char* LeftNode, const char* Relation, const char* RightNode);
void ReturnExpressionNode_print(struct INode* node, int level, FILE* out);
void DeleteExpressionNode_print(int level, const char* VariableName);
void CreateExpressionNode_print(int level, const char* LeftNode, const char* Relation, const char* RightNode);
void SetExpressionNode_print(int level, const char* Dest, const char* Src);
void RequestNode_print(struct INode* node, int level, FILE* out);
void insert(RequestNode *v);

#endif //LLP2_PRINTER_H
