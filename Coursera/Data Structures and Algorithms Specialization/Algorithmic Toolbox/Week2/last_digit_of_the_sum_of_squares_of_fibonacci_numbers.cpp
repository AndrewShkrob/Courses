#include <bits/stdc++.h>

using namespace std;

std::vector<int> pisanoPeriod(int m) {
    std::vector<int> ans;
    ans.push_back(0);
    ans.push_back(1);
    for (int i = 2;; i++) {
        ans.push_back((ans[i - 2] + ans[i - 1]) % m);
        if (ans[i - 1] == 0 && ans[i] == 1)
            break;
    }
    ans.pop_back();
    ans.pop_back();
    return ans;
}

uint64_t LastDigitOfTheSumOfSquares(uint64_t n) {
    auto pPeriod = pisanoPeriod(10);
    auto nth_last_digit = pPeriod[n % pPeriod.size()];
    auto nth_plus_1_last_digit = pPeriod[(n + 1) % pPeriod.size()];
    return (nth_last_digit * nth_plus_1_last_digit) % 10;
}

int main() {
    uint64_t n;
    cin >> n;
    cout << LastDigitOfTheSumOfSquares(n);
    return 0;
}