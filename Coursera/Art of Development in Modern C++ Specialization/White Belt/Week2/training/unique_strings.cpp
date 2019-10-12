#include <bits/stdc++.h>

using namespace std;

int main() {
    set<string> strs;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        strs.insert(str);
    }
    cout << strs.size();
    return 0;
}