#include "Node.hpp"
#include "Visitor.hpp"

Ast::ProgramNode::ProgramNode() :
    statements{} {}
Ast::ProgramNode::~ProgramNode() {
    for (auto child : statements) {
        delete child;
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
        Ast::Operation op, Ast::Expression *left) :
    op{op}, left{left} {}
Ast::UnaryExpression::~UnaryExpression() {
    delete left;
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

Ast::FunctionDeclaration::FunctionDeclaration(Ast::IdentifierLiteral *name, Statement *body) :
    name{name}, body{body} {}
Ast::FunctionDeclaration::~FunctionDeclaration() {
    delete name;
    delete body;
}
void Ast::FunctionDeclaration::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}
