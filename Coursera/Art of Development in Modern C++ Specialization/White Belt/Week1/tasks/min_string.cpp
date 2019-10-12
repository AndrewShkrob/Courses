#include <bits/stdc++.h>

using namespace std;

int main() {
    string str1, str2, str3;
    cin >> str1 >> str2 >> str3;
    cout << min(str1, min(str2, str3));
    return 0;
}