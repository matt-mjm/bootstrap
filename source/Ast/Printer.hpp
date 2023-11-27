#pragma once
#include "Node.hpp"
#include "Visitor.hpp"

namespace Ast {

struct Printer : public Visitor {
    int32_t depth;
    Printer();

    void visit(Node &) override;
    void visit(IntegerNode &) override;
    void visit(UnaryNode &) override;
    void visit(BinaryNode &) override;
};

};
