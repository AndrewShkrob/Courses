#include <bits/stdc++.h>

using namespace std;

void change_capital(map<string, string> &capital_dict) {
    string country, new_capital;
    cin >> country >> new_capital;
    if (capital_dict.count(country) == 0) {
        cout << "Introduce new country " << country << " with capital " << new_capital << endl;
        capital_dict[country] = new_capital;
    } else if (capital_dict[country] == new_capital)
        cout << "Country " << country << " hasn't changed its capital" << endl;
    else {
        cout << "Country " << country << " has changed its capital from " << capital_dict[country] << " to "
             << new_capital << endl;
        capital_dict[country] = new_capital;
    }
}

void rename(map<string, string> &capital_dict) {
    string old_country, new_country;
    cin >> old_country >> new_country;
    if (old_country == new_country ||
        capital_dict.find(old_country) == capital_dict.end() ||
        capital_dict.find(new_country) != capital_dict.end()) {
        cout << "Incorrect rename, skip" << endl;
    } else {
        cout << "Country " << old_country << " with capital " << capital_dict[old_country]
             << " has been renamed to " << new_country << endl;
        capital_dict[new_country] = capital_dict[old_country];
        capital_dict.erase(old_country);
    }
}

void about(map<string, string> &capital_dict) {
    string country;
    cin >> country;
    if (capital_dict.find(country) != capital_dict.end())
        cout << "Country " << country << " has capital " << capital_dict[country] << endl;
    else
        cout << "Country " << country << " doesn't exist" << endl;
}

void dump(map<string, string> &capital_dict) {
    if (capital_dict.empty())
        cout << "There are no countries in the world" << endl;
    else {
        for (auto &&it : capital_dict)
            cout << it.first << "/" << it.second << " ";
        cout << endl;
    }
}

int main() {
    map<string, string> capital_dict;
    int q;
    cin >> q;
    while (q--) {
        string str;
        cin >> str;
        if (str == "CHANGE_CAPITAL") {
            change_capital(capital_dict);
        } else if (str == "RENAME") {
            rename(capital_dict);
        } else if (str == "ABOUT") {
            about(capital_dict);
        } else if (str == "DUMP") {
            dump(capital_dict);
        }
    }
    return 0;
}