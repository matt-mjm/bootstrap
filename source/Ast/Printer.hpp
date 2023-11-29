#pragma once
#include "Node.hpp"
#include "Visitor.hpp"

namespace Ast {

struct Printer : public Visitor {
    int32_t depth;
    Printer();

    void visit(ProgramNode &);
    void visit(IdentifierLiteral &);
    void visit(IntegerLiteral &);
    void visit(UnaryExpression &);
    void visit(BinaryExpression &);
    void visit(BlockStatement &);
    void visit(ReturnStatement &);
    void visit(Binding &);
    void visit(BindingList &);
    void visit(FunctionDeclaration &);
};

};
