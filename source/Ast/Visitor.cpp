#include "Visitor.hpp"

void Ast::Visitor::operator()(Node &node) {
    node.accept(*this);
}
