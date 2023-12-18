#include "CodeGenerator.hpp"

/**
 * ==== Constructors ====
 */

CodeGenerator::CodeGenerator(llvm::raw_ostream &outs)
    : outs{outs}, context{nullptr}, module{nullptr},
    currentFunction{nullptr}, currentBlock{nullptr},
    valueReturn{nullptr}, typeReturn{nullptr},
    isLocal{false}, isValueExpr{false}, isTypeExpr{false}, isExtern{false}, isVariable{false} {
    // TODO
}
CodeGenerator::~CodeGenerator() {
    // TODO
}

/**
 * ==== Helper Functions ====
 */

static llvm::Type *getTypeFromSymbol(llvm::LLVMContext &context, std::string symbol) {
    if (symbol == "i64") {
        return llvm::Type::getInt64Ty(context);
    } else if (symbol == "i32") {
        return llvm::Type::getInt32Ty(context);
    } else if (symbol == "i16") {
        return llvm::Type::getInt16Ty(context);
    } else if (symbol == "i8") {
        return llvm::Type::getInt8Ty(context);
    } else {
        return llvm::Type::getVoidTy(context);
    }
}

/**
 * ==== Visitors ====
 */

void CodeGenerator::visit(GenericNode &) {
    // TODO
}

void CodeGenerator::visit(ListNode &node) {
    if (this->currentFunction != nullptr) {
        this->currentBlock = llvm::BasicBlock::Create(
            *this->context, "entry", this->currentFunction);
        this->builder->SetInsertPoint(this->currentBlock);
    }

    for (Node *child : node.nodes) {
        child->accept(*this);
    }

    if (this->currentFunction != nullptr) {
        this->currentBlock = nullptr;
    }
}

void CodeGenerator::visit(ModifierNode &node) {
    if (node.label == "__extern__") {
        bool prevExtern = isExtern;
        isExtern = true;
        node.child->accept(*this);
        isExtern = prevExtern;
    } else if (node.label == "__return__") {
        bool prevValueExpr = isValueExpr;
        isValueExpr = true;
        node.child->accept(*this);
        this->builder->CreateRet(this->valueReturn);
        isValueExpr = prevValueExpr;
    } else if (node.label == "__variable__") {
        isVariable = true;
    } else {
        // TODO
        node.child->accept(*this);
    }
}

void CodeGenerator::visit(ProgramNode &node) {
    this->context = new llvm::LLVMContext();
    this->module = new llvm::Module("main", *this->context);
    this->builder = new llvm::IRBuilder<>(*this->context);

    node.declarations->accept(*this);
    this->module->print(this->outs, nullptr);
}

void CodeGenerator::visit(IdentifierLiteral &node) {
    if (isTypeExpr) {
        typeReturn = getTypeFromSymbol(*this->context, node.identifier);
    } else {
        // TODO
    }
}

void CodeGenerator::visit(IntegerLiteral &node) {
    this->valueReturn = llvm::ConstantInt::get(
            llvm::Type::getInt32Ty(*this->context), node.value);
}

void CodeGenerator::visit(StringLiteral &node) {
    valueReturn = this->builder->CreateGlobalString(node.value);
}

void CodeGenerator::visit(FunctionExpression &node) {
    // TODO FIX

    std::vector<llvm::Value *> args;
    for (auto child : node.args->nodes) {
        child->accept(*this);
        args.push_back(this->valueReturn);
    }

    std::string label = ((IdentifierLiteral *)node.label)->identifier;
    if (label == "__add__") {
        this->valueReturn = this->builder->CreateAdd(args[0], args[1]);
    } else if (label == "__sub__") {
        this->valueReturn = this->builder->CreateSub(args[0], args[1]);
    } else if (label == "__negate__") {
        llvm::Value *left = llvm::ConstantInt::get(
            llvm::Type::getInt64Ty(*context), 0);
        this->valueReturn = this->builder->CreateSub(left, args[0]);
    } else if (label == "__mul__") {
        this->valueReturn = this->builder->CreateMul(args[0], args[1]);
    } else if (label == "__div__") {
        this->valueReturn = this->builder->CreateSDiv(args[0], args[1]);
    } else if (label == "__deref__") {
        if (isTypeExpr) {
            // node.child->accept(*this);
            // llvm::Type *child = this->typeReturn;
            this->typeReturn = llvm::PointerType::get(*this->context, 0);
        } else {
            // TODO
        }
    } else {
        builder->CreateCall(module->getFunction(label), args);
    }
}

void CodeGenerator::visit(FunctionDeclaration &node) {
    bool prevTypeExpr = isTypeExpr;
    isTypeExpr = true;

    llvm::Type *returnType = nullptr;
    if (node.returnType) {
        node.returnType->accept(*this);
        returnType = this->typeReturn;
    } else {
        returnType = llvm::Type::getVoidTy(*this->context);
    }

    bool prevVariable = isVariable;
    std::vector<llvm::Type *> args;
    for (auto child : node.args->nodes) {
        this->typeReturn = nullptr;
        child->accept(*this);
        if (this->typeReturn) args.push_back(this->typeReturn);
    }

    llvm::FunctionType *functionType = llvm::FunctionType::get(
            returnType, args, isVariable);
    this->currentFunction = llvm::Function::Create(functionType, isExtern ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage,
        node.label->identifier, *this->module);

    isVariable = prevVariable;
    isTypeExpr = prevTypeExpr;

    if (node.body) {
        node.body->accept(*this);
    }

    this->currentFunction = nullptr;
}

void CodeGenerator::visit(VariableDeclaration &node) {
    if (isTypeExpr) {
        if (node.type) {
            node.type->accept(*this);
        } else {
            this->typeReturn = llvm::Type::getVoidTy(*this->context);
        }
    } else {
        // TODO
    }
}
