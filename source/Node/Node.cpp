#include "Node.hpp"
#include "Visitor.hpp"

GenericNode::GenericNode(std::string_view label, const std::vector<Node *> children) :
    label{label}, children{children} {}
GenericNode::~GenericNode() {
    for (auto child : children) {
        delete child;
    }
}
void GenericNode::accept(Visitor &visitor) {
    visitor.visit(*this);
}

ListNode::ListNode(void) :
    nodes{} {}
ListNode::~ListNode() {
    for (auto child : nodes) {
        delete child;
    }
}
void ListNode::accept(Visitor &visitor) {
    visitor.visit(*this);
}
void ListNode::push(Node *node) {
    nodes.push_back(node);
}

ModifierNode::ModifierNode(std::string_view label, Node *child) :
    label{label}, child{child} {
}
ModifierNode::~ModifierNode() {
    delete child;
}
void ModifierNode::accept(Visitor &visitor) {
    visitor.visit(*this);
}

ProgramNode::ProgramNode(ListNode *declarations)
    : declarations{declarations} {}
ProgramNode::~ProgramNode() {
    delete declarations;
}
void ProgramNode::accept(Visitor &visitor) {
    visitor.visit(*this);
}

IdentifierLiteral::IdentifierLiteral(std::string_view identifier) :
    identifier{identifier} {}
IdentifierLiteral::~IdentifierLiteral() {
    // DOES NOTHING
}
void IdentifierLiteral::accept(Visitor &visitor) {
    visitor.visit(*this);
}

IntegerLiteral::IntegerLiteral(unsigned long long value) :
    value{value} {}
IntegerLiteral::~IntegerLiteral() {
    // DOES NOTHING
}
void IntegerLiteral::accept(Visitor &visitor) {
    visitor.visit(*this);
}

StringLiteral::StringLiteral(std::string_view raw) :
    value{} {
    value.reserve(raw.size());
    for (size_t i = 0; i < raw.size(); i++) {
        char ch = raw[i];
        if (ch == '\\') {
            char ch = raw[++i];
            switch (ch) {
                case 'n': value.push_back('\n'); break;
                default: break;
            }
        } else {
            value.push_back(ch);
        }
    }
}
StringLiteral::~StringLiteral() {
    // DOES NOTHING
}
void StringLiteral::accept(Visitor &visitor) {
    visitor.visit(*this);
}

FunctionExpression::FunctionExpression(Node *label, ListNode *args) :
    label{label}, args{args} {}
FunctionExpression::~FunctionExpression() {
    delete label;
    delete args;
}
void FunctionExpression::accept(Visitor &visitor) {
    visitor.visit(*this);
}

FunctionDeclaration::FunctionDeclaration(
        IdentifierLiteral *label, ListNode *args, Node *returnType, Node *body) :
    label{label}, args{args}, returnType{returnType}, body{body} {}
FunctionDeclaration::~FunctionDeclaration() {
    delete label;
    delete args;
    if (returnType) delete returnType;
    if (body) delete body;
}
void FunctionDeclaration::accept(Visitor &visitor) {
    visitor.visit(*this);
}

VariableDeclaration::VariableDeclaration(
        std::string mode, IdentifierLiteral *label, Node *type) :
    mode{mode}, label{label}, type{type} {}
VariableDeclaration::~VariableDeclaration() {
    delete label;
    if (type) delete type;
}
void VariableDeclaration::accept(Visitor &visitor) {
    visitor.visit(*this);
}
