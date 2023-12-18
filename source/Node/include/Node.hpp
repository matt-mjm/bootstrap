#pragma once
#include <vector>
#include <string>
#include <string_view>

struct Visitor;
struct Node {
    virtual ~Node() = default;
    virtual void accept(Visitor &) = 0;
};

struct GenericNode : public Node {
    std::string label;
    std::vector<Node *> children;

    GenericNode(std::string_view, const std::vector<Node *>);
    ~GenericNode();
    void accept(Visitor &) override;
};

struct ListNode : public Node {
    std::vector<Node *> nodes;

    ListNode(void);
    ~ListNode();
    void accept(Visitor &) override;

    void push(Node *);
};

struct ModifierNode : public Node {
    std::string label;
    Node *child;

    ModifierNode(std::string_view, Node *);
    ~ModifierNode();
    void accept(Visitor &);
};

struct ProgramNode : public Node {
    ListNode *declarations;

    ProgramNode(ListNode *);
    ~ProgramNode();
    void accept(Visitor &);
};


struct IdentifierLiteral : public Node {
    std::string identifier;

    IdentifierLiteral(std::string_view);
    ~IdentifierLiteral();
    void accept(Visitor &) override;
};

struct IntegerLiteral : public Node {
    unsigned long long value;

    IntegerLiteral(unsigned long long);
    ~IntegerLiteral();
    void accept(Visitor &) override;
};

struct StringLiteral : public Node {
    std::string value;

    StringLiteral(std::string_view);
    ~StringLiteral();
    void accept(Visitor &) override;
};

struct FunctionExpression : public Node {
    Node *label;
    ListNode *args;

    FunctionExpression(Node *, ListNode *);
    ~FunctionExpression();
    void accept(Visitor &) override;
};

struct FunctionDeclaration : public Node {
    IdentifierLiteral *label;
    ListNode *args;
    Node *returnType;
    Node *body;

    FunctionDeclaration(IdentifierLiteral *, ListNode *, Node *, Node *);
    ~FunctionDeclaration();
    void accept(Visitor &) override;
};

struct VariableDeclaration : public Node {
    std::string mode;
    IdentifierLiteral *label;
    Node *type;

    VariableDeclaration(std::string, IdentifierLiteral *, Node *);
    ~VariableDeclaration();
    void accept(Visitor &);
};
