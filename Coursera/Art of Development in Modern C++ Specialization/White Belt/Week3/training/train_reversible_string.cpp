#include <utility>

#include <bits/stdc++.h>

using namespace std;

class ReversibleString {
public:

    ReversibleString() = default;

    ReversibleString(string str) : str(std::move(str)) {}

    void Reverse() {
        reverse(str.begin(), str.end());
    }

    string ToString() const {
        return str;
    }

private:
    string str;
};