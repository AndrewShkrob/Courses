#include <bits/stdc++.h>

using namespace std;

int main() {
    map<string, set<string>> synonyms;
    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        if (s == "ADD") {
            string s1, s2;
            cin >> s1 >> s2;
            synonyms[s1].insert(s2);
            synonyms[s2].insert(s1);
        } else if (s == "COUNT") {
            string str;
            cin >> str;
            cout << synonyms[str].size() << endl;
        } else if (s == "CHECK") {
            string s1, s2;
            cin >> s1 >> s2;
            if (synonyms[s1].find(s2) != synonyms[s1].end())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
}