#include <bits/stdc++.h>

using namespace std;

int main() {
    double N, A, B, X, Y;
    cin >> N >> A >> B >> X >> Y;
    if (N > B)
        N = N - N * (Y / 100);
    else if (N > A)
        N = N - N * (X / 100);
    cout << N;
    return 0;
}