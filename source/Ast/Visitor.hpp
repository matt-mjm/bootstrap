#pragma once
#include "Node.hpp"

namespace Ast {

struct Visitor {
    virtual ~Visitor() = default;

    virtual void operator()(Node &);
    virtual void visit(Node &) = 0;
    virtual void visit(IntegerNode &) = 0;
    virtual void visit(UnaryNode &) = 0;
    virtual void visit(BinaryNode &) = 0;
};

};
