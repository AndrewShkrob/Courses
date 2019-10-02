#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> v;
    while (n--) {
        string x;
        cin >> x;
        v.push_back(x);
    }

    sort(v.begin(), v.end(), [](auto a, auto b) {
        return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                                       [](char a, char b) { return tolower(a) < tolower(b); });
    });
    for (const auto &it : v)
        cout << it << " ";
}