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

struct CodeGenerator : public Visitor {
    llvm::raw_ostream &outs;

    llvm::LLVMContext *context;
    llvm::Module *module;
    llvm::IRBuilder<> *builder;

    llvm::Function *currentFunction;
    llvm::BasicBlock *currentBlock;

    llvm::Value *valueReturn;
    llvm::Type *typeReturn;

    bool isLocal;
    bool isValueExpr;
    bool isTypeExpr;
    bool isExtern;
    bool isVariable;

    CodeGenerator(llvm::raw_ostream &);
    ~CodeGenerator();

    void visit(GenericNode &) override;
    void visit(ListNode &) override;
    void visit(ModifierNode &) override;
    void visit(ProgramNode &) override;
    void visit(IdentifierLiteral &) override;
    void visit(IntegerLiteral &) override;
    void visit(StringLiteral &) override;
    void visit(FunctionExpression &) override;
    void visit(FunctionDeclaration &) override;
    void visit(VariableDeclaration &) override;
};
