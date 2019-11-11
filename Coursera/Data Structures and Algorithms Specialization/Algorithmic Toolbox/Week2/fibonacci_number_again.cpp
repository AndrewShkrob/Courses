#include <bits/stdc++.h>

using namespace std;

std::vector<int> pisanoPeriod(int m) {
    std::vector<int> ans;
    ans.push_back(0);
    ans.push_back(1);
    for (int i = 2; i < m * 6; i++) {
        ans.push_back((ans[i - 2] + ans[i - 1]) % m);
        if (ans[i - 1] == 0 && ans[i] == 1)
            break;
    }
    ans.pop_back();
    ans.pop_back();
    return ans;
}

uint64_t FibonacciModM(uint64_t n, uint64_t m) {
    assert(n >= 1);
    assert(m >= 2);
    auto pPeriod = pisanoPeriod(m);
    return pPeriod[n % pPeriod.size()];
}

int main() {
    uint64_t n, m;
    cin >> n >> m;
    cout << FibonacciModM(n, m);
    return 0;
}