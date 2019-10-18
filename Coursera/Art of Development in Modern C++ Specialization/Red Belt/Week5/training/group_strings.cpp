#include <algorithm>
#include <vector>

using namespace std;

template<typename String>
using Group = vector<String>;

template<typename String>
using Char = typename String::value_type;

template<typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    map<String, Group<String>> grouped_strings;
    for (auto &str : strings) {
        String sorted_str(str.begin(), str.end());
        sort(sorted_str.begin(), sorted_str.end());
        sorted_str.erase(unique(sorted_str.begin(), sorted_str.end()), sorted_str.end());
        grouped_strings[std::move(sorted_str)].push_back(std::move(str));
    }
    vector<Group<String>> groups;
    for (auto &gr : grouped_strings)
        groups.push_back(std::move(gr.second));
    return groups;
}