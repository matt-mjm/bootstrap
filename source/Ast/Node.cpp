#include "Node.hpp"
#include "Visitor.hpp"

Ast::IntegerNode::IntegerNode(int32_t i32) :
    i32{i32} {}
Ast::IntegerNode::~IntegerNode() {
    // DOES NOTHING
}
void Ast::IntegerNode::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::BinaryNode::BinaryNode(Ast::Operation op, Ast::Node *left, Ast::Node *right) :
    op{op}, left{left}, right{right} {}
Ast::BinaryNode::~BinaryNode() {
    delete left;
    delete right;
}
void Ast::BinaryNode::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}

Ast::UnaryNode::UnaryNode(Ast::Operation op, Ast::Node *left) :
    op{op}, left{left} {}
Ast::UnaryNode::~UnaryNode() {
    delete left;
}
void Ast::UnaryNode::accept(Ast::Visitor &visitor) {
    visitor.visit(*this);
}
