#ifndef C___YELLOW_BELT_NODE_H
#define C___YELLOW_BELT_NODE_H

#include <memory>
#include "date.h"

using std::shared_ptr;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date &d, const string &event) const = 0;
};

class EmptyNode : public Node {
public:
    EmptyNode() = default;

    bool Evaluate(const Date &d, const string &event) const override;
};

class ComparisonNode : public Node {
protected:
    template<class T>
    bool static Compare(const T &a, const T &b, const Comparison &cmp) {
        switch (cmp) {
            case Comparison::Less:
                return a < b;
            case Comparison::LessOrEqual:
                return a <= b;
            case Comparison::Greater:
                return a > b;
            case Comparison::GreaterOrEqual:
                return a >= b;
            case Comparison::Equal:
                return a == b;
            case Comparison::NotEqual:
                return a != b;
            default:
                return false;
        }
    }
};

class DateComparisonNode : public ComparisonNode {
public:
    DateComparisonNode(const Comparison &cmp, const Date &d);

    bool Evaluate(const Date &d, const string &event) const override;

private:
    const Comparison cmp;
    const Date date;
};

class EventComparisonNode : public ComparisonNode {
public:
    EventComparisonNode(const Comparison &cmp, const string &event);
    bool Evaluate(const Date &d, const string &event) const override ;

private:
    const Comparison cmp;
    const string event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &operation, const shared_ptr<Node> &left, const shared_ptr<Node> &right);
    bool Evaluate(const Date &d, const string &event) const override ;

private:
    const LogicalOperation operation;
    const shared_ptr<Node> left;
    const shared_ptr<Node> right;
};

#endif //C___YELLOW_BELT_NODE_H
