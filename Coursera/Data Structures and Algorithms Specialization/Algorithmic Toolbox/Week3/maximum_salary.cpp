#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    sort(begin(a), end(a), [](const string &a, const string &b) {
        return a + b > b + a;
    });
    copy(begin(a), end(a), ostream_iterator<string>(cout));
}