#include <bits/stdc++.h>

using namespace std;

bool can_partition_souvenirs(const vector<int> &souvenirs) {
    int total = accumulate(begin(souvenirs), end(souvenirs), 0);
    if (souvenirs.size() < 3 || total % 3 != 0)
        return false;
    int third = total / 3;
    vector<vector<int>> table(third + 1, vector<int>(souvenirs.size() + 1));
    for (int i = 1; i < table.size(); ++i) {
        for (int j = 1; j < table[i].size(); ++j) {
            int ii = i - souvenirs[j - 1];
            if (souvenirs[j - 1] == i || (ii > 0 && table[ii][j - 1] > 0)) {
                if (table[i][j - 1] == 0)
                    table[i][j] = 1;
                else
                    table[i][j] = 2;
            } else
                table[i][j] = table[i][j - 1];
        }
    }
    return table.back().back() == 2;
}

int main() {
    int n;
    cin >> n;
    vector<int> souvenirs(n);
    for (auto &i : souvenirs)
        cin >> i;
    cout << can_partition_souvenirs(souvenirs);
}