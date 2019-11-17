#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll max_dot_product(vector<ll> &a, vector<ll> &b) {
    ll result = 0;
    sort(begin(a), end(a), std::greater<ll>());
    sort(begin(b), end(b), std::greater<ll>());
    for (size_t i = 0; i < a.size(); ++i)
        result += a[i] * b[i];
    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<ll> a(n), b(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    std::cout << max_dot_product(a, b) << std::endl;
}