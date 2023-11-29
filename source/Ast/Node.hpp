#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace Ast {

enum class Operation {
    NONE,
    ADD, SUBTRACT, MULTIPLY, DIVIDE
};

struct Visitor;
struct Node {
    virtual ~Node() = default;
    virtual void accept(Visitor &) = 0;
};

struct Statement : public Node {
    virtual ~Statement() = default;
    virtual void accept(Visitor &) = 0;
};

struct Expression : public Node {
    virtual ~Expression() = default;
    virtual void accept(Visitor &) = 0;
};

struct Literal : public Expression {
    virtual ~Literal() = default;
    virtual void accept(Visitor &) = 0;
};

struct ProgramNode : public Node {
    std::vector<Statement *> statements;

    ProgramNode();
    ~ProgramNode();
    void accept(Visitor &) override;
};

struct IdentifierLiteral : public Literal {
    std::string string;

    IdentifierLiteral(std::string);
    ~IdentifierLiteral();
    void accept(Visitor &) override;
};

struct IntegerLiteral : public Literal {
    int32_t i32;

    IntegerLiteral(int32_t);
    ~IntegerLiteral();
    void accept(Visitor &) override;
};

struct UnaryExpression : public Expression {
    Operation op;
    Expression *child;

    UnaryExpression(Operation, Expression *);
    ~UnaryExpression();
    void accept(Visitor &) override;
};

struct BinaryExpression : public Expression {
    Operation op;
    Expression *left;
    Expression *right;

    BinaryExpression(Operation, Expression *, Expression *);
    ~BinaryExpression();
    void accept(Visitor &) override;
};

struct BlockStatement : public Statement {
    std::vector<Statement *> statements;

    BlockStatement();
    ~BlockStatement();
    void accept(Visitor &);
};

struct ReturnStatement : public Statement {
    Expression *expr;

    ReturnStatement(Expression *);
    ~ReturnStatement();
    void accept(Visitor &);
};

struct Binding : public Expression {
    IdentifierLiteral *name;
    Expression *type;

    Binding(IdentifierLiteral *, Expression *);
    ~Binding();
    void accept(Visitor &);
};

struct BindingList : public Expression {
    std::vector<Binding *> bindings;

    BindingList();
    ~BindingList();
    void accept(Visitor &);
};

struct FunctionDeclaration : public Statement {
    IdentifierLiteral *name;
    BindingList *arguments;
    Expression *type;
    Statement *body;

    FunctionDeclaration(IdentifierLiteral *, BindingList *, Expression *, Statement *);
    ~FunctionDeclaration();
    void accept(Visitor &);
};

};
