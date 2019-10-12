#include <bits/stdc++.h>

using namespace std;

class Figure {
public:
    [[nodiscard]] virtual string Name() const = 0;

    [[nodiscard]] virtual double Perimeter() const = 0;

    [[nodiscard]] virtual double Area() const = 0;
};

class Rect : public Figure {
public:
    Rect(const int &width, const int &height) : width(width), height(height) {}

    [[nodiscard]] virtual string Name() const override {
        return "RECT";
    }

    [[nodiscard]] virtual double Perimeter() const override {
        return (width + height) * 2;
    }

    [[nodiscard]] virtual double Area() const override {
        return width * height;
    }

private:
    const int width;
    const int height;
};

class Triangle : public Figure {
public:
    Triangle(const int &a, const int &b, const int &c) : a(a), b(b), c(c) {}

    [[nodiscard]] virtual string Name() const override {
        return "TRIANGLE";
    }

    [[nodiscard]] virtual double Perimeter() const override {
        return a + b + c;
    }

    [[nodiscard]] virtual double Area() const override {
        double p = (a + b + c) / 2.;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

private:
    const int a;
    const int b;
    const int c;
};

class Circle : public Figure {
public:
    Circle(const int &radius) : radius(radius) {}

    [[nodiscard]] virtual string Name() const override {
        return "CIRCLE";
    }

    [[nodiscard]] virtual double Perimeter() const override {
        return 2. * 3.14 * radius;
    }

    [[nodiscard]] virtual double Area() const override {
        return 3.14 * pow(radius, 2);
    }

private:
    const int radius;
};

shared_ptr<Figure> CreateFigure(istringstream &is) {
    string type;
    is >> type;
    if (type == "RECT") {
        int width, height;
        is >> width >> height;
        return make_shared<Rect>(width, height);
    } else if (type == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else {
        int radius;
        is >> radius;
        return make_shared<Circle>(radius);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}