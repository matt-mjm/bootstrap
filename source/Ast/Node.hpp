#pragma once
#include <cstdint>

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

struct IntegerNode : public Node {
    int32_t i32;

    IntegerNode(int32_t);
    ~IntegerNode();
    void accept(Visitor &) override;
};

struct UnaryNode : public Node {
    Operation op;
    Node *left;

    UnaryNode(Operation op, Node *left);
    ~UnaryNode();
    void accept(Visitor &) override;
};

struct BinaryNode : public Node {
    Operation op;
    Node *left;
    Node *right;

    BinaryNode(Operation op, Node *left, Node *right);
    ~BinaryNode();
    void accept(Visitor &) override;
};

};
