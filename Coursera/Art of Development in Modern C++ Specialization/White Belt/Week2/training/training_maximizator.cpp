#include <bits/stdc++.h>

using namespace std;

void UpdateIfGreater(const int &first, int &second) {
    if (first > second)
        second = first;
}

int main() {
    int a = 4;
    int b = 2;
    UpdateIfGreater(a, b);
    cout << b;
    return 0;
}