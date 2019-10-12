#include <bits/stdc++.h>

using namespace std;

class Rational {
public:

    Rational(int numerator = 0, int denominator = 1) {
        if (denominator == 0)
            throw invalid_argument("error");
        int g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
        if (numerator < 0 && denominator < 0) {
            numerator = abs(numerator);
            denominator = abs(denominator);
        } else if (numerator >= 0 && denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
        num = numerator;
        denom = denominator;
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return denom;
    }

    bool operator==(const Rational &rhs) const {
        return this->num == rhs.num && this->denom == rhs.denom;
    }

    bool operator<(const Rational &rhs) const {
        int lhs_num = this->num * rhs.denom;
        int rhs_num = rhs.num * this->denom;
        return lhs_num < rhs_num;
    }

    Rational operator+(const Rational &rhs) const {
        int new_denom = this->denom * rhs.denom;
        int new_num = this->num * rhs.denom + rhs.num * this->denom;
        return Rational(new_num, new_denom);
    }

    Rational operator-(const Rational &rhs) const {
        int new_denom = this->denom * rhs.denom;
        int new_num = this->num * rhs.denom - rhs.num * this->denom;
        return Rational(new_num, new_denom);
    }

    Rational operator*(const Rational &rhs) const {
        int new_denom = this->denom * rhs.denom;
        int new_num = this->num * rhs.num;
        return Rational(new_num, new_denom);
    }

    Rational operator/(const Rational &rhs) const {
        if (rhs.num == 0)
            throw domain_error("error");
        return *this * Rational(rhs.denom, rhs.num);
    }


private:
    int num;
    int denom;

    int gcd(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
};

ostream &operator<<(ostream &stream, const Rational &rational) {
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

istream &operator>>(istream &stream, Rational &rational) {
    int numerator;
    int denominator;
    if (!stream)
        return stream;
    stream >> numerator;
    stream.ignore(1);
    if (!stream)
        return stream;
    stream >> denominator;
    rational = Rational(numerator, denominator);
    return stream;
}