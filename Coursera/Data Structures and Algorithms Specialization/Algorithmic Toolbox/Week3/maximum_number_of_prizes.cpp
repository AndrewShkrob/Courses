#include <bits/stdc++.h>

using namespace std;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    while (n != 0) {
        int num = summands.empty() ? 1 : summands.back() + 1;
        while (num < n && num + num >= n)
            ++num;
        summands.push_back(num);
        n -= num;
    }
    return summands;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
} 