#include <bits/stdc++.h>

using namespace std;

int get_lcs_distance(const vector<int> &a, const vector<int> &b, const vector<int> &c) {
    vector<vector<vector<int>>> distance(a.size() + 1, vector<vector<int>>(b.size() + 1, vector<int>(c.size() + 1)));
    for (int i = 1; i <= a.size(); ++i) {
        for (int j = 1; j <= b.size(); ++j) {
            for (int k = 1; k <= c.size(); ++k) {
                if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
                    distance[i][j][k] = distance[i - 1][j - 1][k - 1] + 1;
                else
                    distance[i][j][k] = max(max(distance[i - 1][j][k], distance[i][j - 1][k]), distance[i][j][k - 1]);
            }
        }
    }
    return distance[a.size()][b.size()][c.size()];
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;
    cin >> n;
    vector<int> b(n);
    for (auto &i : b)
        cin >> i;
    cin >> n;
    vector<int> c(n);
    for (auto &i : c)
        cin >> i;
    cout << get_lcs_distance(a, b, c);
}