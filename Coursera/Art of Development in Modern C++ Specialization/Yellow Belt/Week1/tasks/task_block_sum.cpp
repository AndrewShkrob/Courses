#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, r;
    cin >> n >> r;
    unsigned long long ans = 0;
    for (int i = 0; i < n; i++) {
        unsigned long long w, h, d;
        cin >> w >> h >> d;
        ans += w * h * d * static_cast<unsigned long long>(r);
    }

    cout << ans;

    return 0;
}