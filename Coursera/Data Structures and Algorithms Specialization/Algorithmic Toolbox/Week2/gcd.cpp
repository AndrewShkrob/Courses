#include <bits/stdc++.h>

using namespace std;

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    uint64_t a;
    uint64_t b;
    cin >> a >> b;
    cout << gcd(a, b);
    return 0;
}