#pragma once
#include "Node.hpp"
#include "Visitor.hpp"

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>

#include <llvm/IR/Constant.h>
#include <llvm/IR/Value.h>

#include <llvm/Support/raw_ostream.h>

namespace Ast {

struct CodeGenerator : public Visitor {
    llvm::raw_ostream &outs;

    llvm::LLVMContext *context;
    llvm::Module *module;
    llvm::IRBuilder<> *builder;

    llvm::Function *currentFunction;
    llvm::BasicBlock *currentBlock;

    llvm::Value *valueReturn;
    llvm::Type *typeReturn;

    bool isTypeExpr;
    bool isExtern;

    CodeGenerator(llvm::raw_ostream &);
    ~CodeGenerator();

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
