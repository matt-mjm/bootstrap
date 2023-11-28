#include "Printer.hpp"

#include <iostream>
#include <string>
#include <map>

static const std::map<Ast::Operation, std::string> OPERATION_STRINGS = {
    { Ast::Operation::ADD, "+" },
    { Ast::Operation::SUBTRACT, "-" },
    { Ast::Operation::MULTIPLY, "*" },
    { Ast::Operation::DIVIDE, "/" },
};

Ast::Printer::Printer() :
    depth{0} {}

void Ast::Printer::visit(Ast::ProgramNode &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    std::cout << "Program" << std::endl;
    depth += 2;
    for (auto child : node.statements) {
        child->accept(*this);
    }
    depth -= 2;
}

void Ast::Printer::visit(Ast::IdentifierLiteral &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    std::cout << "Identifier " << node.string << std::endl;
}

void Ast::Printer::visit(Ast::IntegerLiteral &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    std::cout << "Integer " << node.i32 << std::endl;
}
void Ast::Printer::visit(Ast::UnaryExpression &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    auto opString = OPERATION_STRINGS.find(node.op);
    std::cout << "Unary Operation " << (opString != OPERATION_STRINGS.end() ?
        opString->second : "<Unknown Operation>") << std::endl;
    depth += 2;
    node.left->accept(*this);
    depth -= 2;
}

void Ast::Printer::visit(Ast::BinaryExpression &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    auto opString = OPERATION_STRINGS.find(node.op);
    std::cout << "Binary Operation " << (opString != OPERATION_STRINGS.end() ?
        opString->second : "<Unknown Operation>") << std::endl;
    depth += 2;
    node.left->accept(*this);
    node.right->accept(*this);
    depth -= 2;
}

void Ast::Printer::visit(Ast::BlockStatement &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    std::cout << "Block" << std::endl;
    depth += 2;
    for (auto child : node.statements) {
        child->accept(*this);
    }
    depth -= 2;
}

void Ast::Printer::visit(Ast::ReturnStatement &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    std::cout << "Return" << std::endl;
    depth += 2;
    node.expr->accept(*this);
    depth -= 2;
}

void Ast::Printer::visit(Ast::FunctionDeclaration &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    std::cout << "Function Declaration" << std::endl;
    depth += 2;
    node.name->accept(*this);
    node.body->accept(*this);
    depth -= 2;
}
