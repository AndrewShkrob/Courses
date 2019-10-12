#include <bits/stdc++.h>

using namespace std;

vector<string> SplitIntoWords(const string &s) {
    vector<string> result;
    auto left = s.begin();
    auto right = s.begin();
    do {
        right = find(left, s.end(), ' ');
        result.emplace_back(left, right);
        left = next(right);
    } while (right != s.end());
    return result;
}