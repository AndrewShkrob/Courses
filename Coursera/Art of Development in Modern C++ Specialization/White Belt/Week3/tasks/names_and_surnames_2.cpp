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
        return concat_names(first_name, last_name);
    }

    string GetFullNameWithHistory(int year) {
        vector<string> first_names = current_to_first(names, year);
        vector<string> last_names = current_to_first(surnames, year);
        string first_name = generate_str(first_names);
        string last_name = generate_str(last_names);
        return concat_names(first_name, last_name);
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

    vector<string> current_to_first(const map<int, string> &container, int key) {
        vector<string> result;
        for (const auto &[k, v] : container) {
            if (k <= key) {
                if (result.empty() || (result.back() != v)) {
                    result.push_back(v);
                }
            } else
                break;
        }
        reverse(result.begin(), result.end());
        return result;
    }

    string generate_str(const vector<string> &strs) {
        if (strs.empty())
            return "";
        string result = strs[0];
        if (strs.size() == 1)
            return result;
        result += " (";
        for (int i = 1; i < strs.size(); i++) {
            result += strs[i];
            if (i != strs.size() - 1)
                result += ", ";
        }
        result += ")";
        return result;
    }

    string concat_names(const string &first_name, const string &last_name) {
        if (first_name.empty() && last_name.empty())
            return "Incognito";
        else if (first_name.empty())
            return last_name + " with unknown first name";
        else if (last_name.empty())
            return first_name + " with unknown last name";
        else
            return first_name + " " + last_name;
    }
};