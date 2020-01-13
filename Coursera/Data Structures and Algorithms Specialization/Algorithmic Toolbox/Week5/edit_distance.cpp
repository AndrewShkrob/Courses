#include <bits/stdc++.h>

using namespace std;

int get_edit_distance(string &a, string &b) {
    vector<vector<int>> distance(a.size() + 1, vector<int>(b.size() + 1));
    for (int i = 1; i < a.size() + 1; ++i)
        distance[i][0] = i;
    for (int j = 1; j < b.size() + 1; ++j)
        distance[0][j] = j;
    for (int i = 1; i <= a.size(); ++i) {
        for (int j = 1; j <= b.size(); ++j) {
            int insertion = distance[i][j - 1] + 1;
            int deletion = distance[i - 1][j] + 1;
            int match = distance[i - 1][j - 1];
            int mismatch = distance[i - 1][j - 1] + 1;
            if (a[i - 1] == b[j - 1])
                distance[i][j] = min(min(insertion, deletion), match);
            else
                distance[i][j] = min(min(insertion, deletion), mismatch);
        }
    }
    return distance[a.size()][b.size()];
}

int main() {
    string a;
    string b;
    cin >> a >> b;
    cout << get_edit_distance(a, b);
}