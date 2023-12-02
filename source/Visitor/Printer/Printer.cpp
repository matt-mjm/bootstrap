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
