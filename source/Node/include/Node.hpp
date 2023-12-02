#pragma once
#include <string>
#include <vector>

struct Visitor;
struct Node {
    virtual ~Node() = default;
    virtual void accept(Visitor &) = 0;
};

struct GenericNode : public Node {
    std::string label;
    std::vector<Node *> children;

    GenericNode(const std::string &label, const std::vector<Node *> children);
    ~GenericNode();
    void accept(Visitor &) override;
};
