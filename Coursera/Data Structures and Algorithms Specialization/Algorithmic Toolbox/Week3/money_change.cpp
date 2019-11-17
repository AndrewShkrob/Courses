#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned int amt;
    cin >> amt;
    vector<int> coins{10, 5, 1};
    size_t idx = 0;
    int amount_of_coins = 0;
    while (amt != 0) {
        if (amt / coins[idx] != 0) {
            amount_of_coins++;
            amt -= coins[idx];
        } else
            idx++;
    }
    cout << amount_of_coins;
    return 0;
}