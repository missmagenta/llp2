#include "ast.h"
#include "printer.h"

static void addSpaces(int level) {
    for (int i = 0; i < level; ++i) {
        printf(" ");
    }
}

VariableValueNode* VariableValueNode_new(char* VName, char* FName) {
    VariableValueNode* node = (VariableValueNode*)malloc(sizeof(VariableValueNode));
    node->base.print = (void (*)(struct INode*, int, FILE*)) VariableValueNode_print;
    node->VariableName = VName;
    node->FieldName = FName;
    VariableValueNode_print((struct INode *) node, 0, stdout);
    return node;
}

StringLiteralNode* StringLiteralNode_new(char* Val) {
    StringLiteralNode* node = (StringLiteralNode*)malloc(sizeof(StringLiteralNode));
    node->base.print = StringLiteralNode_print;
    node->Value = Val;
    StringLiteralNode_print((struct INode *) node, 0, stdout);
    return node;
}

BoolLiteralNode* BoolLiteralNode_new(int Val) {
    BoolLiteralNode* node = (BoolLiteralNode*)malloc(sizeof(BoolLiteralNode));
    node->print = BoolLiteralNode_print;
    node->Value = Val;
    BoolLiteralNode_print(0, Val);
    return node;
}

IntLiteralNode* IntLiteralNode_new(int Val) {
    IntLiteralNode* node = (IntLiteralNode*)malloc(sizeof(IntLiteralNode));
    node->print = IntLiteralNode_print;
    node->Value = Val;
    IntLiteralNode_print(0, Val);
    return node;
}

FloatLiteralNode* FloatLiteralNode_new(float Val) {
    FloatLiteralNode* node = (FloatLiteralNode*)malloc(sizeof(FloatLiteralNode));
    node->print = FloatLiteralNode_print;
    node->Value = Val;
    FloatLiteralNode_print(0, Val);
    return node;
}

FilterNode* FilterNode_new(ValueNode* Left, ValueNode* Right, FilterCheckOperation Op) {
    FilterNode* node = (FilterNode*)malloc(sizeof(FilterNode));
    node->print = FilterNode_print;
    node->RHS = Right;
    node->LHS = Left;
    node->Operation = Op;
    FilterNode_print(0, (const char *) Op, "", "");
    return node;
}

FilterByPassNode* FilterByPassNode_new(FilterNode* F) {
    FilterByPassNode* node = (FilterByPassNode*)malloc(sizeof(FilterByPassNode));
    node->print = FilterByPassNode_print;
    node->Wrapped = F;
    FilterByPassNode_print(0, (const char *) F);
    return node;
}

NotOperationNode* NotOperationNode_new(LogicalExpressionNode* Op) {
    NotOperationNode* node = (NotOperationNode*)malloc(sizeof(NotOperationNode));
    node->print = NotOperationNode_print;
    node->Operand = Op;
    NotOperationNode_print(0, (const char *) Op);
    return node;
}

AndOperationNode* AndOperationNode_new(LogicalExpressionNode* Left, LogicalExpressionNode* Right) {
    AndOperationNode* node = (AndOperationNode*)malloc(sizeof(AndOperationNode));
    node->print = AndOperationNode_print;
    node->base.RHS = Right;
    node->base.LHS = Left;
    AndOperationNode_print(0, Left, Right);
    return node;
}

OrOperationNode* OrOperationNode_new(LogicalExpressionNode* Left, LogicalExpressionNode* Right) {
    OrOperationNode* node = (OrOperationNode*)malloc(sizeof(OrOperationNode));
    node->print = OrOperationNode_print;
    node->base.RHS = Right;
    node->base.LHS = Left;
    OrOperationNode_print(0, Left, Right);
    return node;
}

PredicateNode* PredicateNode_new(LogicalExpressionNode* Expr) {
    PredicateNode* node = (PredicateNode*)malloc(sizeof(PredicateNode));
    node->print = PredicateNode_print;
    node->Body = Expr;
    PredicateNode_print(0, (const char *) Expr);
    return node;
}

AttributeListNode* AttributeListNode_new() {
    AttributeListNode* node = (AttributeListNode*)malloc(sizeof(AttributeListNode));
    node->print = AttributeListNode_print;
    node->AttrList = NULL;
    node->Values = NULL;
    node->size = 0;
    AttributeListNode_print(0, (const char *) node->AttrList);
    return node;
}


int AttributeListNode_addAttribute(AttributeListNode* node, char* name, ValueNode* Value) {
    for (int i = 0; i < node->size; i++) {
        if (strcmp(node->AttrList[i], name) == 0) {
            return 0;
        }
    }
    node->size++;
    node->AttrList = (char**)realloc(node->AttrList, node->size * sizeof(char*));
    node->Values = (ValueNode**)realloc(node->Values, node->size * sizeof(ValueNode*));
    node->AttrList[node->size - 1] = name;
    node->Values[node->size - 1] = Value;
    AttributeListNode_print(0, node->AttrList[node->size - 1]);
    return 1;
}


VariableMatchNode* VariableMatchNode_new(char* Var, char* Scheme) {
    VariableMatchNode* node = (VariableMatchNode*)malloc(sizeof(VariableMatchNode));
    node->print = VariableMatchNode_print;
    node->VariableName = Var;
    node->SchemeName = Scheme;
    VariableMatchNode_print(0, Var, Scheme);
    return node;
}


VariablePatternMatchNode* VariablePatternMatchNode_new(char* Var, char* Scheme, AttributeListNode* AttrList) {
    VariablePatternMatchNode* node = (VariablePatternMatchNode*)malloc(sizeof(VariablePatternMatchNode));
    node->print = VariablePatternMatchNode_print;
    node->base.VariableName = Var;
    node->base.SchemeName = Scheme;
    node->Pattern = AttrList;
    VariablePatternMatchNode_print(0, Var, Scheme, AttrList);
    return node;
}

VariableFilterMatchNode* VariableFilterMatchNode_new(char* Var, char* Scheme, PredicateNode* Filters) {
    VariableFilterMatchNode* node = (VariableFilterMatchNode*)malloc(sizeof(VariableFilterMatchNode));
    node->print = VariableFilterMatchNode_print;
    node->base.VariableName = Var;
    node->base.SchemeName = Scheme;
    node->Predicate = Filters;
    VariableFilterMatchNode_print(0, Var, Scheme, Filters);
    return node;
}

RelationMatchNode* RelationMatchNode_new(char* Var, char* Rel, RelationDirection Dir) {
    RelationMatchNode* node = (RelationMatchNode*)malloc(sizeof(RelationMatchNode));
    node->print = RelationMatchNode_print;
    node->VariableName = Var;
    node->RelationName = Rel;
    node->Direction = Dir;
    RelationMatchNode_print(4, Var, Rel, "1");
    return node;
}


MatchExpressionNode* MatchExpressionNode_new(VariableMatchNode* Node) {
    MatchExpressionNode* node = (MatchExpressionNode*)malloc(sizeof(MatchExpressionNode));
    node->print = MatchExpressionNode_print;
    node->LeftNode = Node;
    node->RightNode = NULL;
    node->Relation = NULL;
    MatchExpressionNode_print(4, Node, NULL, NULL);
    return node;
}

MatchExpressionNode* MatchExpressionNode_new2(VariableMatchNode* Left, VariableMatchNode* Right) {
    MatchExpressionNode* node = (MatchExpressionNode*)malloc(sizeof(MatchExpressionNode));
    node->print = MatchExpressionNode_print;
    node->LeftNode = Left;
    node->RightNode = Right;
    node->Relation = RelationMatchNode_new("", "", ANY);
    MatchExpressionNode_print(4, Left, "", Right);
    return node;
}

MatchExpressionNode* MatchExpressionNode_new3(VariableMatchNode* Left, VariableMatchNode* Right, RelationMatchNode* Rel) {
    MatchExpressionNode* node = (MatchExpressionNode*)malloc(sizeof(MatchExpressionNode));
    node->print = MatchExpressionNode_print;
    node->LeftNode = Left;
    node->RightNode = Right;
    node->Relation = Rel;
    MatchExpressionNode_print(0, Left, Right, Rel);
    return node;
}

ReturnExpressionNode* ReturnExpressionNode_new() {
    ReturnExpressionNode* node = (ReturnExpressionNode*)malloc(sizeof(ReturnExpressionNode));
    node->print = ReturnExpressionNode_print;
    node->Values = NULL;
    node->size = 0;
    ReturnExpressionNode_print((struct INode *) node, 0, stdout);
    return node;
}

void ReturnExpressionNode_addElement(ReturnExpressionNode* node, ValueNode* Val) {
    node->size++;
    node->Values = (ValueNode**)realloc(node->Values, node->size * sizeof(ValueNode*));
    node->Values[node->size - 1] = Val;
}

SetExpressionNode* SetExpressionNode_new(VariableValueNode* Destination, ValueNode* Source) {
    SetExpressionNode* node = (SetExpressionNode*)malloc(sizeof(SetExpressionNode));
    node->print = SetExpressionNode_print;
    node->Dest = Destination;
    node->Src = Source;
    SetExpressionNode_print(0, Destination, Source);
    return node;
}

DeleteExpressionNode* DeleteExpressionNode_new(char* Name) {
    DeleteExpressionNode* node = (DeleteExpressionNode*)malloc(sizeof(DeleteExpressionNode));
    node->print = DeleteExpressionNode_print;
    node->VariableName = Name;
    DeleteExpressionNode_print(0, Name);
    return node;
}

CreateExpressionNode* CreateExpressionNode_new(VariableMatchNode* Node) {
    CreateExpressionNode* node = (CreateExpressionNode*)malloc(sizeof(CreateExpressionNode));
    node->print = CreateExpressionNode_print;
    node->LeftNode = Node;
    node->RightNode = NULL;
    node->Relation = NULL;
    CreateExpressionNode_print(0, Node, NULL, NULL);
    return node;
}

CreateExpressionNode* CreateExpressionNode_new2(VariableMatchNode* Left, VariableMatchNode* Right, RelationMatchNode* Rel) {
    CreateExpressionNode* node = (CreateExpressionNode*)malloc(sizeof(CreateExpressionNode));
    node->print = CreateExpressionNode_print;
    node->LeftNode = Left;
    node->RightNode = Right;
    node->Relation = Rel;
    CreateExpressionNode_print(0, Left, Rel, Right);
    return node;
}

RequestNode* RequestNode_new(ExpressionNode* Expr) {
    RequestNode* node = (RequestNode*)malloc(sizeof(RequestNode));
    node->print = RequestNode_print;
    node->Expressions = (ExpressionNode**)malloc(sizeof(ExpressionNode*));
    node->Expressions[0] = Expr;
    node->size = 1;
    return node;
}

extern void RequestNode_addExpr(RequestNode* node, ExpressionNode* Expr) {
    node->size++;
    node->Expressions = (ExpressionNode**)realloc(node->Expressions, node->size * sizeof(ExpressionNode*));
    node->Expressions[node->size - 1] = Expr;
}