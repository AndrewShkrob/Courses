#include <bits/stdc++.h>

using namespace std;

std::vector<int> pisanoPeriodSum(int m) {
    std::vector<int> fib{0, 1};
    std::vector<int> fib_sum{0, 1};
    for (int i = 2;; i++) {
        fib.push_back((fib[i - 2] + fib[i - 1]) % m);
        fib_sum.push_back((fib[i] + fib_sum[i - 1]) % m);
        if (fib_sum[i - 1] == 0 && fib_sum[i] == 1)
            break;
    }
    fib_sum.pop_back();
    fib_sum.pop_back();
    return fib_sum;
}

uint64_t FibonacciSumLastDigit(uint64_t n) {
    auto pPeriod = pisanoPeriodSum(10);
    return pPeriod[n % pPeriod.size()];
}

int main() {
    uint64_t n;
    cin >> n;
    cout << FibonacciSumLastDigit(n);

    return 0;
}