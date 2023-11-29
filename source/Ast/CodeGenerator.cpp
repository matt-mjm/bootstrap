#include "CodeGenerator.hpp"

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>

#include <llvm/IR/Constant.h>
#include <llvm/IR/Value.h>

Ast::CodeGenerator::CodeGenerator(llvm::raw_ostream &outs) :
    outs{outs} {
    // TODO
}
Ast::CodeGenerator::~CodeGenerator() {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::ProgramNode &) {
    llvm::LLVMContext *context = new llvm::LLVMContext();
    llvm::Module *module = new llvm::Module("main", *context);
    llvm::IRBuilder<> *builder = new llvm::IRBuilder<>(*context);

    llvm::FunctionType *funcType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*context), false);
    llvm::Function *func = llvm::Function::Create(funcType,
            llvm::GlobalValue::ExternalLinkage, "main", *module);
    llvm::BasicBlock *body = llvm::BasicBlock::Create(
            *context, "entry", func);

    builder->SetInsertPoint(body);

    llvm::Constant *x = llvm::ConstantInt::getSigned(
            llvm::Type::getInt32Ty(*context), 5);
    llvm::Constant *y = llvm::ConstantInt::getSigned(
            llvm::Type::getInt32Ty(*context), -6);
    llvm::Value *add = builder->CreateAdd(x, y);

    std::vector<llvm::Type *> printfArgs = {
        llvm::Type::getInt8PtrTy(*context)
    };
    llvm::FunctionType *printfType = llvm::FunctionType::get(
            builder->getInt32Ty(), printfArgs, true);
    llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", *module);

    std::vector<llvm::Value *> printArgs = {
        builder->CreateGlobalStringPtr("%d\n"),
        add
    };
    builder->CreateCall(module->getFunction("printf"), printArgs);

    builder->CreateRetVoid();
    module->print(outs, nullptr);
}

void Ast::CodeGenerator::visit(Ast::IdentifierLiteral &) {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::IntegerLiteral &) {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::UnaryExpression &) {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::BinaryExpression &) {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::BlockStatement &) {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::ReturnStatement &) {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::FunctionDeclaration &) {
    // TODO
}
