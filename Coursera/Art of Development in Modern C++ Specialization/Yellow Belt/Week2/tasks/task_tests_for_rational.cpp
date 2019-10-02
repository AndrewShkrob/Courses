#include <bits/stdc++.h>

using namespace std;


template<class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u,
                 const string &hint) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " hint: " << hint;
        throw runtime_error(os.str());
    }
}

inline void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template<class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (runtime_error &e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

void Tests() {
    {
        Rational r;
        AssertEqual(r.Numerator(), 0, "empty num = 0");
        AssertEqual(r.Denominator(), 1, "empty denom = 1");
    }
    {
        Rational r = {2, 4};
        AssertEqual(r.Numerator(), 1, "2/4 = 1/2 Num");
        AssertEqual(r.Denominator(), 2, "2/4 = 1/2 Denom");
    }
    {
        Rational r = {-5, 1};
        Assert(r.Numerator() < 0, "-5");
        Assert(r.Denominator() > 0, "1");
        r = {5, -1};
        Assert(r.Numerator() < 0, "-5");
        Assert(r.Denominator() > 0, "1");
    }
    {
        Rational r = {1, 4};
        AssertEqual(r.Numerator(), 1, "1");
        AssertEqual(r.Denominator(), 4, "4");
        r = {-1, 4};
        AssertEqual(r.Numerator(), -1, "1");
        AssertEqual(r.Denominator(), 4, "4");
    }
    {
        Rational r = {0, 8};
        AssertEqual(r.Denominator(), 1, "Zero");
    }
}

int main() {
    TestRunner tr;
    tr.RunTest(Tests, "Tests");
}
