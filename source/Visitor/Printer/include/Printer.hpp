#pragma once
#include "Node.hpp"
#include "Visitor.hpp"

struct Printer : public Visitor {
    int depth;

    Printer(void);
    ~Printer();
    void printDepth(void);

    void visit(GenericNode &) override;
};
