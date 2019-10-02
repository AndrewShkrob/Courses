#include <bits/stdc++.h>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string &first_name) {
        names[year] = first_name;
    }

    void ChangeLastName(int year, const string &last_name) {
        surnames[year] = last_name;
    }

    string GetFullName(int year) {
        string first_name = lower_or_equal(names, year);
        string last_name = lower_or_equal(surnames, year);
        if (first_name.empty() && last_name.empty())
            return "Incognito";
        else if (first_name.empty())
            return last_name + " with unknown first name";
        else if (last_name.empty())
            return first_name + " with unknown last name";
        else
            return first_name + " " + last_name;
    }

private:
    map<int, string> names;
    map<int, string> surnames;

    string lower_or_equal(const map<int, string> &container, int key) {
        string value;
        for (const auto &[k, v] : container) {
            if (k <= key)
                value = v;
            else
                break;
        }
        return value;
    }
};