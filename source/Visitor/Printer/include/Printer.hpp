#pragma once
#include "Node.hpp"
#include "Visitor.hpp"

struct Printer : public Visitor {
    int depth;

    Printer(void);
    ~Printer();
    void printDepth(void);

    void visit(GenericNode &) override;
    void visit(ListNode &) override;
    void visit(IdentifierLiteral &) override;
    void visit(IntegerLiteral &) override;
    void visit(StringLiteral &) override;
    void visit(FunctionExpression &) override;
    void visit(ModifiedStatement &) override;
};
