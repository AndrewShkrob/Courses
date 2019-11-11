#include <bits/stdc++.h>

using namespace std;

std::vector<int> pisanoPeriodSum(int m, initializer_list<int> init = {0, 1}) {
    std::vector<int> fib(init);
    std::vector<int> fib_sum{fib[0], (fib[0] + fib[1]) % m};
    for (int i = 2;; i++) {
        fib.push_back((fib[i - 2] + fib[i - 1]) % m);
        fib_sum.push_back((fib[i] + fib_sum[i - 1]) % m);
        if (fib_sum[i - 1] == fib_sum[0] && fib_sum[i] == fib_sum[1])
            break;
    }
    fib_sum.pop_back();
    fib_sum.pop_back();
    return fib_sum;
}

std::vector<int> pisanoPeriod(int m, initializer_list<int> init = {0, 1}) {
    std::vector<int> ans(init);
    for (int i = 2;; i++) {
        ans.push_back((ans[i - 2] + ans[i - 1]) % m);
        if (ans[i - 1] == ans[0] && ans[i] == ans[1])
            break;
    }
    ans.pop_back();
    ans.pop_back();
    return ans;
}

uint64_t FibonacciSumLastDigit(uint64_t from, uint64_t to) {
    auto pPeriod = pisanoPeriod(10);
    auto pPeriodSum = pisanoPeriodSum(10, {pPeriod[from % pPeriod.size()], pPeriod[(from + 1) % pPeriod.size()]});
    return pPeriodSum[(to - from) % pPeriodSum.size()];
}

int main() {
    uint64_t from, to;
    cin >> from >> to;
    cout << FibonacciSumLastDigit(from, to);

    return 0;
}