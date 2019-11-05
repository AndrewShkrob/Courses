#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    unsigned long long a = 0;
    unsigned long long b = 0;

    cin >> n;

    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        if (tmp > a) {
            if (a > b)
                b = a;
            a = tmp;
        }
        else if (tmp > b) {
            if (b > a)
                a = b;
            b = tmp;
        }
    }

    cout << a * b;

    return 0;
}