#pragma once
#include "Node.hpp"

struct Visitor {
    virtual void visit(GenericNode &) = 0;
};
