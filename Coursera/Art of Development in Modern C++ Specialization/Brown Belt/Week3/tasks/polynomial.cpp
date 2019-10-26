#include "test_runner.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class Polynomial {
private:
    std::vector<T> coeffs_ = {0};

    void Shrink() {
        while (coeffs_.size() > 1 && coeffs_.back() == 0) {
            coeffs_.pop_back();
        }
    }

public:
    Polynomial() = default;

    Polynomial(vector<T> coeffs) : coeffs_(std::move(coeffs)) {
        Shrink();
    }

    template<typename Iterator>
    Polynomial(Iterator first, Iterator last) : coeffs_(first, last) {
        Shrink();
    }

    class Proxy {
    public:
        Proxy(size_t degree, Polynomial &poly)
                : degree(degree),
                  polynomial(poly) {}

        Proxy &operator=(T value) {
            if (polynomial.Degree() < degree)
                polynomial.coeffs_.resize(degree + 1);
            polynomial.coeffs_[degree] = value;
            polynomial.Shrink();
            return *this;
        }

        operator T() const {
            return std::as_const(polynomial)[degree];
        }

    private:
        size_t degree;
        Polynomial &polynomial;
    };

    bool operator==(const Polynomial &other) const {
        return coeffs_ == other.coeffs_;
    }

    bool operator!=(const Polynomial &other) const {
        return !operator==(other);
    }

    int Degree() const {
        return coeffs_.size() - 1;
    }

    Polynomial &operator+=(const Polynomial &r) {
        if (r.coeffs_.size() > coeffs_.size()) {
            coeffs_.resize(r.coeffs_.size());
        }
        for (size_t i = 0; i != r.coeffs_.size(); ++i) {
            coeffs_[i] += r.coeffs_[i];
        }
        Shrink();
        return *this;
    }

    Polynomial &operator-=(const Polynomial &r) {
        if (r.coeffs_.size() > coeffs_.size()) {
            coeffs_.resize(r.coeffs_.size());
        }
        for (size_t i = 0; i != r.coeffs_.size(); ++i) {
            coeffs_[i] -= r.coeffs_[i];
        }
        Shrink();
        return *this;
    }

    T operator[](size_t degree) const {
        return degree < coeffs_.size() ? coeffs_[degree] : 0;
    }

    Proxy operator[](size_t degree) {
        return {degree, *this};
    }

    T operator()(const T &x) const {
        T res = 0;
        for (auto it = coeffs_.rbegin(); it != coeffs_.rend(); ++it) {
            res *= x;
            res += *it;
        }
        return res;
    }

    using const_iterator = typename std::vector<T>::const_iterator;

    const_iterator begin() const {
        return coeffs_.cbegin();
    }

    const_iterator end() const {
        return coeffs_.cend();
    }
};

template<typename T>
Polynomial<T> operator+(Polynomial<T> lhs, const Polynomial<T> &rhs) {
    lhs += rhs;
    return lhs;
}

template<typename T>
Polynomial<T> operator-(Polynomial<T> lhs, const Polynomial<T> &rhs) {
    lhs -= rhs;
    return lhs;
}