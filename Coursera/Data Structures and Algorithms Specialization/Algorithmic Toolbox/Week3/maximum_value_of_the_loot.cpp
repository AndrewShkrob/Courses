#include <bits/stdc++.h>

using namespace std;

bool cmp(const tuple<int, int, double> &a, const tuple<int, int, double> &b) {
    return get<2>(a) > get<2>(b);
}

double get_optimal_value(int capacity, vector<tuple<int, int, double>> &loot) {
    double value = 0.0;
    sort(loot.begin(), loot.end(), cmp);
    int idx = 0;
    while (idx < loot.size() && capacity >= get<1>(loot[idx])) {
        value += static_cast<double>(get<0>(loot[idx]));
        capacity -= get<1>(loot[idx]);
        idx++;
    }
    if (capacity != 0) {
        value += static_cast<double>(get<0>(loot[idx])) / (static_cast<double>(get<1>(loot[idx])) / capacity);
    }
    return value;
}

int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    vector<tuple<int, int, double>> loot;
    for (int i = 0; i < n; i++) {
        int value;
        int weight;
        cin >> value >> weight;
        loot.emplace_back(make_tuple(value, weight, static_cast<double>(value) / weight));
    }

    double optimal_value = get_optimal_value(capacity, loot);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}