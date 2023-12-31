#pragma once
#include "Node.hpp"

struct Visitor {
    virtual void visit(GenericNode &) = 0;
    virtual void visit(ListNode &) = 0;
    virtual void visit(ModifierNode &) = 0;
    virtual void visit(ProgramNode &) = 0;
    virtual void visit(IdentifierLiteral &) = 0;
    virtual void visit(IntegerLiteral &) = 0;
    virtual void visit(StringLiteral &) = 0;
    virtual void visit(FunctionExpression &) = 0;
    virtual void visit(FunctionDeclaration &) = 0;
    virtual void visit(VariableDeclaration &) = 0;
};
