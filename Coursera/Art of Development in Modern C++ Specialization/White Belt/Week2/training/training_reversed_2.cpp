#include <bits/stdc++.h>

using namespace std;

vector<int> Reversed(const vector<int>& v) {
    vector reversed_vector = v;
    std::reverse(reversed_vector.begin(), reversed_vector.end());
    return reversed_vector;
}

int main() {
    vector ans = Reversed({1, 5, 3, 4, 2});
    for (auto &&it : ans)
        cout << it << " ";
}