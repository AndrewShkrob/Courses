#include <sstream>
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

void test_get_full_name() {
    {
        Person p;
        AssertEqual(p.GetFullName(0), "Incognito", "Incognito");
        AssertEqual(p.GetFullName(228), "Incognito", "Incognito");
        AssertEqual(p.GetFullName(-999), "Incognito", "Incognito");
    }
    {
        Person p;
        p.ChangeFirstName(0, "a");
        p.ChangeFirstName(1, "b");
        p.ChangeFirstName(2, "c");
        AssertEqual(p.GetFullName(0), "a with unknown last name", "Year: 0, First: a, Last: empty");
        AssertEqual(p.GetFullName(1), "b with unknown last name", "Year: 1, First: b, Last: empty");
        AssertEqual(p.GetFullName(2), "c with unknown last name", "Year: 2, First: c, Last: empty");
        AssertEqual(p.GetFullName(5), "c with unknown last name", "Year: 2, First: c, Last: empty");
        AssertEqual(p.GetFullName(-999), "Incognito", "Incognito");
        Assert(p.GetFullName(2) != "Incognito", "Not Incognito");
    }
    {
        Person p;
        p.ChangeLastName(0, "a");
        p.ChangeLastName(1, "b");
        p.ChangeLastName(2, "c");
        AssertEqual(p.GetFullName(0), "a with unknown first name", "Year: 0, First: empty, Last: a");
        AssertEqual(p.GetFullName(1), "b with unknown first name", "Year: 1, First: empty, Last: b");
        AssertEqual(p.GetFullName(2), "c with unknown first name", "Year: 2, First: empty, Last: c");
        AssertEqual(p.GetFullName(5), "c with unknown first name", "Year: 2, First: empty, Last: c");
        AssertEqual(p.GetFullName(-999), "Incognito", "Incognito");
        Assert(p.GetFullName(2) != "Incognito", "Not Incognito");
    }
    {
        Person p;
        p.ChangeFirstName(0, "a");
        p.ChangeLastName(0, "b");
        p.ChangeLastName(1, "c");
        p.ChangeFirstName(8, "dd");
        AssertEqual(p.GetFullName(0), "a b", "Year: 0, First: a, Last: b");
        AssertEqual(p.GetFullName(1), "a c", "Year: 1, First: a, Last: c");
        AssertEqual(p.GetFullName(228), "dd c", "Year: 228, First: dd, Last: c");
        AssertEqual(p.GetFullName(-999), "Incognito", "Incognito");
        Assert(p.GetFullName(2) != "Incognito", "Not Incognito");
    }
}

void test_all() {
    TestRunner tr;
    tr.RunTest(test_get_full_name, "Get Full Name");
}

int main() {
    test_all();
}