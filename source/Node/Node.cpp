#include "Node.hpp"
#include "Visitor.hpp"

GenericNode::GenericNode(const std::string &label, const std::vector<Node *> children) :
    label{label}, children{children} {}

GenericNode::~GenericNode() {
    for (auto child : children) {
        delete child;
    }
}
void GenericNode::accept(Visitor &visitor) {
    visitor.visit(*this);
}
