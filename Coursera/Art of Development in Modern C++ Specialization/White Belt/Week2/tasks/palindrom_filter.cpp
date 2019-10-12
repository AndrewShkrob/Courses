#include <bits/stdc++.h>

using namespace std;

bool IsPalindrom(const std::string &str) {
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

vector<string> PalindromFilter(const vector<string> &strs, int minLength) {
    vector<string> ans;
    for (const string &str : strs) {
        if (IsPalindrom(str) && str.length() >= minLength)
            ans.push_back(str);
    }
    return ans;
}