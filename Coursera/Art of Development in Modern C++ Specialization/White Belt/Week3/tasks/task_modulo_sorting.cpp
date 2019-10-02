#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v;
    while (n--) {
        int x;
        cin >> x;
        v.push_back(x);
    }

    sort(v.begin(), v.end(), [](auto a, auto b) { return abs(a) < abs(b); });
    for (const auto it : v)
        cout << it << " ";
}