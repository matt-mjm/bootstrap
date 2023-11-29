#include "CodeGenerator.hpp"

Ast::CodeGenerator::CodeGenerator(llvm::raw_ostream &outs) :
    outs{outs}, context{nullptr}, module{nullptr},
    currentFunction{nullptr}, currentBlock{nullptr},
    valueReturn{nullptr}, typeReturn{nullptr},
    isTypeExpr{false}, isExtern{false} {
    // TODO
}
Ast::CodeGenerator::~CodeGenerator() {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::ProgramNode &node) {
    /*
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
    */

    this->context = new llvm::LLVMContext();
    this->module = new llvm::Module("main", *context);
    this->builder = new llvm::IRBuilder<>(*context);

    for (auto statement : node.statements) {
        statement->accept(*this);
    }

    this->module->print(this->outs, nullptr);
}

static llvm::Type *getTypeFromName(llvm::LLVMContext &context, std::string name) {
    if (name == "i32") {
        return llvm::Type::getInt32Ty(context);
    } else {
        return llvm::Type::getVoidTy(context);
    }
}

void Ast::CodeGenerator::visit(Ast::IdentifierLiteral &node) {
    if (isTypeExpr) {
        typeReturn = getTypeFromName(*this->context, node.string);
    } else {
        // TODO
    }
}

void Ast::CodeGenerator::visit(Ast::IntegerLiteral &node) {
    this->valueReturn = llvm::ConstantInt::getSigned(
            llvm::Type::getInt32Ty(*context), node.i32);
}

static llvm::Value *getExprFromOperator(llvm::IRBuilder<> *builder,
        Ast::Operation op, llvm::Value *left, llvm::Value *right) {
    switch (op) {
        case Ast::Operation::NONE: return nullptr;
        case Ast::Operation::ADD: return builder->CreateAdd(left, right);
        case Ast::Operation::SUBTRACT: return builder->CreateSub(left, right);
        case Ast::Operation::MULTIPLY: return builder->CreateMul(left, right);
        case Ast::Operation::DIVIDE: return builder->CreateSDiv(left, right);
        default: return nullptr;
    }
}

void Ast::CodeGenerator::visit(Ast::UnaryExpression &node) {
    llvm::Value *left = llvm::ConstantInt::getSigned(
            llvm::Type::getInt32Ty(*context), 0);
    node.child->accept(*this);
    llvm::Value *right = this->valueReturn;
    this->valueReturn = getExprFromOperator(this->builder, node.op, left, right);
}

void Ast::CodeGenerator::visit(Ast::BinaryExpression &node) {
    node.left->accept(*this);
    llvm::Value *left = this->valueReturn;
    node.right->accept(*this);
    llvm::Value *right = this->valueReturn;
    this->valueReturn = getExprFromOperator(this->builder, node.op, left, right);
}

void Ast::CodeGenerator::visit(Ast::BlockStatement &node) {
    this->currentBlock = llvm::BasicBlock::Create(
            *context, "entry", this->currentFunction);
    this->builder->SetInsertPoint(this->currentBlock);

    for (auto statement : node.statements) {
        statement->accept(*this);
    }
}

void Ast::CodeGenerator::visit(Ast::ReturnStatement &node) {
    node.expr->accept(*this);
    this->builder->CreateRet(this->valueReturn);
}

void Ast::CodeGenerator::visit(Ast::Binding &) {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::BindingList &) {
    // TODO
}

void Ast::CodeGenerator::visit(Ast::FunctionDeclaration &node) {
    isTypeExpr = true;
    node.type->accept(*this);
    isTypeExpr = false;
    llvm::Type *returnType = this->typeReturn;

    llvm::FunctionType *funcType = llvm::FunctionType::get(
            returnType, false);
    this->currentFunction = llvm::Function::Create(funcType,
            llvm::GlobalValue::ExternalLinkage, "main", *module);

    node.body->accept(*this);
}
