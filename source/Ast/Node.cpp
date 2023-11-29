#include "Node.hpp"
#include "Visitor.hpp"

Ast::ProgramNode::ProgramNode() :
    statements{} {}
Ast::ProgramNode::~ProgramNode() {
    for (auto statement : statements) {
        delete statement;
    }
}
void Ast::ProgramNode::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::IdentifierLiteral::IdentifierLiteral(std::string string) :
    string{string} {}
Ast::IdentifierLiteral::~IdentifierLiteral() {
    // DOES NOTHING
}
void Ast::IdentifierLiteral::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::IntegerLiteral::IntegerLiteral(int32_t i32) :
    i32{i32} {}
Ast::IntegerLiteral::~IntegerLiteral() {
    // DOES NOTHING
}
void Ast::IntegerLiteral::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::BinaryExpression::BinaryExpression(
        Ast::Operation op, Ast::Expression *left, Ast::Expression *right) :
    op{op}, left{left}, right{right} {}
Ast::BinaryExpression::~BinaryExpression() {
    delete left;
    delete right;
}
void Ast::BinaryExpression::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::UnaryExpression::UnaryExpression(
        Ast::Operation op, Ast::Expression *child) :
    op{op}, child{child} {}
Ast::UnaryExpression::~UnaryExpression() {
    delete child;
}
void Ast::UnaryExpression::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::BlockStatement::BlockStatement(void) :
    statements{} {}
Ast::BlockStatement::~BlockStatement() {
    for (auto statement : statements) {
        delete statement;
    }
}
void Ast::BlockStatement::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::ReturnStatement::ReturnStatement(Ast::Expression *expr) :
    expr{expr} {}
Ast::ReturnStatement::~ReturnStatement() {
    delete expr;
}
void Ast::ReturnStatement::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::Binding::Binding(Ast::IdentifierLiteral *name, Ast::Expression *type) :
    name{name}, type{type} {}
Ast::Binding::~Binding() {
    delete name;
    delete type;
}
void Ast::Binding::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::BindingList::BindingList() :
    bindings{} {}
Ast::BindingList::~BindingList() {
    for (auto binding : bindings) {
        delete binding;
    }
}
void Ast::BindingList::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::FunctionDeclaration::FunctionDeclaration(
        Ast::IdentifierLiteral *name, BindingList *arguments, Expression *type, Statement *body) :
    name{name}, arguments{arguments}, type{type}, body{body} {}
Ast::FunctionDeclaration::~FunctionDeclaration() {
    delete name;
    delete body;
}
void Ast::FunctionDeclaration::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}
