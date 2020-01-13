#include <bits/stdc++.h>

using namespace std;

int get_minimum_number_of_operations(const vector<int> &coins, int amt) {
    vector<int> min_num_coins(amt + 1, 0);
    for (int i = 1; i < min_num_coins.size(); ++i) {
        min_num_coins[i] = numeric_limits<int>::max();
        for (int coin : coins) {
            if (i >= coin && i - coin >= 0) {
                int num_coins = min_num_coins[i - coin] + 1;
                min_num_coins[i] = min(min_num_coins[i], num_coins);
            }
        }
    }
    return min_num_coins[amt];
}

int main() {
    int amt;
    cin >> amt;
    cout << get_minimum_number_of_operations({1, 3, 4}, amt);
}