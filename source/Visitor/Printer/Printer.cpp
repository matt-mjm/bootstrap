#include "Printer.hpp"

#include <iostream>

Printer::Printer(void) :
    depth{0} {}
Printer::~Printer() {
    // TODO
}
void Printer::printDepth(void) {
    for (int i = 0; i < depth; i++) {
        std::cout << " ";
    }
}

void Printer::visit(GenericNode &node) {
    printDepth();
    std::cout << node.label << std::endl;
    depth += 2;
    for (auto child : node.children) {
        child->accept(*this);
    }
    depth -= 2;
}

void Printer::visit(ListNode &node) {
    for (auto child : node.nodes) {
        child->accept(*this);
    }
}

void Printer::visit(IdentifierLiteral &node) {
    printDepth();
    std::cout << "Identifier " << node.identifier << std::endl;
}

void Printer::visit(IntegerLiteral &node) {
    printDepth();
    std::cout << "Integer " << node.value << std::endl;
}

void Printer::visit(StringLiteral &node) {
    printDepth();
    std::cout << "String " << node.value << std::endl;
}

void Printer::visit(FunctionExpression &node) {
    printDepth();
    std::cout << "Function" << std::endl;
    depth += 2;
    node.label->accept(*this);
    node.args->accept(*this);
    depth -= 2;
}

void Printer::visit(FunctionDeclaration &node) {
    printDepth();
    std::cout << "Function Declaration" << std::endl;
    depth += 2;
    node.label->accept(*this);
    node.args->accept(*this);
    node.returnType->accept(*this);
    node.body->accept(*this);
    depth -= 2;
}

void Printer::visit(VariableDeclaration &node) {
    printDepth();
    std::cout << "Declaration " << node.mode << std::endl;
    depth += 2;
    node.label->accept(*this);
    if (node.type) node.type->accept(*this);
    depth -= 2;
}

void Printer::visit(ModifiedStatement &node) {
    printDepth();
    std::cout << "Statement " << node.label << std::endl;
    depth += 2;
    node.child->accept(*this);
    depth -= 2;
}
