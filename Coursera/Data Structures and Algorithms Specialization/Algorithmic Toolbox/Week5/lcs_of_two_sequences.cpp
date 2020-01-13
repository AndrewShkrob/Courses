#include <bits/stdc++.h>

using namespace std;

int get_lcs_distance(const vector<int> &a, const vector<int> &b) {
    vector<vector<int>> distance(a.size() + 1, vector<int>(b.size() + 1));
    for (int i = 1; i <= a.size(); ++i) {
        for (int j = 1; j <= b.size(); ++j) {
            if (a[i - 1] == b[j - 1])
                distance[i][j] = distance[i - 1][j - 1] + 1;
            else
                distance[i][j] = max(distance[i - 1][j], distance[i][j - 1]);
        }
    }
    return distance[a.size()][b.size()];
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;
    int m;
    cin >> m;
    vector<int> b(m);
    for (auto &i : b)
        cin >> i;
    cout << get_lcs_distance(a, b);
}