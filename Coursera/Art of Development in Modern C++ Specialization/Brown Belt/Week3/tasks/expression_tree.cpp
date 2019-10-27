#include "Common.h"

#include <sstream>

using namespace std;

namespace expression {
    class Value : public Expression {
    public:
        Value(int num) : number(num) {}

        virtual int Evaluate() const {
            return number;
        }

        std::string ToString() const {
            return to_string(number);
        }

    private:
        int number;
    };

    class Sum : public Expression {
    public:
        Sum(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(move(lhs)), rhs(move(rhs)) {}

        virtual int Evaluate() const {
            return lhs->Evaluate() + rhs->Evaluate();
        }

        std::string ToString() const {
            ostringstream os;
            os << '(' << lhs->ToString() << ")+(" << rhs->ToString() << ')';
            return os.str();
        }

    private:
        ExpressionPtr lhs;
        ExpressionPtr rhs;
    };

    class Product : public Expression {
    public:
        Product(ExpressionPtr lhs, ExpressionPtr rhs) : lhs(move(lhs)), rhs(move(rhs)) {}

        virtual int Evaluate() const {
            return lhs->Evaluate() * rhs->Evaluate();
        }

        std::string ToString() const {
            ostringstream os;
            os << '(' << lhs->ToString() << ")*(" << rhs->ToString() << ')';
            return os.str();
        }

    private:
        ExpressionPtr lhs;
        ExpressionPtr rhs;
    };
}

ExpressionPtr Value(int value) {
    return make_unique<expression::Value>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<expression::Sum>(move(left), move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<expression::Product>(move(left), move(right));
}
