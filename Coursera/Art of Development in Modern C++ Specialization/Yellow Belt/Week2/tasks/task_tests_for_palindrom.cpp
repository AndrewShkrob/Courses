#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
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
    Assert(IsPalindrom(""), "empty");
    Assert(IsPalindrom("a"), "one symbol");
    Assert(!IsPalindrom("a "), "a ");
    Assert(IsPalindrom("a a"), "a a");
    Assert(IsPalindrom("abcdcba"), "abcdcba");
    Assert(!IsPalindrom("a bcdcba"), "a bcdcba");
    Assert(IsPalindrom("a bcdcb a"), "a bcdcb a");
    Assert(!IsPalindrom("acba"), "acba");
    Assert(!IsPalindrom("bacca"), "bacca");
    Assert(!IsPalindrom("accab"), "accab");
    Assert(IsPalindrom("madam"), "madam");
    Assert(IsPalindrom("level"), "level");
    Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
    Assert(IsPalindrom("a  b c      c b  a"), "a  b c      c b  a");
    Assert(!IsPalindrom("a b c      c b  a"), "a b c      c b  a");

}

int main() {
    TestRunner runner;
    runner.RunTest(Tests, "");
}