#include <bits/stdc++.h>

using namespace std;

uint64_t FibonacciLastDigit(uint64_t n) {
    if (n <= 1)
        return n;
    uint64_t a = 0;
    uint64_t b = 1;
    uint64_t ans = 0;
    for (size_t i = 2; i <= n; i++) {
        ans = (a + b) % 10;
        a = b;
        b = ans;
    }
    return ans;
}

int main() {
    uint64_t n;
    cin >> n;
    cout << FibonacciLastDigit(n);
    return 0;
}