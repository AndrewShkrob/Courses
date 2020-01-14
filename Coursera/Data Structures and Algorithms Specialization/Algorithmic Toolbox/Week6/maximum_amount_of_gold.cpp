#include <bits/stdc++.h>

using namespace std;

int get_maximum_amount_of_gold(int W, vector<int> &bars) {
    vector<vector<int>> values(W + 1, vector<int>(bars.size() + 1));
    for (int i = 1; i <= W; ++i) {
        for (int j = 1; j <= bars.size(); ++j) {
            values[i][j] = values[i][j - 1];
            if (bars[j - 1] <= i)
                values[i][j] = max(values[i][j], values[i - bars[j - 1]][j - 1] + bars[j - 1]);
        }
    }
    return values[W][bars.size()];
}

int main() {
    int W;
    int n;
    cin >> W >> n;
    vector<int> bars(n);
    for (auto &i : bars)
        cin >> i;
    cout << get_maximum_amount_of_gold(W, bars);
}