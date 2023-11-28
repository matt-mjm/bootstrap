#pragma once
#include "Node.hpp"

namespace Ast {

struct Visitor {
    virtual ~Visitor() = default;

    virtual void operator()(Node &);
    virtual void visit(ProgramNode &) = 0;
    virtual void visit(IdentifierLiteral &) = 0;
    virtual void visit(IntegerLiteral &) = 0;
    virtual void visit(UnaryExpression &) = 0;
    virtual void visit(BinaryExpression &) = 0;
    virtual void visit(BlockStatement &) = 0;
    virtual void visit(ReturnStatement &) = 0;
    virtual void visit(FunctionDeclaration &) = 0;
};

};
