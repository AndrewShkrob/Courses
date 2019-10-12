#include <bits/stdc++.h>

using namespace std;

int main() {
    string str;
    cin >> str;
    int amt = 0;
    int pos = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'f') {
            amt++;
            pos = i;
            if (amt == 2)
                break;
        }
    }
    if (amt == 0)
        cout << -2;
    else if (amt == 1)
        cout << -1;
    else
        cout << pos;
    return 0;
}