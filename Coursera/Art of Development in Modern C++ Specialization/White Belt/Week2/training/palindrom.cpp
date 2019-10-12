#include <bits/stdc++.h>

using namespace std;

bool IsPalindrom(std::string str) {
    int l = 0, r = str.length() - 1;
    while (l < r) {
        if (!isalnum(str[l]))
            l++;
        else if (!isalnum(str[r]))
            r--;
        else if (str[l] != str[r])
            return false;
        else {
            l++;
            r--;
        }
    }
    return true;
}

int main() {
    string str;
    cin >> str;
    cout << (IsPalindrom(str) ? "true" : "false");
    return 0;
}