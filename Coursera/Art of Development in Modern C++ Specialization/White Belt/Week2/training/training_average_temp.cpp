#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, avg = 0;
    vector<int> temps;
    vector<int> avg_above;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        temps.push_back(x);
        avg += x;
    }
    avg /= n;
    for (int i = 0; i < n; i++) {
        if (temps[i] > avg)
            avg_above.push_back(i);
    }
    cout << avg_above.size() << endl;
    for (auto &&it : avg_above)
        cout << it << " ";
}