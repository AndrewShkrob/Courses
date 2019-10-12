#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

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
    void RunTest(TestFunc func) {
        try {
            func();
            cerr << __func__ << " OK" << endl;
        } catch (runtime_error &e) {
            ++fail_count;
            cerr << __func__ << " fail: " << e.what() << endl;
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

void Test() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "1 = 0");
    AssertEqual(GetDistinctRealRootCount(3, -5, 0), 2, "3x^2 - 5x = 0");
    AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "x = 0");
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "x^2 = -1");
    AssertEqual(GetDistinctRealRootCount(1, 0, -1), 2, "x^2 = 1");
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, "D = 0");
    AssertEqual(GetDistinctRealRootCount(1, 4, 2), 2, "D < 0");
    AssertEqual(GetDistinctRealRootCount(2, 15, 1), 2, "D > 0");
}

int main() {
    TestRunner tr;
    tr.RunTest(Test);
    return 0;
}