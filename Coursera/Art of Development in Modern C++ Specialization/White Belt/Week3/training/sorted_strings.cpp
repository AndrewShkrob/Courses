#include <bits/stdc++.h>

using namespace std;

class SortedStrings {
public:
    void AddString(const string& s) {
        sorted_strings.push_back(s);
        sort(sorted_strings.begin(), sorted_strings.end());
    }
    vector<string> GetSortedStrings() {
        return sorted_strings;
    }
private:
    vector<string> sorted_strings;
};