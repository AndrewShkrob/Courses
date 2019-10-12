#include <bits/stdc++.h>

using namespace std;

class FunctionPart {
public:
    FunctionPart(char operation, double value) {
        this->operation = operation;
        this->value = value;
    }

    double Apply(double source_value) const {
        switch (operation) {
            case '+':
                return source_value + value;
            case '-':
                return source_value - value;
            case '*':
                return source_value * value;
            case '/':
                return source_value / value;
        }
    }

    void Invert() {
        if (operation == '+' || operation == '-')
            operation == '+' ? operation = '-' : operation = '+';
        else
            operation == '*' ? operation = '/' : operation = '*';
    }

private:
    char operation;
    double value;
};

class Function {
public:
    void AddPart(char c, double value) {
        parts.emplace_back(c, value);
    }

    double Apply(double value) const {
        for (const FunctionPart &part : parts) {
            value = part.Apply(value);
        }
        return value;
    }

    void Invert() {
        for (auto &part : parts) {
            part.Invert();
        }
        reverse(parts.begin(), parts.end());
    }

private:
    vector<FunctionPart> parts;
};

int main() {
    cout << endl;
}