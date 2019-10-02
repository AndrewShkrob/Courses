#include "node.h"

bool EmptyNode::Evaluate(const Date &d, const string &event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison &cmp, const Date &date) : cmp(cmp), date(date) {}

bool DateComparisonNode::Evaluate(const Date &d, const string &event) const {
    return Compare(d, date, cmp);
}

EventComparisonNode::EventComparisonNode(const Comparison &cmp, const string &event) : cmp(cmp), event(event) {}

bool EventComparisonNode::Evaluate(const Date &d, const string &e) const {
    return Compare(e, event, cmp);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &operation, const shared_ptr<Node> &left,
                                           const shared_ptr<Node> &right)
        : operation(operation), left(left), right(right) {}

bool LogicalOperationNode::Evaluate(const Date &d, const string &event) const {
    const bool leftEvaluation = left->Evaluate(d, event);
    const bool rightEvaluation = right->Evaluate(d, event);
    switch (operation) {
        case LogicalOperation::And:
            return leftEvaluation && rightEvaluation;
        case LogicalOperation::Or:
            return leftEvaluation || rightEvaluation;
        default:
            return false;
    }
}