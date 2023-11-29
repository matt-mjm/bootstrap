#pragma once
#include "Node.hpp"
#include "Visitor.hpp"

#include <llvm/Support/raw_ostream.h>

namespace Ast {

struct CodeGenerator : public Visitor {
    llvm::raw_ostream &outs;

    CodeGenerator(llvm::raw_ostream &);
    ~CodeGenerator();

    void visit(ProgramNode &);
    void visit(IdentifierLiteral &);
    void visit(IntegerLiteral &);
    void visit(UnaryExpression &);
    void visit(BinaryExpression &);
    void visit(BlockStatement &);
    void visit(ReturnStatement &);
    void visit(FunctionDeclaration &);
};

};
