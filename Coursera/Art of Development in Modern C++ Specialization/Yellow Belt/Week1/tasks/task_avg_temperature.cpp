#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n;
    cin >> n;
    vector<long long> temperatures(n);
    long long sum = 0;
    for (auto &temperature : temperatures) {
        cin >> temperature;
        sum += temperature;
    }
    long long average = sum / n;

    vector<int> result_indices;
    for (long long i = 0; i < n; ++i) {
        if (temperatures[i] > average) {
            result_indices.push_back(i);
        }
    }

    cout << result_indices.size() << endl;
    for (auto result_index : result_indices) {
        cout << result_index << " ";
    }
    cout << endl;

    return 0;
}