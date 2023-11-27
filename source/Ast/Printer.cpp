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

void Ast::Printer::visit(Node &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    std::cout << "<Unknown Node>" << std::endl;
}

void Ast::Printer::visit(IntegerNode &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    std::cout << "Integer " << node.i32 << std::endl;
}

void Ast::Printer::visit(UnaryNode &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    auto opString = OPERATION_STRINGS.find(node.op);
    std::cout << "Unary Operation " << (opString != OPERATION_STRINGS.end() ?
        opString->second : "<Unknown Operation>") << std::endl;
    depth += 2;
    node.left->accept(*this);
    depth -= 2;
}

void Ast::Printer::visit(BinaryNode &node) {
    for (int32_t i = 0; i < depth; i++) std::cout << " ";
    auto opString = OPERATION_STRINGS.find(node.op);
    std::cout << "Binary Operation " << (opString != OPERATION_STRINGS.end() ?
        opString->second : "<Unknown Operation>") << std::endl;
    depth += 2;
    node.left->accept(*this);
    node.right->accept(*this);
    depth -= 2;
}
