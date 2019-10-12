#include <bits/stdc++.h>

using namespace std;

map<char, int> BuildCharCounters(string &str) {
    map<char, int> ans;
    for(auto &&c : str)
        ans[c]++;
    return ans;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        if (BuildCharCounters(s1) == BuildCharCounters(s2))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}